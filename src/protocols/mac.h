#ifndef MAC_H
#define MAC_H

#include <QString>

class MAC
{
public:
    MAC();

    static void initHeader(qint8* destMACAdress, qint8* srcMACAdress, qint16 lengthField);
};

#endif // MAC_H
