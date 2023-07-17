#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <string>

using namespace std;
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
    HeaderNotFoundException(string errorMessage);

    /**
     * @brief GetErrorMessage
     * @return ErrorMessage
     * @par Returns the errorMessage
     */
    string getErrorMessage() const{
        return this->errorMessage;
    }

private:
    string errorMessage;
};

#endif // HEADERNOTFOUNDEXCEPTION_H