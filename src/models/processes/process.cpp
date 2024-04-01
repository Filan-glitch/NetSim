#include "process.h"
#include "src/network/host.h"

using namespace NetSim;

Process::Process(const Port &destinationPort, const QString &name)
    : m_name(name), m_socket(Port::getRandomPort(), destinationPort) {}

QString Process::name() const { return m_name; }

void Process::setHost(Host *host) { this->m_host = host; }

QString Process::toString() const {
  return QString("Name: %1 Port: %2")
      .arg(m_name)
      .arg(m_socket.sourcePort().portNumber());
}

Socket &Process::socket() { return m_socket; }

Socket Process::socket() const { return m_socket; }
