#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    quint8 getClientsAmount() const;
    quint8 getServerAmount() const;

private slots:
    void setClientsAmount(int amount);
    void setServerAmount(int amount);

private:
    Ui::SettingsDialog *ui;
    quint8 clientsAmount;
    quint8 serverAmount;
};

#endif // SETTINGSDIALOG_H
