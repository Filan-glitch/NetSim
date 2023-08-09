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

void Server::getRequest()
{

}

void Server::sendResponse()
{

}

QString Server::getHtmlFile()const{
    return this->htmlFile;
}

void Server::receivePackage(Package &data){
    //TODO add to PackageList

    //Receives a TCP Handshake Package
    if(HeaderUtil::getTCPFlag(data,TCPFlag::SYN) == "Set"){
        //Getting the HTTP Process
        QList<Process> processList = this->getProcessTable().values();
        Process httpProcess;

        for(int i = 0; i < processList.size(); i++){
            if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
                httpProcess = processList[i];
            }
        }

        //Creating the response Package for TCP Handshake
        Package synAckPackage = httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
        routerIP.getAddressAsArray()[3] = 1;
        MACAddress routerMAC = this->getHostTable().value(routerIP);
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
        QList<Process> processList = this->getProcessTable().values();
        Process httpProcess;

        for(int i = 0; i < processList.size(); i++){
            if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
                httpProcess = processList[i];
            }
        }

        //Creating the response Package for close connection
        Package synAckPackage = httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,false);

        //Getting the local Router
        IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
        routerIP.getAddressAsArray()[3] = 1;
        MACAddress routerMAC = this->getHostTable().value(routerIP);
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
        QList<Process> processList = this->getProcessTable().values();
        Process httpProcess;

        for(int i = 0; i < processList.size(); i++){
            if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
                httpProcess = processList[i];
            }
        }

        //Creating the HTTP Response Package
        Package httpResponse = httpProcess.getHTTPResponse(HeaderUtil::getIPAddressAsIPAddress(data,true));

        //Getting the local Router
        IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
        routerIP.getAddressAsArray()[3] = 1;
        MACAddress routerMAC = this->getHostTable().value(routerIP);
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
