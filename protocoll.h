#ifndef PROTOCOLL_H
#define PROTOCOLL_H

#include "Header.h"
#include "vector"

#include <HeaderNotFoundException.h>

using namespace std;
/**
 * @brief The protocoll class
 * @par This class Simulates a Protocoll from the 5-Layer ISO-OSI-Modell like UDP,TCP,HTTP etc.
 */
class Protocoll
{
public:
    Protocoll();

    /**
     * @brief getSizeInBit
     * @return sizeInBit
     * @par returns the size of the Protocoll in Bit
     */
    int getSizeInBit(){
        return this->sizeInBit;
    }
    /**
     * @brief getHeaderByName
     * @param name
     * @return header
     * @par returns the corrosponding header to the given name
     */
    Header getHeaderByName(string name){
        for(Header h : headerList){
            if(h.getHeaderName() == name){
                return h;
            }
        }
        throw new HeaderNotFoundException("There is no header named: " + name);
    }
private:
    vector<Header> headerList;
    int sizeInBit;
};

#endif // PROTOCOLL_H
