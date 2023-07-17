#include "router.h"


Router::Router(const QHash<QString, IPAddress> &domainTable) : domainTable(domainTable)
{}
