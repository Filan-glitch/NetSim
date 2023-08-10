#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "qlabel.h"
#include "qlineedit.h"
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

    QList<QString> domains() const;


private slots:
    void setClientsAmount(int amount);
    void setServerAmount(int amount);

    void on_domainLineEdit_1_textChanged(const QString &arg1);

    void on_domainLineEdit_2_textChanged(const QString &arg1);

    void on_domainLineEdit_3_textChanged(const QString &arg1);

    void on_domainLineEdit_4_textChanged(const QString &arg1);

    void on_domainLineEdit_5_textChanged(const QString &arg1);

private:
    Ui::SettingsDialog *ui;
    quint8 clientsAmount = 1;
    quint8 serverAmount = 1;
    QString m_domain1;
    QString m_domain2;
    QString m_domain3;
    QString m_domain4;
    QString m_domain5;
    bool allVisibleLineEditsFilled();
};

#endif // SETTINGSDIALOG_H
