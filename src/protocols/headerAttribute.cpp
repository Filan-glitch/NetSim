#include "headerAttribute.h"

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, qint8 *content) : name(name),
    sizeInBit(std::move(sizeInBit)),
    content(content)
{}

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, qint8 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content = new qint8[1];
    this->content[0] = content;
}

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, qint16 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content = new qint8[2];
    this->content[0] = content >> 8;
    this->content[1] = content & 0xFF;
}

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, qint32 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content = new qint8[4];
    this->content[0] = content >> 24;
    this->content[1] = (content >> 16) & 0xFF;
    this->content[2] = (content >> 8) & 0xFF;
    this->content[3] = content & 0xFF;
}

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, qint64 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content = new qint8[8];
    this->content[0] = content >> 56;
    this->content[1] = (content >> 48) & 0xFF;
    this->content[2] = (content >> 40) & 0xFF;
    this->content[3] = (content >> 32) & 0xFF;
    this->content[4] = (content >> 24) & 0xFF;
    this->content[5] = (content >> 16) & 0xFF;
    this->content[6] = (content >> 8) & 0xFF;
    this->content[7] = content & 0xFF;
}

HeaderAttribute::HeaderAttribute(const QString &name, qint32 sizeInBit, const QString &content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content = new qint8[content.length()];
    for(auto i = 0; i < content.length(); i++) {
        this->content[i] = content.at(i).toLatin1();
    }
}

HeaderAttribute::~HeaderAttribute()
{
    delete this->content;
}

qint64 HeaderAttribute::getContentAsInt() const
{
    qint64 returnInt = content[7];
    returnInt = (returnInt << 8) + content[6];
    returnInt = (returnInt << 8) + content[5];
    returnInt = (returnInt << 8) + content[4];
    returnInt = (returnInt << 8) + content[3];
    returnInt = (returnInt << 8) + content[2];
    returnInt = (returnInt << 8) + content[1];
    returnInt = (returnInt << 8) + content[0];
    return returnInt;
}

qint8* HeaderAttribute::getContentAsArray() const
{
    return content;
}


