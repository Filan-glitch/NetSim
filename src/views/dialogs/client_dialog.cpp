#include "client_dialog.h"
#include "ui_client_dialog.h"

Client_Dialog::Client_Dialog(ClientWidget* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Dialog),
    client(client)
{
    ui->setupUi(this);
    ui->nameLabel->setText(client->name());
    ui->ipLabel->setText(client->client()->getNetworkCard().getNetworkAddress().toString());
    ui->macLabel->setText(client->client()->getNetworkCard().getPhysicalAddress().toString());
    for(auto& process : client->client()->getProcessTable()) {
        ui->processesList->addItem(process.toString());
    }
    for(auto& domain : client->client()->getDomainTable().keys()) {
        ui->domainsList->addItem(domain + " (" + client->client()->getDomainTable().value(domain).toString() + ")");
    }
    for(auto& ipAddress : client->client()->getHostTable().keys()) {
        ui->connectionsList->addItem(ipAddress.toString() + " -> " + client->client()->getHostTable().value(ipAddress).toString());
    }
    for(auto& cable : client->client()->getCables().keys()) {
        ui->cablesList->addItem("Cable to " + cable.toString());
    }
}

Client_Dialog::~Client_Dialog()
{
    delete ui;
}

QString Client_Dialog::getURI() const
{
    return ui->pathLineEdit->text();
}

QString Client_Dialog::getDomain() const
{
    return ui->serverDomainLineEdit->text();
}

void Client_Dialog::on_serverDomainLineEdit_textChanged(const QString &arg1)
{
    if(ui->serverDomainLineEdit->text().size() > 0 && ui->pathLineEdit->text().size() > 0){
        ui->sendPushButton->setEnabled(true);
    }
    else{
        ui->sendPushButton->setEnabled(false);
    }
}


void Client_Dialog::on_pathLineEdit_textChanged(const QString &arg1)
{
    if(ui->serverDomainLineEdit->text().size() > 0 && ui->pathLineEdit->text().size() > 0){
        ui->sendPushButton->setEnabled(true);
    }
    else{
        ui->sendPushButton->setEnabled(false);
    }
}

