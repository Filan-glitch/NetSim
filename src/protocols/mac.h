#ifndef MAC_H
#define MAC_H

#include <QString>
#include "../models/macaddress.h"

class MAC
{
public:
    static void initHeader(MACAddress destMACAdress, MACAddress srcMACAdress, qint16 lengthField);
};

#endif // MAC_H
