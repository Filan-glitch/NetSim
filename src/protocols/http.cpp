#include "http.h"

void HTTP::initHTTPRequest(const QString &method, const QString &url, const QString &version, Package& data){
    HeaderAttribute* requestMethod = new HeaderAttribute("Method",method.toLatin1().length()*8,method);
    HeaderAttribute* URL = new HeaderAttribute("URL",url.toLatin1().length()*8,url);
    HeaderAttribute* httpVersion = new HeaderAttribute("Version", version.toLatin1().length()*8,version);

    QList<HeaderAttribute*> headerList;
    headerList.append(requestMethod);
    headerList.append(URL);
    headerList.append(httpVersion);

    Header* httpHeader = new Header(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
}

void HTTP::initHTTPResponse(const QString &version, quint16 messageCode, const QString &messageText, Package& data, QString htmlFile)
{
    HeaderAttribute* httpVersion = new HeaderAttribute("Version", version.toLatin1().length()*8,version);
    HeaderAttribute* code = new HeaderAttribute("Message code",16,messageCode);
    HeaderAttribute* message = new HeaderAttribute("Message Text", messageText.toLatin1().length()*8,messageText);

    QList<HeaderAttribute*> headerList;
    headerList.append(httpVersion);
    headerList.append(code);
    headerList.append(message);

    Header* httpHeader = new Header(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
    data.setContent(htmlFile);
}
