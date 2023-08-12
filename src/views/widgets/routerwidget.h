#ifndef ROUTERWIDGET_H
#define ROUTERWIDGET_H

#include "qlabel.h"
#include "src/network/router.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace NetSim {

class RouterWidget : public QWidget {
  Q_OBJECT
public:
  explicit RouterWidget(Router *router, QWidget *parent = nullptr);

  Router *router();

  QPushButton *button() const;

private:
  Router *m_router;

  QPushButton *m_button;

  QLabel *m_localIpLabel;

  QLabel *m_globalIpLabel;

  QLabel *m_macLabel;

  QVBoxLayout *m_layout;

private slots:
  void onButtonClicked();

signals:
  void clicked(RouterWidget *router);
};
} // namespace NetSim

#endif // ROUTERWIDGET_H
