#ifndef HEADERATTRIBUTENOTFOUNDEXCEPTION_H
#define HEADERATTRIBUTENOTFOUNDEXCEPTION_H

#include <QString>



class HeaderAttributeNotFoundException
{
public:
    HeaderAttributeNotFoundException(QString errorMessage);

    QString getErrorMessage(){
        return errorMessage;
    }

private:
    QString errorMessage;
};

#endif // HEADERATTRIBUTENOTFOUNDEXCEPTION_H
