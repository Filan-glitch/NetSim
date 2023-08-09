#include "client_dialog.h"
#include "ui_client_dialog.h"

Client_Dialog::Client_Dialog(ClientWidget* client, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Dialog),
    client(client)
{
    ui->setupUi(this);
    ui->ipLabel->setText(client->client()->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    ui->macLabel->setText(client->client()->getNetworkCard().getPhysicalAddress().getAddressAsString());
}

Client_Dialog::~Client_Dialog()
{
    delete ui;
}
