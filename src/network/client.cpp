#include "client.h"
#include "src/protocols/headerutil.h"
#include "src/protocols/tcp.h"
#include "src/protocols/http.h"
#include "src/network/router.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{}

IPAddress Client::execDomainResolution(const QString &domain){
    //TODO Implement
}

void Client::execHandShake(const IPAddress &address){
    IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
    routerIP.getAddressAsArray()[3] = 1;
    MACAddress routerMAC = this->getHostTable().value(routerIP);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    QList<Process> processList = this->getProcessTable().values();
    Process httpProcess;

    for(int i = 0; i < processList.size(); i++){
        if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
            httpProcess = processList[i];
        }
    }

    router->receivePackage(httpProcess.getHandShakePackage(address,true,true));
}

void Client::execHTTPRequest(const IPAddress &address, const QString &uri){
    IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
    routerIP.getAddressAsArray()[3] = 1;
    MACAddress routerMAC = this->getHostTable().value(routerIP);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHTTPRequest";
        return;
    }

    QList<Process> processList = this->getProcessTable().values();
    Process httpProcess;

    for(int i = 0; i < processList.size(); i++){
        if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
            httpProcess = processList[i];
        }
    }

    router->receivePackage(httpProcess.getHTTPRequest(uri,address));
}

void Client::execCloseConnection(const IPAddress &address){
    IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
    routerIP.getAddressAsArray()[3] = 1;
    MACAddress routerMAC = this->getHostTable().value(routerIP);
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execHandShake";
        return;
    }

    QList<Process> processList = this->getProcessTable().values();
    Process httpProcess;

    for(int i = 0; i < processList.size(); i++){
        if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
            httpProcess = processList[i];
        }
    }

    router->receivePackage(httpProcess.getCloseConnectionPackage(address,true,true));
}

void Client::receivePackage(Package &data){
    //TODO Add to Packagelist

    //Receives a TCP Handshake Package from Server
    if(HeaderUtil::getTCPFlag(data, TCPFlag::SYN) == "Set" && HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set"){
        IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
        routerIP.getAddressAsArray()[3] = 1;
        MACAddress routerMAC = this->getHostTable().value(routerIP);
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        QList<Process> processList = this->getProcessTable().values();
        Process httpProcess;

        for(int i = 0; i < processList.size(); i++){
            if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
                httpProcess = processList[i];
            }
        }

        router->receivePackage(httpProcess.getHandShakePackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }

    //Receives a Closing Package from Server
    if(HeaderUtil::getTCPFlag(data, TCPFlag::FIN) == "Set" && HeaderUtil::getTCPFlag(data, TCPFlag::ACK) == "Set"){
        IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
        routerIP.getAddressAsArray()[3] = 1;
        MACAddress routerMAC = this->getHostTable().value(routerIP);
        Router* router = this->getRouterByMACAddress(routerMAC);

        if(router == nullptr){
            qDebug() << "Router is nullptr in Client::receivePackage";
            return;
        }

        QList<Process> processList = this->getProcessTable().values();
        Process httpProcess;

        for(int i = 0; i < processList.size(); i++){
            if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
                httpProcess = processList[i];
            }
        }

        router->receivePackage(httpProcess.getCloseConnectionPackage(HeaderUtil::getIPAddressAsIPAddress(data,true),false,true));
    }
}
