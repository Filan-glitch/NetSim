#include "server.h"


Server::Server(const NetworkCard &networkCard, const QString &domain) : Host(networkCard), m_domain(domain)
{}

QString Server::domain() const
{
    return m_domain;
}

void Server::getRequest()
{

}

void Server::sendResponse()
{

}
