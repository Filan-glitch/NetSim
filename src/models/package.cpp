#include "package.h"

Package::Package(const QString &content) : content(content)
{
    this->headers = QList<Header>();
}
