#include "networktab.h"
#include <QPainter>

using namespace NetSim;

NetworkTab::NetworkTab(QWidget *parent) : QWidget{parent} {
  this->setContentsMargins(2, 2, 2, 2);
}

void NetworkTab::addRouter(RouterWidget *router) { m_routers.append(router); }

void NetworkTab::addServer(ServerWidget *server) { m_servers.append(server); }

void NetworkTab::addClient(ClientWidget *client) { m_clients.append(client); }

QList<RouterWidget *> NetworkTab::routers() const { return m_routers; }

QList<ServerWidget *> NetworkTab::servers() const { return m_servers; }

QList<ClientWidget *> NetworkTab::clients() const { return m_clients; }

// Overriding the paintEvent function to draw the connections between the
// widgets
void NetworkTab::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

  QPainter painter{this};
  painter.setPen(QPen(Qt::blue, 4));

  // Connections Server -> Router
  for (auto i = 0; i < m_servers.size(); ++i) {
    painter.drawLine(
        m_servers[i]->mapTo(this, m_servers[i]->button()->rect().center()),
        m_routers[i+1]->mapTo(this, m_routers[i+1]->button()->rect().center()));
  }

  // Connections Router -> Router
  for (auto router : m_routers) {
    if (router == m_routers[0])
      continue;
    painter.drawLine(
        router->mapTo(this, router->button()->rect().center()),
        m_routers[0]->mapTo(this, m_routers[0]->button()->rect().center()));
  }

  // Connections Router -> Clients
  for (auto client : m_clients) {
    painter.drawLine(
        client->mapTo(this, client->button()->rect().center()),
        m_routers[0]->mapTo(this, m_routers[0]->button()->rect().center()));
  }

  // // Connection Router -> DNS Server
  // painter.setPen(QPen(Qt::red, 4));
  // painter.drawLine(
  //     m_routers[0]->mapTo(this, m_routers[0]->button()->rect().center()),
  //     m_servers[0]->mapTo(this, m_servers[0]->button()->rect().center()));
}
