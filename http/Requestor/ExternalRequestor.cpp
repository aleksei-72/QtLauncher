#include "ExternalRequestor.h"
#include "QtNetwork/QNetworkRequest"
#include "QDebug"
#include "../ResponseProcessor/RawProcessor.h"

ExternalRequestor::ExternalRequestor(QObject *parent)
{
    this->parent = parent;
}

void ExternalRequestor::request(AbstractRequest *requestObject,
                                const std::function<void(QByteArray)> &onResolve,
                                const std::function<void(QString)> &onReject)
 {
     QNetworkAccessManager *network = new QNetworkAccessManager();

     auto func = [=](QNetworkReply *r) {

         if (r->error())
         {
             if (onReject)
             {
                 onReject("Network error: " + r->errorString());
             }

             return;
         }

         RawResponseProcessor processor(r);

         if (processor.getError() != nullptr)
         {
             if (onReject)
             {
                 onReject("JsonParse error: " + r->errorString());
             }

             return;
         }

         if (onResolve)
         {
             onResolve(processor.getBody());
         }
     };

     QObject::connect(network, &QNetworkAccessManager::finished, parent, func);


     requestObject->request.setUrl(this->baseUrl + requestObject->getUrl());

     QNetworkReply *reply = nullptr;

     if (requestObject->getMethod() == AbstractRequest::GET)
     {
         reply = network->get(requestObject->request);
     }


     if (reply)
     {
         reply->waitForReadyRead(this->timeout);
     }

 }
