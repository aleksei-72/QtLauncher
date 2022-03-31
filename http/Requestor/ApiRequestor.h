#ifndef API_REQUESTOR_H
#define API_REQUESTOR_H

#include "QtNetwork/QNetworkAccessManager"
#include "../Requests.h"
#include "QtNetwork/QNetworkReply"
#include <QObject>
#include <QtCore>
#include "QJsonDocument"
#include "QJsonObject"
#include <iostream>

class ApiRequestor
{

public:

    ApiRequestor(QObject *parent = nullptr);

    void request(AbstractRequest *requestObject,
                 const std::function<void(QJsonObject)> &onResolve,
                 const std::function<void(QString)> &onReject);

private:
    QObject *parent;
    QString baseUrl = "http://127.0.0.1:3000/api";
    int timeout = 7500; //ms
};
#endif // API_REQUESTOR_H
