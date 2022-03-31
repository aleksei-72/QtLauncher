#ifndef EXTERNAL_REQUESTOR_H
#define EXTERNAL_REQUESTOR_H

#include "QtNetwork/QNetworkAccessManager"
#include "../Requests.h"
#include "QtNetwork/QNetworkReply"
#include <QObject>
#include <QtCore>
#include "QJsonDocument"
#include "QJsonObject"
#include <iostream>

class ExternalRequestor
{

public:

    ExternalRequestor(QObject *parent = nullptr);

    void request(AbstractRequest *requestObject,
                 const std::function<void(QByteArray)> &onResolve,
                 const std::function<void(QString)> &onReject);

private:
    QObject *parent;
    QString baseUrl = "";
    int timeout = 7500; //ms
};
#endif // EXTERNAL_REQUESTOR_H
