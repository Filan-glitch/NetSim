#ifndef NETWORKTAB_H
#define NETWORKTAB_H

#include "src/views/widgets/clientwidget.h"
#include "src/views/widgets/routerwidget.h"
#include "src/views/widgets/serverwidget.h"
#include <QWidget>

class NetworkTab : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkTab(QWidget *parent = nullptr);
    void addRouter(RouterWidget* router);
    void addServer(ServerWidget* server);
    void addClient(ClientWidget* client);
    QList<RouterWidget*> getRouters() const;
    QList<ServerWidget*> getServers() const;
    QList<ClientWidget*> getClients() const;

private:
    QList<RouterWidget*> routers;
    QList<ServerWidget*> servers;
    QList<ClientWidget*> clients;

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // NETWORKTAB_H
