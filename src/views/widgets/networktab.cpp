#include "networktab.h"
#include <QPainter>

NetworkTab::NetworkTab(QWidget *parent)
    : QWidget{parent}
{

}

void NetworkTab::addRouter(RouterWidget *router)
{
    routers.append(router);
}

void NetworkTab::addServer(ServerWidget *server)
{
    servers.append(server);
}

void NetworkTab::addClient(ClientWidget *client)
{
    clients.append(client);
}

void NetworkTab::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter{this};
    painter.setPen(QPen(Qt::black, 2));

    // Connections Server -> Router
    for (auto i = 0; i < servers.size(); ++i) {
        painter.drawLine(servers[i]->mapTo(this, servers[i]->button()->rect().center()), routers[i+1]->mapTo(this, routers[0]->button()->rect().center()));
    }

    // Connections Router -> Router
    for (auto router : routers) {
        if (router == routers[0]) continue;
        painter.drawLine(router->mapTo(this, router->button()->rect().center()), routers[0]->mapTo(this, routers[0]->button()->rect().center()));
    }

    // Connections Router -> Clients
    for (auto client : clients) {
        painter.drawLine(client->mapTo(this, client->button()->rect().center()), routers[0]->mapTo(this, routers[0]->button()->rect().center()));
    }
}
