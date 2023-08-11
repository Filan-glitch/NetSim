#ifndef NATENTRY_H
#define NATENTRY_H

#include "src/models/ipaddress.h"
#include "src/models/port.h"

namespace NetSim {
class NATEntry;
}

class NATEntry {
public:
  NATEntry(const IPAddress &address, const Port &port);

  NATEntry();

  Port port() const;

  IPAddress address() const;

  bool operator<(const NATEntry &entry) const;

private:
  Port m_port;

  IPAddress m_address;
};

#endif // NATENTRY_H
