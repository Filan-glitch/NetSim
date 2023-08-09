#include "http.h"

void HTTP::initHTTPRequest(const QString &method, const QString &uri, const QString &version, Package& data){
    HeaderAttribute isResponse("Response",8,static_cast<quint8>(0));
    HeaderAttribute requestMethod("Method",method.toLatin1().length()*8,method);
    HeaderAttribute URI("URI",uri.toLatin1().length()*8,uri);
    HeaderAttribute httpVersion("Version", version.toLatin1().length()*8,version);

    QList<HeaderAttribute> headerList;
    headerList.append(isResponse);
    headerList.append(requestMethod);
    headerList.append(URI);
    headerList.append(httpVersion);

    Header httpHeader(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
}

void HTTP::initHTTPResponse(const QString &version, quint16 messageCode, const QString &messagePhrase, Package& data,const QString &htmlFile)
{
    HeaderAttribute isResponse("Response",8,static_cast<quint8>(1));
    HeaderAttribute httpVersion("Version", version.toLatin1().length()*8,version);
    HeaderAttribute code("Code",QString::number(messageCode).length()*8,QString::number(messageCode));
    HeaderAttribute phrase("Phrase", messagePhrase.toLatin1().length()*8,messagePhrase);
    HeaderAttribute contentType("Content-Type", 72, "text/html");

    QList<HeaderAttribute> headerList;
    headerList.append(isResponse);
    headerList.append(httpVersion);
    headerList.append(code);
    headerList.append(phrase);
    headerList.append(contentType);

    Header httpHeader(HeaderType::HTTP,headerList);
    data.addHeader(httpHeader);
    data.setContent(htmlFile);
}
