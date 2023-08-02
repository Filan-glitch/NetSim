#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Connections
    connect(ui->clientsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setClientsAmount(int)));
    connect(ui->serverSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setServerAmount(int)));}

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
}

quint8 SettingsDialog::getClientsAmount() const
{
    return clientsAmount;
}

quint8 SettingsDialog::getServerAmount() const
{
    return serverAmount;
}
