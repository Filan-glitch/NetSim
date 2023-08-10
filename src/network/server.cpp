#include "server.h"
#include "router.h"

#include <src/protocols/headerutil.h>


Server::Server(const NetworkCard &networkCard, const QString &domain) : Host(networkCard), m_domain(domain)
{
}

QString Server::domain() const
{
    return m_domain;
}

QString Server::getHtmlFile()const{
    return this->htmlFile;
}

void Server::receivePackage(Package data){
    getPackages()->addPackage(data);

    //Receives a DNS Request Package
    if(HeaderUtil::getApplicationProtocol(data) == HeaderType::DNS) {
        //Getting the DNS process
        Process dnsProcess = getProcessByName("DNS");

        //Creating the response package for dns request
        Package dnsResponse = dnsProcess.getDNSResponse(HeaderUtil::getIPAddressAsIPAddress(data, true), HeaderUtil::getDNSQuery(data, 0, RRAttribute::NAME), HeaderUtil::getPortAsPort(data, true));

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        router->receivePackage(dnsResponse);
        return;

    }

    //Receives a TCP Handshake Package
    if(HeaderUtil::getTCPFlag(data,TCPFlag::SYN) == "Set"){
        //Getting the HTTP Process
        Process httpProcess = getProcessByName("HTTP");
        httpProcess.getSocket().setDestinationPort(HeaderUtil::getPortAsPort(data, false));

        //Creating the response Package for TCP Handshake
        Package synAckPackage = httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        router->receivePackage(synAckPackage);
        return;
    }

    //TODO Connection close returnen nicht vergessen!!!!
    if(HeaderUtil::getTCPFlag(data,TCPFlag::FIN) == "Set"){
        //Getting the HTTP Process
        Process httpProcess = getProcessByName("HTTP");

        //Creating the response Package for close connection
        Package synAckPackage = httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        router->receivePackage(synAckPackage);
        return;
    }

    //HTTP Response Message
    if(HeaderUtil::getHTTPIsRequest(data)){
        //Getting the HTTP Process
        Process httpProcess = getProcessByName("HTTP");

        //Creating the HTTP Response Package
        Package httpResponse = httpProcess.getHTTPResponse(HeaderUtil::getIPAddressAsIPAddress(data,true), HeaderUtil::getPortAsPort(data, true));

        //Getting the local Router
        MACAddress routerMAC = this->getHostTable().value(HeaderUtil::getIPAddressAsIPAddress(data, true));
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Server::receivePackage";
            return;
        }

        //Sending package to local Router
        router->receivePackage(httpResponse);
        return;
    }

}
