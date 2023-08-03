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
     * @param headerName, sizeInByte, content
     * @par Constructor for a HeaderAttribute
     */
    HeaderAttribute(string headerName, int sizeInByte, int content);

    /**
     * @brief getHeaderName
     * @return headerName
     * @par Returns the name of the HeaderAttribute
     */
    string getHeaderName() const{
        return this->headerName;
    }
    /**
     * @brief getSizeInBit
     * @return sizeInBit
     * @par returns the size of the HeaderAttribute in Bits
     */
    int getSizeInBit() const{
        return this->sizeInBit;
    }
    /**
     * @brief getContent
     * @return content
     * @par returns the Content of the HeaderAttribute as Bits
     */
    int getContent() const{
        return this->content;
    }

private:
    string headerName;
    int sizeInBit;
    int content;
};

#endif // HEADERATTRIBUTE_H
