#include "simulationmanager.h"

using namespace NetSim;

SimulationManager::SimulationManager(quint8 clientAmount, quint8 serverAmount,
                                     QList<QString> domains) {
  for (auto i = 0; i <= serverAmount; i++) {
    m_routers.append(Router());
  }

  m_servers.append(Server(NetworkCard(IPAddress::getRandomAddress(),
                                      MACAddress::getRandomAddress()),
                          "dns.beispiel.de", ""));

  for (quint8 i = 0; i < clientAmount; i++) {
    QVector<quint8> routerAddress =
        m_routers[0].networkCard().networkAddress().toArray();
    routerAddress[3] = i + 2;
    m_clients.append(Client(
        NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));
    m_clients[i].addDomain(
        "dns.beispiel.de",
        m_servers.constFirst().networkCard().networkAddress());
  }

  const QString html =
      "<!DOCTYPE html>\n<html>\n\t<header len=\"de\">\n\t\t<meta "
      "charset=\"utf.8\">\n\t</head>\n\t<body>\n\t\t<a>r.mtdv.me/videos/"
      "exampleVideo</a>\n\t</body>\n</html>";
  for (auto i = 0; i < serverAmount; i++) {
    QVector<quint8> routerAddress =
        m_routers[i + 1].networkCard().networkAddress().toArray();
    routerAddress[3] = 2;
    m_servers.append(Server(
        NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress()),
        domains[i], html));
  }

  int i = 0;
  for (auto &client : m_clients) {
    for (auto &router : m_routers) {
      if (i == 0) {
        i++;
        continue;
      }
      client.addIPAddress(router.globalIpAddress(),
                          m_routers[0].networkCard().physicalAddress());
      i++;
    }
    client.addIPAddress(m_servers[0].networkCard().networkAddress(),
                        m_routers[0].networkCard().physicalAddress());
    client.addMACAddress(m_routers.constFirst().networkCard().physicalAddress(),
                         &m_routers[0]);
    m_routers[0].addIPAddress(client.networkCard().networkAddress(),
                              client.networkCard().physicalAddress());
    m_routers[0].addMACAddress(client.networkCard().physicalAddress(), &client);
  }

  for (int i = 0; i < m_servers.size(); ++i) {
    m_servers[i].addIPAddress(m_routers[0].globalIpAddress(),
                              m_routers[i].networkCard().physicalAddress());
    m_servers[i].addMACAddress(m_routers[i].networkCard().physicalAddress(),
                               &m_routers[i]);
  }

  for (int i = 1; i < m_routers.size(); ++i) {
    m_routers[0].addIPAddress(m_routers[i].globalIpAddress(),
                              m_routers[i].networkCard().physicalAddress());
    m_routers[0].addMACAddress(m_routers[i].networkCard().physicalAddress(),
                               &m_routers[i]);
    m_routers[i].addIPAddress(m_routers[0].globalIpAddress(),
                              m_routers[0].networkCard().physicalAddress());
    m_routers[i].addIPAddress(m_servers[i].networkCard().networkAddress(),
                              m_servers[i].networkCard().physicalAddress());
    m_routers[i].addMACAddress(m_routers[0].networkCard().physicalAddress(),
                               &m_routers[0]);
    m_routers[i].addMACAddress(m_servers[i].networkCard().physicalAddress(),
                               &m_servers[i]);
    m_servers[0].addDomain(domains[i - 1], m_routers[i].globalIpAddress());
  }

  m_routers[0].addIPAddress(m_servers[0].networkCard().networkAddress(),
                            m_servers[0].networkCard().physicalAddress());
  m_routers[0].addMACAddress(m_servers[0].networkCard().physicalAddress(),
                             &m_servers[0]);

  for (int i = 1; i < m_routers.size(); ++i) {
    m_routers[i].addNATEntry(
        NATEntry(
            m_servers[i].networkCard().networkAddress(),
            m_servers[i].getProcessByName("HTTP").getSocket().sourcePort()),
        Port(80));
    m_routers[i].addNATEntry(
        NATEntry(m_servers[i].networkCard().networkAddress(),
                 m_servers[i].getProcessByName("DNS").getSocket().sourcePort()),
        Port(53));
  }
  for (int i = 0; i < m_clients.size(); ++i) {
    m_routers[0].addNATEntry(
        NATEntry(
            m_clients[i].networkCard().networkAddress(),
            m_clients[i].getProcessByName("HTTP").getSocket().sourcePort()),
        Port(50000 + 2 * i));
    m_routers[0].addNATEntry(
        NATEntry(m_clients[i].networkCard().networkAddress(),
                 m_clients[i].getProcessByName("DNS").getSocket().sourcePort()),
        Port(50001 + 2 * i));
  }

  // Host Pointer
  for (int i = 0; i < m_clients.size(); i++) {
    m_clients[i].setHostOfProcesses(&m_clients[i]);
  }

  for (int i = 0; i < m_servers.size(); i++) {
    m_servers[i].setHostOfProcesses(&m_servers[i]);
  }
}

quint8 SimulationManager::clientsAmount() const {
  return static_cast<quint8>(m_clients.size());
}

quint8 SimulationManager::serversAmount() const {
  return static_cast<quint8>(m_servers.size() - 1);
}

QList<Server> *SimulationManager::servers() { return &m_servers; }

QList<Client> *SimulationManager::clients() { return &m_clients; }

QList<Router> *SimulationManager::routers() { return &m_routers; }

void SimulationManager::setPackages(PackageTableModel *packages) {
  for (auto &client : m_clients) {
    client.setPackages(packages);
  }
  for (auto &server : m_servers) {
    server.setPackages(packages);
  }
}
