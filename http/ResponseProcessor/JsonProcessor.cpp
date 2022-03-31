#include "JsonProcessor.h"


JsonResponseProcessor::JsonResponseProcessor(QNetworkReply *r)
{
    QByteArray body = r->readAll();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(body, &error);

    if (error.error != error.NoError)
    {
        this->error = new QString(error.errorString());
        return;
    }

    this->body = document.object();
}

QJsonObject JsonResponseProcessor::getJson()
{
    return this->body;
}
