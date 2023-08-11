#include "server_dialog.h"
#include "ui_server_dialog.h"

Server_Dialog::Server_Dialog(ServerWidget *server, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server_Dialog),
    server(server)
{
    ui->setupUi(this);
    ui->domainLabel->setText(server->server()->domain());
    ui->ipLabel->setText(server->server()->getNetworkCard().getNetworkAddress().toString());
    ui->macLabel->setText(server->server()->getNetworkCard().getPhysicalAddress().toString());
    for(auto& process : server->server()->getProcessTable()) {
        ui->processesList->addItem(process.toString());
    }
    const auto& domainTable = server->server()->getDomainTable();
    for (auto it = domainTable.constBegin(); it != domainTable.constEnd(); ++it) {
        QString domain = it.key();
        QString value = it.value().toString();
        ui->domainsList->addItem(domain + " (" + value + ")");
    }
    if(server->server()->getDomainTable().empty()) {
        ui->domainsLabel->setVisible(false);
        ui->domainsList->setVisible(false);
    }
    const auto& hostTable = server->server()->getHostTable();
    for (auto it = hostTable.constBegin(); it != hostTable.constEnd(); ++it) {
        QString ipAddress = it.key().toString();
        QString value = it.value().toString();
        ui->connectionsList->addItem(ipAddress + " -> " + value);
    }
    const auto& cables = server->server()->getCables();
    for (auto it = cables.constBegin(); it != cables.constEnd(); ++it) {
        QString cable = it.key().toString();
        ui->cablesList->addItem("Cable to " + cable);
    }

    QRect rect = this->geometry();
    rect.setHeight(0);
    this->setGeometry(rect);
}

Server_Dialog::~Server_Dialog()
{
    delete ui;
}
