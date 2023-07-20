#ifndef PROCESS_H
#define PROCESS_H

#include <src/network/socket.h>

#include <QString>

class Process
{
public:


    Process();

    void httpGetRequest(QString url);
    void openSocket();
private:
    Socket socket;
};

#endif // PROCESS_H
