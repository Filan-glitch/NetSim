#ifndef CLIENT_DIALOG_H
#define CLIENT_DIALOG_H

#include "src/views/widgets/clientwidget.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client_Dialog;
}
QT_END_NAMESPACE

namespace NetSim {

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

  ClientWidget *m_client{nullptr};
};
} // namespace NetSim

#endif // CLIENT_DIALOG_H
