#ifndef GET_MAIN_PAGE_REQUEST_H
#define GET_MAIN_PAGE_REQUEST_H

#include "AbstractRequest.h"

class GetMainPageRequest: public virtual AbstractRequest
{

    virtual QString getMethod() override
    {
        return GET;
    }

    virtual QString getUrl() override
    {
        return "/main-page";
    }
};

#endif // GET_MAIN_PAGE_REQUEST_H
