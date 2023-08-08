#include "headerAttribute.h"

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, const QVector<quint8> &content) : name(name),
    sizeInBit(std::move(sizeInBit)),
    content(content)
{}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content.append(content);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, quint16 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content.append(content >> 8);
    this->content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, quint32 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content.append(content >> 24);
    this->content.append((content >> 16) & 0xFF);
    this->content.append((content >> 8) & 0xFF);
    this->content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, quint64 content) : name(name), sizeInBit(std::move(sizeInBit))
{
    this->content.append(content >> 56);
    this->content.append((content >> 48) & 0xFF);
    this->content.append((content >> 40) & 0xFF);
    this->content.append((content >> 32) & 0xFF);
    this->content.append((content >> 24) & 0xFF);
    this->content.append((content >> 16) & 0xFF);
    this->content.append((content >> 8) & 0xFF);
    this->content.append(content & 0xFF);
}

HeaderAttribute::HeaderAttribute(const QString &name, quint32 sizeInBit, const QString &content) : name(name), sizeInBit(std::move(sizeInBit))
{
    for(auto i = 0; i < content.length(); i++) {
        this->content.append(content.at(i).toLatin1());
    }
}

QString HeaderAttribute::getName() const{
    return this->name;
}

quint32 HeaderAttribute::getSizeInBit() const{
    return this->sizeInBit;
}

quint64 HeaderAttribute::getContentAsInt() const
{
    quint64 returnInt = content[7];
    returnInt = (returnInt << 8) + content[6];
    returnInt = (returnInt << 8) + content[5];
    returnInt = (returnInt << 8) + content[4];
    returnInt = (returnInt << 8) + content[3];
    returnInt = (returnInt << 8) + content[2];
    returnInt = (returnInt << 8) + content[1];
    returnInt = (returnInt << 8) + content[0];
    return returnInt;
}

QVector<quint8> HeaderAttribute::getContentAsArray() const
{
    return content;
}

void HeaderAttribute::setContent(QVector<quint8> content){
    this->content = content;
}
