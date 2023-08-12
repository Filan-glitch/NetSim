#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

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

  ~SettingsDialog();

  quint8 clientsAmount() const;

  quint8 serversAmount() const;

  QList<QString> domains() const;

private slots:
  void setClientsAmount(int amount);

  void setServerAmount(int amount);

  void textChanged1(const QString &data);

  void textChanged2(const QString &data);

  void textChanged3(const QString &data);

  void textChanged4(const QString &data);

  void textChanged5(const QString &data);

private:
  Ui::SettingsDialog *ui;

  quint8 m_clientsAmount{1};

  quint8 m_serverAmount{1};

  QString m_domain1;

  QString m_domain2;

  QString m_domain3;

  QString m_domain4;

  QString m_domain5;

  bool allVisibleLineEditsFilled();
};
} // namespace NetSim

#endif // SETTINGSDIALOG_H
