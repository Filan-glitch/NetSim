#include "process.h"
#include "package.h"
#include "src/hardware/host.h"
#include "src/hardware/server.h"
#include "src/software/01_application_layer/dns.h"
#include "src/software/01_application_layer/http.h"

using namespace NetSim;

Process::Process(const Port &destinationPort, const QString &name)
    : m_name(name), m_socket(Port::getRandomPort(), destinationPort) {}

Package Process::generateHTTPRequestPackage(const QString &uri,
                                            const IPAddress &destination) {
  // Creating the package with info
  Package data("Request HTML of " + uri);

  // Adding the HTTP header to the package
  HTTP::initHTTPRequest("GET", uri, "HTTP/1.1", data);

  // Adding the TCP header to the package
  m_socket.addTCPHeader(data, m_host->networkCard().networkAddress(),
                        destination, true, true, false, false);

  // Adding the IP header to the package
  m_host->networkCard().addIPHeader(data, 6, destination);

  // Adding the MAC header to the package
  m_host->networkCard().addMACHeader(
      data, m_host->hostTable().value(destination), 2048);
  return data;
}

Package Process::generateHandShakePackage(const IPAddress &address,
                                          bool initiate, bool client) {
  // Creating a [SYN] handshake package
  if (initiate && client) {
    Package tcpSynPackage("TCP Handshake [SYN]");

    m_socket.addTCPHeader(tcpSynPackage, m_host->networkCard().networkAddress(),
                          address, false, false, true, false);

    m_host->networkCard().addIPHeader(tcpSynPackage, 6, address);

    m_host->networkCard().addMACHeader(
        tcpSynPackage, m_host->hostTable().value(address), 2048);
    return tcpSynPackage;
  }
  // Creating a [ACK] handshake package
  else if (!initiate && client) {
    Package tcpACKPackage("TCP Handshake [ACK]");
    m_socket.addTCPHeader(tcpACKPackage, m_host->networkCard().networkAddress(),
                          address, true, false, false, false);

    m_host->networkCard().addIPHeader(tcpACKPackage, 6, address);
    m_host->networkCard().addMACHeader(
        tcpACKPackage, m_host->hostTable().value(address), 2048);
    return tcpACKPackage;
  }
  // Creating a [SYN, ACK] handshake package
  else if (!client) {
    Package synAckPackage("TCP Handshake [SYN, ACK]");
    m_socket.addTCPHeader(synAckPackage, m_host->networkCard().networkAddress(),
                          address, true, false, true, false);
    m_host->networkCard().addIPHeader(synAckPackage, 6, address);
    m_host->networkCard().addMACHeader(
        synAckPackage, m_host->hostTable().value(address), 2048);
    return synAckPackage;
  }

  // Returning a default package, if none of the above cases are true
  return Package();
}

Package Process::generateHTTPResponsePackage(const IPAddress &destination,
                                             const Port &destPort,
                                             const int &messageCode) {
  // Creating a HTTP response package
  Package data("HTTP Response to: " + destination.toString());

  // Adding the HTTP response header to the package
  if (messageCode == 200) {
    HTTP::initHTTPResponse("HTTP/1.1", messageCode, "OK", data,
                           static_cast<Server *>(m_host)->htmlFile());
  } else if (messageCode == 404) {
    HTTP::initHTTPResponse("HTTP/1.1", messageCode, "Not Found", data, "");
  } else {
    qDebug() << "No valid messageCode in Process::getHTTPResponse messageCode: "
             << messageCode;
    return Package();
  }

  // Adding the TCP header to the package
  m_socket.setDestinationPort(destPort);
  m_socket.addTCPHeader(data, m_host->networkCard().networkAddress(),
                        destination, true, true, false, false);

  // Adding the IP header to the package
  m_host->networkCard().addIPHeader(data, 6, destination);

  // Adding the MAC header to the package
  m_host->networkCard().addMACHeader(
      data, m_host->hostTable().value(destination), 2048);
  return data;
}

Package Process::generateCloseConnectionPackage(const IPAddress &address,
                                                bool initiate, bool client) {
  // Creating a [FIN] connection package
  if (initiate && client) {
    Package tcpFinPackage("TCP Connection Close [FIN]");

    m_socket.addTCPHeader(tcpFinPackage, m_host->networkCard().networkAddress(),
                          address, false, false, false, true);

    m_host->networkCard().addIPHeader(tcpFinPackage, 6, address);

    m_host->networkCard().addMACHeader(
        tcpFinPackage, m_host->hostTable().value(address), 2048);
    return tcpFinPackage;
  }
  // Creating a [ACK] connection package
  else if (!initiate && client) {
    Package tcpACKPackage("TCP Connection Close [ACK]");
    m_socket.addTCPHeader(tcpACKPackage, m_host->networkCard().networkAddress(),
                          address, true, false, false, false);

    m_host->networkCard().addIPHeader(tcpACKPackage, 6, address);
    m_host->networkCard().addMACHeader(
        tcpACKPackage, m_host->hostTable().value(address), 2048);
    return tcpACKPackage;
  }
  // Creating a [FIN, ACK] connection package
  else if (!client) {
    Package finAckPackage("TCP Connection Close [FIN, ACK]");
    m_socket.addTCPHeader(finAckPackage, m_host->networkCard().networkAddress(),
                          address, true, false, false, true);
    m_host->networkCard().addIPHeader(finAckPackage, 6, address);
    m_host->networkCard().addMACHeader(
        finAckPackage, m_host->hostTable().value(address), 2048);
    return finAckPackage;
  }

  // Returning a default package if none of the above conditions are met
  return Package();
}

Package Process::generateDNSRequestPackage(const QString &domain) {
  Package package("DNS Request of domain: " + domain);

  DNS::initDNSRequest(package, QList<DNSEntry>() << DNSEntry(domain, 1, 1));

  m_socket.addUDPHeader(package);

  IPAddress dnsServer = m_host->domainTable().value(QString("dns.beispiel.de"));
  m_host->networkCard().addIPHeader(package, 17, dnsServer);

  m_host->networkCard().addMACHeader(
      package, m_host->hostTable().value(dnsServer), 2048);

  return package;
}

Package Process::generateDNSResponsePackage(const IPAddress &address,
                                            const QString &domain,
                                            const Port &destPort) {
  Package package("DNS Response of domain: " + domain);
  bool nxDomain = !m_host->domainTable().contains(domain);
  if (nxDomain) {
    DNS::initDNSResponse(package, QList<DNSEntry>() << DNSEntry(domain, 1, 1),
                         QList<DNSEntry>(), nxDomain);

  } else {
    DNS::initDNSResponse(
        package, QList<DNSEntry>() << DNSEntry(domain, 1, 1),
        QList<DNSEntry>() << DNSEntry(
            domain, 1, 1, 5600, m_host->domainTable().value(domain).toArray()),
        nxDomain);
  }

  m_socket.setDestinationPort(destPort);
  m_socket.addUDPHeader(package);

  m_host->networkCard().addIPHeader(package, 17, address);

  m_host->networkCard().addMACHeader(package,
                                     m_host->hostTable().value(address), 2048);

  return package;
}

QString Process::name() const { return m_name; }

void Process::setHost(Host *host) { this->m_host = host; }

QString Process::toString() const {
  return QString("Name: %1 Port: %2")
      .arg(m_name)
      .arg(m_socket.sourcePort().portNumber());
}

Socket &Process::socket() { return m_socket; }

Socket Process::socket() const { return m_socket; }
