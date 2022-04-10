#ifndef ABSTRACT_REQUEST_H
#define ABSTRACT_REQUEST_H

#include "QtNetwork/QNetworkReply"

class AbstractRequest
{

public:

    inline static const QString GET = "GET";
    inline static const QString POST = "POST";

    AbstractRequest()
    {

        this->request.setRawHeader("Content-Type", "application/json");
        this->request.setRawHeader("Accept", "application/json");
        //this->request.setRawHeader("User-Agent", "MyApp v0.1");

    }

    virtual QString getMethod()
    {
        return GET;
    }

    virtual QString getUrl()
    {
        return "/";
    }

    QNetworkRequest request;
};

#endif // ABSTRACT_REQUEST_H
