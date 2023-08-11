#ifndef NATENTRY_H
#define NATENTRY_H

#include <src/models/port.h>
#include "src/models/ipaddress.h"



class NATEntry
{
public:
    NATEntry(const IPAddress &address, const Port &port);

    NATEntry(){};

    Port getPortNumber() const;

    IPAddress getIPAddress() const;

    bool operator<(const NATEntry& entry)const;

private:
    Port portNumber;

    IPAddress address;
};

#endif // NATENTRY_H
