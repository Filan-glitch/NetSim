#ifndef SERVER_DIALOG_H
#define SERVER_DIALOG_H

#include "src/views/widgets/serverwidget.h"
#include <QDialog>

namespace Ui {
class Server_Dialog;
}

class Server_Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Server_Dialog(ServerWidget *server, QWidget *parent = nullptr);

  ~Server_Dialog();

private:
  Ui::Server_Dialog *ui;

  ServerWidget *m_server;
};

#endif // SERVER_DIALOG_H
