#ifndef SERVER_DIALOG_H
#define SERVER_DIALOG_H

#include "src/ui/widgets/serverwidget.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Server_Dialog;
}
QT_END_NAMESPACE

namespace NetSim {

class Server_Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Server_Dialog(ServerWidget *server, QWidget *parent = nullptr);

  ~Server_Dialog();

private:
  Ui::Server_Dialog *ui;

  ServerWidget *m_server{nullptr};
};
} // namespace NetSim

#endif // SERVER_DIALOG_H
