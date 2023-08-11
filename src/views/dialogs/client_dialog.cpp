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
    const auto& domainTable = client->client()->getDomainTable();
    for (auto it = domainTable.constBegin(); it != domainTable.constEnd(); ++it) {
        QString domain = it.key();
        QString value = it.value().toString();
        ui->domainsList->addItem(domain + " (" + value + ")");
    }
    const auto& hostTable = client->client()->getHostTable();
    for (auto it = hostTable.constBegin(); it != hostTable.constEnd(); ++it) {
        QString ipAddress = it.key().toString();
        QString value = it.value().toString();
        ui->connectionsList->addItem(ipAddress + " -> " + value);
    }
    const auto& cables = client->client()->getCables();
    for (auto it = cables.constBegin(); it != cables.constEnd(); ++it) {
        QString cable = it.key().toString();
        ui->cablesList->addItem("Cable to " + cable);
    }


    QRect rect = this->geometry();
    rect.setHeight(0);
    this->setGeometry(rect);

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



