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
     * @param HeaderName, sizeInBit, content
     * @par Constructor for a HeaderAttribute
     */
    HeaderAttribute(QString headerName, qint32 sizeInBit, qint64 content);

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
     * @par Returns the content of the HeaderAttribute as bits
     */
    qint64 getContent() const{
        return this->content;
    }

private:
    QString name;
    qint32 sizeInBit;
    qint64 content;
};

#endif // HEADERATTRIBUTE_H
