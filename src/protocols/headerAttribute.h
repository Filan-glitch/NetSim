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
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 content);
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint16 content);
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint32 content);
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint64 content);
    HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 *content);
    HeaderAttribute(const QString &name, quint32 sizeInBit, const QString &content);

    ~HeaderAttribute();

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
    quint32 getSizeInBit() const{
        return this->sizeInBit;
    }

    /**
     * @brief GetContent
     * @return Content
     * @par Returns the content of the HeaderAttribute as bits as int
     */
    quint64 getContentAsInt() const;

    /**
     * @brief GetContent
     * @return Content
     * @par Returns the content of the HeaderAttribute as bits as an array
     */
    quint8* getContentAsArray() const;


private:
    QString name;
    quint32 sizeInBit;
    quint8* content;
};

#endif // HEADERATTRIBUTE_H
