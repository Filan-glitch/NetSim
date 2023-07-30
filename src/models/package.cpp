#include "package.h"

Package::Package(const QString& summary, const QString &content) : summary(summary), content(content)
{
    this->headers = QList<Header*>();
}
