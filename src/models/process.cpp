#include "process.h"
#include "package.h"
#include "src/protocols/http.h"


void Process::httpGetRequest(QString url){
    Package httpRequestPackage("");
    HTTP::initHTTPRequest("GET",url,"1.1",httpRequestPackage);

    openSocket();
    socket.addTCPHeader(httpRequestPackage);
}

void Process::openSocket(){
    qint16 portnumber = 80;
    Port port(portnumber);

    Socket socket(port);
    this->socket = socket;
}
