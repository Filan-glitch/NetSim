#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <string>

using namespace std;
/**
 * @brief The HeaderNotFoundException class
 * @par The Exception is thrown if a header is not found in a Protocoll
 */
class HeaderNotFoundException
{
public:
    /**
     * @brief HeaderNotFoundException
     * @param errorMessage
     * @par Constructor for the HeaderNotFoundException
     */
    HeaderNotFoundException(string errorMessage);

    /**
     * @brief getErrorMessage
     * @return errorMessage
     * @par returns the Exceptions errorMessage
     */
    string getErrorMessage() const{
        return this->errorMessage;
    }

private:
    string errorMessage;
};

#endif // HEADERNOTFOUNDEXCEPTION_H
