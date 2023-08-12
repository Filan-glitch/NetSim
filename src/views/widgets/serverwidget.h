#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include "src/network/server.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NetSim {

class ServerWidget : public QWidget {
  Q_OBJECT
public:
  explicit ServerWidget(Server *server, QWidget *parent = nullptr);

  ~ServerWidget();

  Server *server();

  QPushButton *button() const;

private:
  Server *m_server;

  QPushButton *m_button;

  QLabel *m_domainLabel;

  QLabel *m_ipLabel;

  QLabel *m_macLabel;

  QVBoxLayout *m_layout;

private slots:
  void onButtonClicked();

signals:
  void clicked(ServerWidget *server);
};
} // namespace NetSim

#endif // SERVERWIDGET_H
