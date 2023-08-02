#ifndef PROCESS_H
#define PROCESS_H

#include "src/network/socket.h"

#include <QString>

class Process
{
public:
    Process();

    void httpGetRequest(const QString &url, Port *sourcePort);
    void openSocket(Port *sourcePort);
private:
    Socket* socket;
};

#endif // PROCESS_H
