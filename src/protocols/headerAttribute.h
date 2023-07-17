#ifndef HEADERATTRIBUTE_H
#define HEADERATTRIBUTE_H

#import <string>

using namespace std;
/**
 * @brief The HeaderAttribute class
 * @par Represents a single HeaderAttribute
 */

class HeaderAttribute
{
public:
    /**
     * @brief HeaderAttribute
     * @param HeaderName, sizeInByte, content
     * @par Constructor for a HeaderAttribute
     */
    HeaderAttribute(string headerName, int sizeInByte, int content);

    /**
     * @brief GetName
     * @return Name
     * @par Returns the name of the HeaderAttribute
     */
    string getName() const{
        return this->name;
    }
    /**
     * @brief GetSizeInBit
     * @return SizeInBit
     * @par Returns the size of the HeaderAttribute in bits
     */
    int getSizeInBit() const{
        return this->sizeInBit;
    }
    /**
     * @brief GetContent
     * @return Content
     * @par Returns the content of the HeaderAttribute as bits
     */
    int getContent() const{
        return this->content;
    }

private:
    string name;
    int sizeInBit;
    int content;
};

#endif // HEADERATTRIBUTE_H
