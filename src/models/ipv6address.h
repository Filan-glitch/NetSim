#ifndef IPV6ADDRESS_H
#define IPV6ADDRESS_H


#include "src/models/rawdata.h"
class IPv6Address
{
public:
    IPv6Address() = default;
    IPv6Address(const RawData& address);
    QString toString() const;
    RawData address() const;
    static IPv6Address getRandomAddress();

private:
    RawData m_address{128};
};

#endif // IPV6ADDRESS_H
