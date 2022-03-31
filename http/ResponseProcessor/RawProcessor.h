#ifndef RAW_PROCESSOR_H
#define RAW_PROCESSOR_H

#include "QtNetwork/QNetworkReply"
#include <QObject>
#include <QtCore>
#include "QJsonDocument"
#include "QJsonObject"
#include <iostream>
#include "AbstractProcessor.h"

class RawResponseProcessor: public AbstractResponseProcessor
{

public:

    RawResponseProcessor(QNetworkReply *);
    QByteArray getBody();

private:
    QByteArray body;

};
#endif // RAW_PROCESSOR_H
