#ifndef IPV4_H
#define IPV4_H

#include <QString>

class IPv4
{
public:
    static void initHeader(qint16 id, qint8 flags, qint16 fragmentOffset, qint8 ttl, qint8 protocol, qint32 sourceAdress, qint32 destinationAdress, char* options, char* data);
};

#endif // IPV4_H
