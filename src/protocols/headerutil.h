#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include <QString>
#include "src/models/package.h"


class HeaderUtil
{
public:
    HeaderUtil();

    static QString getHTTPAttributeAsString(const Package &data, const QString attributeName);

    /**
     * @brief getPort
     * @param data
     * @param tcp
     * @param src
     * @return returns the port
     * @par Returns the port number of a package. You get the source Port if src is true otherwise you get the destination Port
     */
    static QString getPort(const Package &data, bool src);

    static QString getTCPFlag(const Package &data, QString flagName);

    /**
     * @brief getIPAddress
     * @param data
     * @param src
     * @return returns the IPAddress
     * @par Returns the IPAddress of a package. You get the source Address is src is true otherwise you get the destonation Address
     */
    static QString getIPAddress(const Package &data, bool src);

    static QString getIPFlag(const Package &data, QString flagName);

    static QString getIPNextProtocol(const Package &data);

    static QString getMacAddress(const Package &data, bool src);

    static QString getEtherType(const Package &data);

private:
    static Header* getHeaderByType(const HeaderType &type, const Package &data);
    static HeaderAttribute getHeaderAttributeByName(const QString &name, const Header &header);
};

#endif // HEADERUTIL_H
