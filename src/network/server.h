#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "host.h"

class Server : public Host
{
    Q_OBJECT
public:
    Server();
};

#endif // SERVER_H
