#include "client_dialog.h"
#include "ui_client_dialog.h"

Client_Dialog::Client_Dialog(ClientWidget* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Dialog),
    client(client)
{
    ui->setupUi(this);
    ui->nameLabel->setText(client->name());
    ui->ipLabel->setText(client->client()->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    ui->macLabel->setText(client->client()->getNetworkCard().getPhysicalAddress().getAddressAsString());
    for(auto& process : client->client()->getProcessTable()) {
        ui->processesList->addItem(process.toString());
    }
    for(auto& domain : client->client()->getDomainTable().keys()) {
        ui->domainsList->addItem(domain + " (" + client->client()->getDomainTable().value(domain).getAddressAsDecString() + ")");
    }
    for(auto& ipAddress : client->client()->getHostTable().keys()) {
        ui->connectionsList->addItem(ipAddress.getAddressAsDecString() + " -> " + client->client()->getHostTable().value(ipAddress).getAddressAsString());
    }
    for(auto& cable : client->client()->getCables().keys()) {
        ui->cablesList->addItem("Cable to " + cable.getAddressAsString());
    }

    connect(ui->serverDomainLineEdit, &QLineEdit::textChanged, this, &Client_Dialog::textChanged);
    connect(ui->pathLineEdit, &QLineEdit::textChanged, this, &Client_Dialog::textChanged);
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

void Client_Dialog::textChanged()
{
    if(ui->serverDomainLineEdit->text().size() > 0 && ui->pathLineEdit->text().size() > 0){
        ui->sendPushButton->setEnabled(true);
    }
    else{
        ui->sendPushButton->setEnabled(false);
    }
}



