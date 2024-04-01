#ifndef HTTPDATA_H
#define HTTPDATA_H

#include "src/models/rawdata.h"
namespace NetSim {

class HTTPData
{
public:
    HTTPData() = default;
    HTTPData(const RawData& data);
    HTTPData(const RawData& method, const RawData& path, const RawData& version, const RawData& headers, const RawData& body);

};
} // namespace NetSim
#endif // HTTPDATA_H
