#include "server_dialog.h"
#include "ui_server_dialog.h"

Server_Dialog::Server_Dialog(ServerWidget *server, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server_Dialog),
    server(server)
{
    ui->setupUi(this);
    ui->domainLabel->setText(server->server()->domain());
    ui->ipLabel->setText(server->server()->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    ui->macLabel->setText(server->server()->getNetworkCard().getPhysicalAddress().getAddressAsString());
}

Server_Dialog::~Server_Dialog()
{
    delete ui;
}
