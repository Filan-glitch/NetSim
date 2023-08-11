#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include "src/network/client.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NetSim {
class ClientWidget;
}

class ClientWidget : public QWidget {
  Q_OBJECT
public:
  explicit ClientWidget(Client *client, const QString &name,
                        QWidget *parent = nullptr);

  Client *client();

  QPushButton *button() const;

  QString name() const;

private:
  Client *m_client;

  QPushButton *m_button;

  QLabel *m_nameLabel;

  QLabel *m_ipLabel;

  QLabel *m_macLabel;

  QVBoxLayout *m_layout;

private slots:
  void onButtonClicked();

signals:
  void clicked(ClientWidget *client);
};

#endif // CLIENTWIDGET_H
