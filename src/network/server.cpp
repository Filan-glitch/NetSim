#include "server.h"

#include <src/protocols/headerutil.h>


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

void Server::receivePackage(Package &data){
    if(HeaderUtil::getTCPFlag(data,TCPFlag::SYN) == "Set"){
        //TODO send SYN ACK Package
        //Package ackPackage = this->
    }

    //TODO HTTP Response

    //TODO Connection close

    //TODO add to PackageList
}
