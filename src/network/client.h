#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

class Client : public Host
{
public:
    Client(const NetworkCard &networkCard);


};

#endif // CLIENT_H
