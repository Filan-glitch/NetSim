#include "simulationmanager.h"

using namespace NetSim;

SimulationManager::SimulationManager(Praktikum praktikum) {
  m_praktikum = praktikum;
  // // Setting the routers
  // for (auto i = 0; i <= serverAmount; i++) {
  //   m_routers.append(Router());
  // }

  // // Setting the DNS Server
  // m_servers.append(Server(NetworkCard(IPAddress::getRandomAddress(),
  //                                     MACAddress::getRandomAddress()),
  //                         "dns.beispiel.de", ""));

  // // Setting the clients
  // for (quint8 i = 0; i < clientAmount; i++) {
  //   // Extracting the IP Address of the client router
  //   QVector<quint8> routerAddress =
  //       m_routers[0].networkCard().networkAddress().toArray();
  //   // Incrementing the last byte of the IP Address for each host
  //   routerAddress[3] = i + 2;

  //   // Adding the client to the list
  //   m_clients.append(Client(
  //       NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));

  //   // Adding the domain of the dns to the dns cache of the client
  //   m_clients[i].addDomain(
  //       "dns.beispiel.de",
  //       m_servers.constFirst().networkCard().networkAddress());
  // }

  // // Setting a basic default html file for the servers
  // const QString html =
  //     "<!DOCTYPE html>\n<html>\n\t<header len=\"de\">\n\t\t<meta "
  //     "charset=\"utf.8\">\n\t</head>\n\t<body>\n\t\t<a>r.mtdv.me/videos/"
  //     "exampleVideo</a>\n\t</body>\n</html>";

  // // Setting the servers
  // for (auto i = 0; i < serverAmount; i++) {
  //   // Extracting the IP Address of the specific router
  //   QVector<quint8> routerAddress =
  //       m_routers[i + 1].networkCard().networkAddress().toArray();
  //   routerAddress[3] = 2;

  //   // Adding the server to the list
  //   m_servers.append(Server(
  //       NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress()),
  //       domains[i], html));
  // }

  // // Setting the Connections
  // int i = 0;
  // for (auto &client : m_clients) {
  //   for (auto &router : m_routers) {
  //     if (i == 0) {
  //       i++;
  //       continue;
  //     }
  //     // Setting the Clients IP to MAC Table
  //     client.addIPAddress(router.globalIpAddress(),
  //                         m_routers[0].networkCard().physicalAddress());
  //     i++;
  //   }
  //   // Setting the Clients IP to MAC Table
  //   client.addIPAddress(m_servers[0].networkCard().networkAddress(),
  //                       m_routers[0].networkCard().physicalAddress());
  //   // Setting the Clients MAC to Router Pointer Table
  //   client.addMACAddress(m_routers.constFirst().networkCard().physicalAddress(),
  //                        &m_routers[0]);
  //   // Setting the Client-Routers IP to MAC Table
  //   m_routers[0].addIPAddress(client.networkCard().networkAddress(),
  //                             client.networkCard().physicalAddress());
  //   // Setting the Client-Routers MAC to Client Pointer Table
  //   m_routers[0].addMACAddress(client.networkCard().physicalAddress(), &client);
  // }

  // for (int i = 0; i < m_servers.size(); ++i) {
  //   // Setting the Servers IP to MAC Table
  //   m_servers[i].addIPAddress(m_routers[0].globalIpAddress(),
  //                             m_routers[i].networkCard().physicalAddress());
  //   // Setting the Servers MAC to Router Table
  //   m_servers[i].addMACAddress(m_routers[i].networkCard().physicalAddress(),
  //                              &m_routers[i]);
  // }

  // for (int i = 1; i < m_routers.size(); ++i) {
  //   // Setting the Client-Routers IP to MAC Table
  //   m_routers[0].addIPAddress(m_routers[i].globalIpAddress(),
  //                             m_routers[i].networkCard().physicalAddress());
  //   // Setting the Client-Router MAC to Router Pointer Table
  //   m_routers[0].addMACAddress(m_routers[i].networkCard().physicalAddress(),
  //                              &m_routers[i]);
  //   // Setting the specific Server-Router IP to MAC Table
  //   m_routers[i].addIPAddress(m_routers[0].globalIpAddress(),
  //                             m_routers[0].networkCard().physicalAddress());
  //   // Setting the specific Server-Router IP to MAC Table
  //   m_routers[i].addIPAddress(m_servers[i].networkCard().networkAddress(),
  //                             m_servers[i].networkCard().physicalAddress());
  //   // Setting the specific Server-Router MAC to Router Pointer Table
  //   m_routers[i].addMACAddress(m_routers[0].networkCard().physicalAddress(),
  //                              &m_routers[0]);
  //   // Setting the specific Server-Router MAC to Server Pointer Table
  //   m_routers[i].addMACAddress(m_servers[i].networkCard().physicalAddress(),
  //                              &m_servers[i]);
  //   // Setting the DNS Server Domain Table
  //   m_servers[0].addDomain(domains[i - 1], m_routers[i].globalIpAddress());
  // }

  // // Setting the Client-Router IP to MAC Table
  // m_routers[0].addIPAddress(m_servers[0].networkCard().networkAddress(),
  //                           m_servers[0].networkCard().physicalAddress());
  // // Setting the Client-Router MAC to Server Pointer Table
  // m_routers[0].addMACAddress(m_servers[0].networkCard().physicalAddress(),
  //                            &m_servers[0]);

  // for (int i = 1; i < m_routers.size(); ++i) {
  //   // Setting the specific Server-Router NAT Entry
  //   m_routers[i].addNATEntry(
  //       NATEntry(m_servers[i].networkCard().networkAddress(),
  //                m_servers[i].getProcessByName("HTTP").socket().sourcePort()),
  //       Port(80));
  //   m_routers[i].addNATEntry(
  //       NATEntry(m_servers[i].networkCard().networkAddress(),
  //                m_servers[i].getProcessByName("DNS").socket().sourcePort()),
  //       Port(53));
  // }
  // for (int i = 0; i < m_clients.size(); ++i) {
  //   // Setting the Client-Router NAT Entry
  //   m_routers[0].addNATEntry(
  //       NATEntry(m_clients[i].networkCard().networkAddress(),
  //                m_clients[i].getProcessByName("HTTP").socket().sourcePort()),
  //       Port(50000 + 2 * i));
  //   m_routers[0].addNATEntry(
  //       NATEntry(m_clients[i].networkCard().networkAddress(),
  //                m_clients[i].getProcessByName("DNS").socket().sourcePort()),
  //       Port(50001 + 2 * i));
  // }

  // // Setting the Host of the Processes, so the processes can use the functions
  // for (int i = 0; i < m_clients.size(); i++) {
  //   m_clients[i].setHostOfProcesses(&m_clients[i]);
  // }

  // // Setting the Host of the Processes, so the processes can use the functions
  // for (int i = 0; i < m_servers.size(); i++) {
  //   m_servers[i].setHostOfProcesses(&m_servers[i]);
  // }
  switch(praktikum) {
    case HTTP_Praktikum:
    {
        // Mainrouter
        m_routers.append(Router(IPAddress(QVector<quint8>({192, 168, 178, 1})), IPAddress(QVector<quint8>({203, 0, 113, 195}))));

        // Serverrouter
        m_routers.append(Router(IPAddress(QVector<quint8>({10, 0, 0, 1})), IPAddress(QVector<quint8>({213, 8, 70, 122}))));

        // Client
        QVector<quint8> routerAddress =
            m_routers[0].networkCard().networkAddress().toArray();
        // Incrementing the last byte of the IP Address for each host
        routerAddress[3] = 2;

        // Adding the client to the list
        m_clients.append(Client(
            NetworkCard(IPAddress(routerAddress), MACAddress::getRandomAddress())));

        // // Setting a basic default html file for the servers
        const QString html =
            "<!DOCTYPE html>\n<html>\n\t<header len=\"de\">\n\t\t<meta "
            "charset=\"utf.8\">\n\t</head>\n\t<body>\n\t\t<a>r.mtdv.me/videos/"
            "exampleVideo</a>\n\t</body>\n</html>";

        // Setting the servers
        // Extracting the IP Address of the specific router
        QVector<quint8> serverRouterAddress =
            m_routers[1].networkCard().networkAddress().toArray();
        serverRouterAddress[3] = 2;
        // Adding the server to the list
        m_servers.append(Server(
            NetworkCard(IPAddress(serverRouterAddress), MACAddress::getRandomAddress()),
            "cn.hs-ruhrwest.de", html));
        // Adding the domain of the server to the dns cache of the client
        m_clients[0].addDomain(
            "cn.hs-ruhrwest.de",
            m_routers[1].globalIpAddress());
        // Setting the Clients IP to MAC Table
            m_clients[0].addIPAddress(m_routers[1].globalIpAddress(),
                                m_routers.constFirst().networkCard().physicalAddress());
        // Setting the Clients MAC to Router Pointer Table
        m_clients[0].addMACAddress(m_routers.constFirst().networkCard().physicalAddress(),
                             &m_routers[0]);
        // Setting the Client-Routers IP to MAC Table
        m_routers[0].addIPAddress(m_clients.constFirst().networkCard().networkAddress(),
                                  m_clients.constFirst().networkCard().physicalAddress());
        // Setting the Client-Routers MAC to Client Pointer Table
          m_routers[0].addMACAddress(m_clients.constFirst().networkCard().physicalAddress(), &m_clients[0]);


        //Setting the Servers IP to MAC Table
          m_servers[0].addIPAddress(m_routers[0].globalIpAddress(),
                                    m_routers[1].networkCard().physicalAddress());
          // Setting the Servers MAC to Router Table
          m_servers[0].addMACAddress(m_routers[1].networkCard().physicalAddress(),
                                     &m_routers[1]);

          // Setting the Client-Routers IP to MAC Table
          m_routers[0].addIPAddress(m_routers[1].globalIpAddress(),
                                    m_routers[1].networkCard().physicalAddress());
          // Setting the Client-Router MAC to Router Pointer Table
          m_routers[0].addMACAddress(m_routers[1].networkCard().physicalAddress(),
                                     &m_routers[1]);
          // Setting the specific Server-Router IP to MAC Table
          m_routers[1].addIPAddress(m_routers[0].globalIpAddress(),
                                    m_routers[0].networkCard().physicalAddress());
          // Setting the specific Server-Router IP to MAC Table
          m_routers[1].addIPAddress(m_servers[0].networkCard().networkAddress(),
                                    m_servers[0].networkCard().physicalAddress());
          // Setting the specific Server-Router MAC to Router Pointer Table
          m_routers[1].addMACAddress(m_routers[0].networkCard().physicalAddress(),
                                     &m_routers[0]);
          // Setting the specific Server-Router MAC to Server Pointer Table
          m_routers[1].addMACAddress(m_servers[0].networkCard().physicalAddress(),
                                     &m_servers[0]);

          // Setting the specific Server-Router NAT Entry
          m_routers[1].addNATEntry(
              NATEntry(m_servers[0].networkCard().networkAddress(),
                       m_servers[0].getProcessByName("HTTP").socket().sourcePort()),
              Port(80));
          m_routers[1].addNATEntry(
              NATEntry(m_servers[0].networkCard().networkAddress(),
                       m_servers[0].getProcessByName("DNS").socket().sourcePort()),
              Port(53));
          // Setting the Client-Router NAT Entry
          m_routers[0].addNATEntry(
              NATEntry(m_clients[0].networkCard().networkAddress(),
                       m_clients[0].getProcessByName("HTTP").socket().sourcePort()),
              Port(50000 + 2));
          m_routers[0].addNATEntry(
              NATEntry(m_clients[0].networkCard().networkAddress(),
                       m_clients[0].getProcessByName("DNS").socket().sourcePort()),
              Port(50001 + 2));

        // Setting the Host of the Processes, so the processes can use the functions
        m_clients[0].setHostOfProcesses(&m_clients[0]);

        // Setting the Host of the Processes, so the processes can use the functions
        m_servers[0].setHostOfProcesses(&m_servers[0]);
    }
    case DNS_Praktikum:
    case UDP_Praktikum:
    case TCP_Praktikum:
    case ICMP_Praktikum:
    case IP_Praktikum:
    case DHCP_Praktikum:
    case ARP_Praktikum:
        break;
  }
}

quint8 SimulationManager::clientsAmount() const {
  return static_cast<quint8>(m_clients.size());
}

quint8 SimulationManager::serversAmount() const {
  return static_cast<quint8>(m_servers.size() - 1);
}

Praktikum SimulationManager::praktikum() const { return m_praktikum; }

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
