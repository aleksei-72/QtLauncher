#ifndef JSON_REQUEST_PROCESSOR_H
#define JSON_REQUEST_PROCESSOR_H

#include "QtNetwork/QNetworkReply"
#include <QObject>
#include <QtCore>
#include "QJsonDocument"
#include "QJsonObject"
#include <iostream>
#include "AbstractProcessor.h"

class JsonResponseProcessor: public AbstractResponseProcessor
{

public:

    JsonResponseProcessor(QNetworkReply *);
    QJsonObject getJson();

private:
    QJsonObject body;

};
#endif // JSON_REQUEST_PROCESSOR_H
