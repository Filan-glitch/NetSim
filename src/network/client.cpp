#include "client.h"
#include "src/protocols/tcp.h"
#include "src/protocols/http.h"
#include "src/network/router.h"


Client::Client(const NetworkCard &networkCard) : Host(networkCard)
{}

IPAddress Client::execDomainResolution(const QString &domain){
    //TODO Implement
}

void Client::execHandShake(const QString &domain){
    IPAddress routerIP(this->getNetworkCard().getNetworkAddress());
    routerIP.getAddressAsArray()[3] = 1;
    MACAddress routerMAC = this->getHostTable()[routerIP];
    Router* router = this->getRouterByMACAddress(routerMAC);

    if(router == nullptr){
        qDebug() << "Router is nullptr in Client::execDomainResolution";
        return;
    }

    QList<Process> processList = this->getProcessTable().values();
    Process httpProcess;

    for(int i = 0; i < processList.size(); i++){
        if(processList[i].getSocket().getSourcePort().getPortNumber() == 80){
            httpProcess = processList[i];
        }
    }

    router->receivePackage(httpProcess.getHandShakePackage(domain,true,true));
}

void Client::execHTTPRequest(){

}

void Client::receivePackage(Package &data){
    //TODO TCP ACK
    //TODO Connection close
    //TODO Add to package List
}
