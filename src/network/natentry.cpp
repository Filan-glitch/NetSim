#include "natentry.h"

NATEntry::NATEntry(const IPAddress &address, const Port &port)
{
    this->address = address;
    this->portNumber = port;
}

IPAddress NATEntry::getIPAddress(){
    return address;
}

Port NATEntry::getPortNumber(){
    return portNumber;
}
