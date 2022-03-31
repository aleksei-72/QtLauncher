#include "RawProcessor.h"


RawResponseProcessor::RawResponseProcessor(QNetworkReply *r)
{
    this->body = r->readAll();
}

QByteArray RawResponseProcessor::getBody()
{
    return this->body;
}
