#ifndef RAW_REQUEST_H
#define RAW_REQUEST_H

#include "AbstractRequest.h"

class RawGetRequest: public virtual AbstractRequest
{

public:
    RawGetRequest(QString url)
    {
        this->url = url;
    }

    virtual QString getMethod() override
    {
        return GET;
    }

    virtual QString getUrl() override
    {
        return this->url;
    }

private:
    QString url;
};

#endif // RAW_REQUEST_H
