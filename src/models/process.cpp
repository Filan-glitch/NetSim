#include "process.h"
#include "package.h"
#include "src/protocols/http.h"

void Process::httpGetRequest(const QString &url, Port *sourcePort){
    Package httpRequestPackage("Request HTML of " + url,"");
    HTTP::initHTTPRequest("GET",url,"HTTP/1.1",httpRequestPackage);

    openSocket(sourcePort);
    socket->addTCPHeader(httpRequestPackage);
}

void Process::openSocket(Port *sourcePort){
    this->socket = new Socket(sourcePort, new Port(80));
}
