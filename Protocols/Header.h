#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include "headerAttribute.h"
#include "HeaderNotFoundException.h"

using namespace std;
/**
 * @brief The Header class
 * @par This class Simulates a Header from the 5-Layer ISO-OSI-Modell like UDP,TCP,HTTP etc.
 */
class Header
{
public:
    /**
     * @brief Header
     * @param headerList
     * @par The Cunstructor of a Header, requieres a List of Headers
     */
    Header(vector<HeaderAttribute> headerList);

    /**
     * @brief getSizeInBit
     * @return sizeInBit
     * @par returns the size of the Header in Bit
     */
    int getSizeInBit() const{
        return this->sizeInBit;
    }
    /**
     * @brief getHeaderByName
     * @param name
     * @return header
     * @par returns the corrosponding headerAttribute to the given name
     */
    HeaderAttribute getHeaderByName(string &name) const{
        for(HeaderAttribute h : headerList){
            if(h.getHeaderName() == name){
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
