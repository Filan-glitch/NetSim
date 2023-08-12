#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class About_Dialog;
}
QT_END_NAMESPACE

namespace NetSim {

class About_Dialog : public QDialog {
  Q_OBJECT

public:
  explicit About_Dialog(QWidget *parent = nullptr);

  ~About_Dialog();

private:
  Ui::About_Dialog *ui;
};
} // namespace NetSim

#endif // ABOUT_DIALOG_H
