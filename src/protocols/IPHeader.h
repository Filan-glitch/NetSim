#ifndef IPHEADER_H
#define IPHEADER_H

#include "header.h"
#include "src/models/ipaddress.h"

class IPHeader : virtual public Header
{
public:
    IPHeader() : Header{} {}
    IPHeader(const HeaderType& headerType, const QList<HeaderAttribute> &headerList) : Header(headerType, headerList){}
    inline IPAddress getSourceAddress() const {
        return IPAddress(headerList.at(10).getContentAsArray());
    }
    inline IPAddress getDestinationAddress() const {
        return IPAddress(headerList.at(11).getContentAsArray());
    }

};

#endif // IPHEADER_H
