#ifndef HEADERUTIL_H
#define HEADERUTIL_H

#include <QString>
#include "src/models/package.h"

/**
 * @brief The HeaderUtil class
 * @par This class gives Utilityfuncionality for packages. All functions are static and return a QString representation of a HeaderAttribute
 */

class HeaderUtil
{
public:
    HeaderUtil();

    /**
     * @brief getHTTPAttributeAsString
     * @param data
     * @param attributeName
     * @return Returns the HTTP Headerattribute corresponding to the attributename
     */
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

    /**
     * @brief getTCPFlag
     * @param data
     * @param flagName
     * @return Returns the tcp flag as true or false corresponding to the flag name
     */
    static QString getTCPFlag(const Package &data, QString flagName);

    /**
     * @brief getIPAddress
     * @param data
     * @param src
     * @return returns the IPAddress
     * @par Returns the IPAddress of a package. You get the source Address is src is true otherwise you get the destonation Address
     */
    static QString getIPAddress(const Package &data, bool src);

    /**
     * @brief getIPFlag
     * @param data
     * @param flagName
     * @return Returns the IPFlag corresponding to the flag name
     */
    static QString getIPFlag(const Package &data, QString flagName);

    /**
     * @brief getIPNextProtocol
     * @param data
     * @return Returns the next Protocol after IPv4, currently only UDP and TCP are possible
     */
    static QString getIPNextProtocol(const Package &data);

    /**
     * @brief getMacAddress
     * @param data
     * @param src
     * @return Returns the MAC Address, if src is true you get the source Address, otherwise the destination Address
     */
    static QString getMacAddress(const Package &data, bool src);


    /**
     * @brief getEtherType
     * @param data
     * @return Returns the EtherType from the Ethernet II Protocol
     */
    static QString getEtherType(const Package &data);

private:
    /**
     * @brief getHeaderByType
     * @param type
     * @param data
     * @return Returns the corresponding Header to a Headertype in a package
     */
    static Header* getHeaderByType(const HeaderType &type, const Package &data);

    /**
     * @brief getHeaderAttributeByName
     * @param name
     * @param header
     * @return Returns the corresponging HeaderAttribute to a HeaderAttributeName in a Header
     */
    static HeaderAttribute getHeaderAttributeByName(const QString &name, const Header &header);
};

#endif // HEADERUTIL_H
