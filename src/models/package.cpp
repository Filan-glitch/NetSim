#include "package.h"

Package::Package(const QString& content) : content(content)
{
    this->headers = QList<Header>();
}

void Package::addHeader(const Header& header) {
    this->headers.append(header);
}
