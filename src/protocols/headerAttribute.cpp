#include "headerAttribute.h"

HeaderAttribute::HeaderAttribute(string name, int sizeInByte, int content)
{
    this->name = name;
    this->sizeInBit = sizeInByte;
    this->content = content;
}
