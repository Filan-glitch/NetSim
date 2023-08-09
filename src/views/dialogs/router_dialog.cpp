#include "router_dialog.h"
#include "ui_router_dialog.h"

Router_Dialog::Router_Dialog(RouterWidget* router, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Router_Dialog),
    router(router)
{
    ui->setupUi(this);
    ui->globalIPLabel->setText(router->router()->getGlobalIpAddress().getAddressAsDecString());
    ui->localIPLabel->setText(router->router()->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    ui->macLabel->setText(router->router()->getNetworkCard().getPhysicalAddress().getAddressAsString());
}

Router_Dialog::~Router_Dialog()
{
    delete ui;
}
