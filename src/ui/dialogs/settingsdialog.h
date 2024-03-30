#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "src/management/simulationmanager.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsDialog;
}
QT_END_NAMESPACE

namespace NetSim {

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr);

  Praktikum praktikum() const;

  ~SettingsDialog();

public slots:
  void onhttpRadioButtonChecked();
  void ondnsRadioButtonChecked();
  void onudpRadioButtonChecked();
  void ontcpRadioButtonChecked();
  void onicmpRadioButtonChecked();
  void onipRadioButtonChecked();
  void ondhcpRadioButtonChecked();
  void onarpRadioButtonChecked();


private:
  Ui::SettingsDialog *ui;


};
} // namespace NetSim

#endif // SETTINGSDIALOG_H
