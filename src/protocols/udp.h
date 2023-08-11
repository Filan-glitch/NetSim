#ifndef UDP_H
#define UDP_H

#include "src/models/port.h"
#include "src/models/package.h"
#include <cstdint>
#include <QString>

class UDP
{
public:
    static void initHeader(const Port &sourcePort, const Port &destinationPort, Package &data);

private:
    static quint16 getChecksum(const char* data, quint16 length, quint16 sourcePort, quint16 destinationPort);

    static quint16 overflowHandling(quint16 checksum);
};

#endif // UDP_H
