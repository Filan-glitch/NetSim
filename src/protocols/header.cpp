#include "header.h"

Header::Header(vector<HeaderAttribute> headerList)
{
    for(HeaderAttribute h : headerList){
        this->headerList.push_back(h);
    }
}