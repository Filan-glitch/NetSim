#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <QString>


/**
 * @brief The HeaderNotFoundException class
 * @par The exception is thrown if a header is not found in a protocol
 */
class HeaderNotFoundException
{
public:
    /**
     * @brief HeaderNotFoundException
     * @param ErrorMessage
     * @par Constructor for the HeaderNotFoundException
     */
    HeaderNotFoundException(QString errorMessage);

    /**
     * @brief GetErrorMessage
     * @return ErrorMessage
     * @par Returns the errorMessage
     */
    QString getErrorMessage() const{
        return this->errorMessage;
    }

private:
    QString errorMessage;
};

#endif // HEADERNOTFOUNDEXCEPTION_H
