#ifndef PROTOCOL_H
#define PROTOCOL_H

/**
 * @brief The Protocol class
 * @par The superclass to all Protocols
 */
class Protocol
{
public:
    /**
     * @brief Protocol
     * @par The constructor of the superclass Protocol
     */
    Protocol();

    //TODO Braucht noch als Übergabeparameter das Paket
    static void initHeader();
};

#endif // PROTOCOL_H
