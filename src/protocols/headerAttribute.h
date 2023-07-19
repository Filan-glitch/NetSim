#ifndef HEADERATTRIBUTE_H
#define HEADERATTRIBUTE_H

#include <QString>


/**
 * @brief The HeaderAttribute class
 * @par Represents a single HeaderAttribute
 */

class HeaderAttribute
{
public:
    /**
     * @brief HeaderAttribute
     * @param Name, sizeInBit, content
     * @par Constructor for a HeaderAttribute
     */
    HeaderAttribute(const QString &name, qint32 sizeInBit, qint8 content);
    HeaderAttribute(const QString &name, qint32 sizeInBit, qint16 content);
    HeaderAttribute(const QString &name, qint32 sizeInBit, qint32 content);
    HeaderAttribute(const QString &name, qint32 sizeInBit, qint64 content);
    HeaderAttribute(const QString &name, qint32 sizeInBit, qint8 *content);

    /**
     * @brief GetName
     * @return Name
     * @par Returns the name of the HeaderAttribute
     */
    QString getName() const{
        return this->name;
    }

    /**
     * @brief GetSizeInBit
     * @return SizeInBit
     * @par Returns the size of the HeaderAttribute in bits
     */
    qint32 getSizeInBit() const{
        return this->sizeInBit;
    }

    /**
     * @brief GetContent
     * @return Content
     * @par Returns the content of the HeaderAttribute as bits as int
     */
    qint64 getContentAsInt() const;

    /**
     * @brief GetContent
     * @return Content
     * @par Returns the content of the HeaderAttribute as bits as an array
     */
    qint8* getContentAsArray() const;


private:
    QString name;
    qint32 sizeInBit;
    qint8* content;
};

#endif // HEADERATTRIBUTE_H
