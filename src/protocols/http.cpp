#include "http.h"

void HTTP::initHTTPRequest(const QString &method, const QString &url, const QString &version, Package& data){
    HeaderAttribute requestMethod("Method",method.toLatin1().length()*8,method);
    HeaderAttribute URL("URL",url.toLatin1().length()*8,url);
    HeaderAttribute httpVersion("Version", version.toLatin1().length()*8,version);

    QList<HeaderAttribute> headerList;
    headerList.append(requestMethod);
    headerList.append(URL);
    headerList.append(httpVersion);

    Header httpHeader(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
}

void HTTP::initHTTPResponse(const QString &version, quint16 messageCode, const QString &messageText, Package& data, QString htmlFile)
{
    HeaderAttribute httpVersion("Version", version.toLatin1().length()*8,version);
    HeaderAttribute code("Message code",16,messageCode);
    HeaderAttribute message("Message Text", messageText.toLatin1().length()*8,messageText);

    QList<HeaderAttribute> headerList;
    headerList.append(httpVersion);
    headerList.append(code);
    headerList.append(message);

    Header httpHeader(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
    data.setContent(htmlFile);
}
