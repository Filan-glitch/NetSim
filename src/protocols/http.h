#ifndef HTTP_H
#define HTTP_H

#include <string>

using namespace std;

class HTTP
{
public:
    HTTP();

    static void initHTTPRequest(string requestType, string url, string version);
    static void initHTTPResponse(string version, int messageCode, int messageText);
};

#endif // HTTP_H
