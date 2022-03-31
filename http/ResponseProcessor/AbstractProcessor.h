#ifndef ABSTRACT_PROCESSOR_H
#define ABSTRACT_PROCESSOR_H

#include "QtNetwork/QNetworkReply"
#include <QObject>
#include <QtCore>
#include "QJsonDocument"
#include "QJsonObject"
#include <iostream>

class AbstractResponseProcessor
{

public:

    QString *getError()
    {
        if (this->error == nullptr)
        {
            return nullptr;
        }

        QString str = QString(*(this->error));

        return &str;
    }

protected:
    QString *error = nullptr;

};
#endif // ABSTRACT_PROCESSOR_H
