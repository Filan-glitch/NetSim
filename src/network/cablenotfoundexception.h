#ifndef CABLENOTFOUNDEXCEPTION_H
#define CABLENOTFOUNDEXCEPTION_H

#include <QString>

class CableNotFoundException
{
public:
    CableNotFoundException(const QString &errorMessage);

    QString getErrorMessage() const;

private:
     QString errorMessage;
};

#endif // CABLENOTFOUNDEXCEPTION_H
