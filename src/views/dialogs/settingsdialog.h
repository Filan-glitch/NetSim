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
