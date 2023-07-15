#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "host.h"

class Client : public Host
{
    Q_OBJECT
public:
    Client();
};

#endif // CLIENT_H
