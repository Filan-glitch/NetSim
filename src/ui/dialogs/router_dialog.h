#ifndef ROUTER_DIALOG_H
#define ROUTER_DIALOG_H

#include "src/ui/widgets/routerwidget.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Router_Dialog;
}
QT_END_NAMESPACE

namespace NetSim {

class Router_Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Router_Dialog(RouterWidget *router, QWidget *parent = nullptr);

  ~Router_Dialog();

private:
  Ui::Router_Dialog *ui;

  RouterWidget *m_router{nullptr};
};
} // namespace NetSim

#endif // ROUTER_DIALOG_H
