#include "ApiRequestor.h"
#include "QtNetwork/QNetworkRequest"
#include "QDebug"
#include "http/ResponseProcessor/JsonProcessor.h"

ApiRequestor::ApiRequestor(QObject *parent)
{
    this->parent = parent;
}

void ApiRequestor::request(AbstractRequest *requestObject,
                               const std::function<void(QJsonObject)> &onResolve,
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

        JsonResponseProcessor processor(r);

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
            onResolve(processor.getJson());
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
