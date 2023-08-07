#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Connections
    connect(ui->clientsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setClientsAmount(int)));
    connect(ui->serverSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setServerAmount(int)));

    ui->domainLabel_2->setVisible(false);
    ui->domainLineEdit_2->setVisible(false);
    ui->domainLabel_3->setVisible(false);
    ui->domainLineEdit_3->setVisible(false);
    ui->domainLabel_4->setVisible(false);
    ui->domainLineEdit_4->setVisible(false);
    ui->domainLabel_5->setVisible(false);
    ui->domainLineEdit_5->setVisible(false);

}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setClientsAmount(int amount)
{
    clientsAmount = static_cast<quint8>(amount);
}

void SettingsDialog::setServerAmount(int amount)
{
    serverAmount = static_cast<quint8>(amount);
    switch(amount) {
    case 1:
        ui->domainLabel_2->setVisible(false);
        ui->domainLineEdit_2->setVisible(false);
        ui->domainLabel_3->setVisible(false);
        ui->domainLineEdit_3->setVisible(false);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        break;
    case 2:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(false);
        ui->domainLineEdit_3->setVisible(false);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        break;
    case 3:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        break;
    case 4:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(true);
        ui->domainLineEdit_4->setVisible(true);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        break;
    case 5:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(true);
        ui->domainLineEdit_4->setVisible(true);
        ui->domainLabel_5->setVisible(true);
        ui->domainLineEdit_5->setVisible(true);
        break;
    }
}

quint8 SettingsDialog::getClientsAmount() const
{
    return clientsAmount;
}

quint8 SettingsDialog::getServerAmount() const
{
    return serverAmount;
}

void SettingsDialog::on_domainLineEdit_1_textChanged(const QString &arg1)
{
    m_domain1 = arg1;
}

void SettingsDialog::on_domainLineEdit_2_textChanged(const QString &arg1)
{
    m_domain2 = arg1;
}

void SettingsDialog::on_domainLineEdit_3_textChanged(const QString &arg1)
{
    m_domain3 = arg1;
}

void SettingsDialog::on_domainLineEdit_4_textChanged(const QString &arg1)
{
    m_domain4 = arg1;
}

void SettingsDialog::on_domainLineEdit_5_textChanged(const QString &arg1)
{
    m_domain5 = arg1;
}

QList<QString> SettingsDialog::domains() const {
    switch(serverAmount) {
    case 1:
        return QList<QString>() << m_domain1;
    case 2:
        return QList<QString>() << m_domain1 << m_domain2;
    case 3:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3;
    case 4:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3 << m_domain4;
    case 5:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3 << m_domain4 << m_domain5;
    }
}
