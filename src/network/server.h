#ifndef SERVER_H
#define SERVER_H

#include "host.h"


class Server : public Host
{
private:
    QString m_domain;
public:
    Server(const NetworkCard &networkCard, const QString &domain);

    QString domain() const;

    void getRequest();
    void sendResponse();
};

#endif // SERVER_H
