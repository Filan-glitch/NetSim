#include "natentry.h"

using namespace NetSim;

NATEntry::NATEntry(const IPv4Address &address, const Port &port) {
  this->m_address = address;
  this->m_port = port;
}

IPv4Address NATEntry::address() const { return m_address; }

bool NATEntry::operator<(const NATEntry &entry) const {
  return this->m_port.portNumber() < entry.m_port.portNumber();
}

Port NATEntry::port() const { return m_port; }
