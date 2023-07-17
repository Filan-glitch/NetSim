#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include "headerAttribute.h"
#include "headerNotFoundException.h"

using namespace std;
/**
 * @brief The Header class
 * @par This class simulates a header of a protocol
 */
class Header
{
public:
    /**
     * @brief Header
     * @param HeaderList
     * @par The constructor of a Header, requires a list of HeaderAttributes
     */
    Header(vector<HeaderAttribute> headerList);

    /**
     * @brief GetSizeInBit
     * @return SizeInBit
     * @par Returns the size of the Header in bits
     */
    int getSizeInBit() const{
        return this->sizeInBit;
    }
    /**
     * @brief GetHeaderAttributeByName
     * @param Name
     * @return HeaderAttribute
     * @par Returns the corrosponding HeaderAttribute to the given name
     */
    HeaderAttribute getHeaderAttributeByName(string &name) const{
        for(HeaderAttribute h : headerList){
            if(h.getName() == name){
                return h;
            }
        }
        throw new HeaderNotFoundException("There is no header named: " + name);
    }
private:
    vector<HeaderAttribute> headerList;
    int sizeInBit;
};

#endif // HEADER_H
