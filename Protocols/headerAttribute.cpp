#include "headerAttribute.h"

HeaderAttribute::HeaderAttribute(string headerName, int sizeInByte, int content)
{
    this->headerName = headerName;
    this->sizeInBit = sizeInByte;
    this->content = content;
}
