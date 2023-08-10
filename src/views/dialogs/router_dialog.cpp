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

    for(auto& port : router->router()->getNAT().keys()) {
        ui->natList->addItem(router->router()->getGlobalIpAddress().getAddressAsDecString() + " (" + QString::number(port.getPortNumber()) + ") <-> " + router->router()->getNAT().value(port).getIPAddress().getAddressAsDecString() + " (" + QString::number(router->router()->getNAT().value(port).getPortNumber().getPortNumber()) + ")");
    }
    for(auto& ipAddress : router->router()->getMacTable().keys()) {
        ui->connectionsList->addItem(ipAddress.getAddressAsDecString() + " -> " + router->router()->getMacTable().value(ipAddress).getAddressAsString());
    }
    for(auto& cable : router->router()->getHostCable().keys()) {
        ui->cablesList->addItem("Cable to " + cable.getAddressAsString());
    }
    for(auto& cable : router->router()->getRouterCable().keys()) {
        ui->cablesList->addItem("Cable to " + cable.getAddressAsString());
    }
}

Router_Dialog::~Router_Dialog()
{
    delete ui;
}
