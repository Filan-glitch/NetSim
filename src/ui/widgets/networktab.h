#ifndef NETWORKTAB_H
#define NETWORKTAB_H

#include "src/ui/widgets/clientwidget.h"
#include "src/ui/widgets/routerwidget.h"
#include "src/ui/widgets/serverwidget.h"
#include <QWidget>

namespace NetSim {

class NetworkTab : public QWidget {
  Q_OBJECT
public:
  explicit NetworkTab(QWidget *parent = nullptr);

  void addRouter(RouterWidget *router);

  void addServer(ServerWidget *server);

  void addClient(ClientWidget *client);

  QList<RouterWidget *> routers() const;

  QList<ServerWidget *> servers() const;

  QList<ClientWidget *> clients() const;

private:
  QList<RouterWidget *> m_routers;

  QList<ServerWidget *> m_servers;

  QList<ClientWidget *> m_clients;

protected:
  virtual void paintEvent(QPaintEvent *event) override;
};
} // namespace NetSim

#endif // NETWORKTAB_H
