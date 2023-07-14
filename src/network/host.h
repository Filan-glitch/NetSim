#ifndef HOST_H
#define HOST_H

#include <QString>
#include <QHash>
#include "process.h"

class Host
{
private:
    qint32 ipAddress;
    QHash<qint16, Process> processTable;
    QHash<qint64, qint32> hostTable;
    QHash<QString, qint32> domainTable;

public:
    Host();
};

#endif // HOST_H
