#include "ipv6address.h"
#include <QRandomGenerator>

IPv6Address::IPv6Address(const RawData &address) : m_address(address) {}

QString IPv6Address::toString() const
{
    QString returnString = "";
    for(int i = 0; i < 16; i++)
    {
        returnString += QString::number(static_cast<int>(m_address.getByte(i)), 16);
        if(i != 15)
        {
            returnString += ":";
        }
    }
    return returnString;
}

RawData IPv6Address::address() const
{
    return m_address;
}

IPv6Address IPv6Address::getRandomAddress()
{
    RawData address(128);
    for(int i = 0; i < 16; i++)
    {
        address.setByte(i, QRandomGenerator::global()->generate());
    }
    return IPv6Address(address);
}
