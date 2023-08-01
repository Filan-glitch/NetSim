#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
public:
    Client(NetworkCard *networkCard) : Host(networkCard)
    {}


};

#endif // CLIENT_H
