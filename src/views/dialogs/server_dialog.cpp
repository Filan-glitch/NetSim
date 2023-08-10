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
    for(auto& domain : server->server()->getDomainTable().keys()) {
        ui->domainsList->addItem(domain + " (" + server->server()->getDomainTable().value(domain).toString() + ")");
    }
    if(server->server()->getDomainTable().empty()) {
        ui->domainsLabel->setVisible(false);
        ui->domainsList->setVisible(false);
    }
    for(auto& ipAddress : server->server()->getHostTable().keys()) {
        ui->connectionsList->addItem(ipAddress.toString() + " -> " + server->server()->getHostTable().value(ipAddress).toString());
    }
    for(auto& cable : server->server()->getCables().keys()) {
        ui->cablesList->addItem("Cable to " + cable.toString());
    }

    QRect rect = this->geometry();
    rect.setHeight(0);
    this->setGeometry(rect);
}

Server_Dialog::~Server_Dialog()
{
    delete ui;
}
