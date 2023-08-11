#ifndef CLIENT_DIALOG_H
#define CLIENT_DIALOG_H

#include "src/views/widgets/clientwidget.h"
#include <QDialog>

namespace Ui {
class Client_Dialog;
}

class Client_Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Client_Dialog(ClientWidget *client, QWidget *parent = nullptr);

  ~Client_Dialog();

  QString uri() const;

  QString domain() const;

private slots:
  void textChanged();

private:
  Ui::Client_Dialog *ui;

  ClientWidget *m_client;
};

#endif // CLIENT_DIALOG_H
