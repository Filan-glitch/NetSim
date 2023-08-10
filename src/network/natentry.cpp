#include "natentry.h"

NATEntry::NATEntry(const IPAddress &address, const Port &port)
{
    this->address = address;
    this->portNumber = port;
}

IPAddress NATEntry::getIPAddress(){
    return address;
}

bool NATEntry::operator<(const NATEntry &entry) const{
    return this->portNumber.getPortNumber() < entry.portNumber.getPortNumber();
}

Port NATEntry::getPortNumber(){
    return portNumber;
}
