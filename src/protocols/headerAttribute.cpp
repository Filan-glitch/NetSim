#include "headerAttribute.h"

HeaderAttribute::HeaderAttribute(QString name, qint32 sizeInBit, qint64 content)
{
    this->name = name;
    this->sizeInBit = sizeInBit;
    this->content = content;
}
