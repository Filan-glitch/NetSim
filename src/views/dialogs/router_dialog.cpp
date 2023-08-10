#include "router_dialog.h"
#include "ui_router_dialog.h"

Router_Dialog::Router_Dialog(RouterWidget* router, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Router_Dialog),
    router(router)
{
    ui->setupUi(this);
    ui->globalIPLabel->setText(router->router()->getGlobalIpAddress().toString());
    ui->localIPLabel->setText(router->router()->getNetworkCard().getNetworkAddress().toString());
    ui->macLabel->setText(router->router()->getNetworkCard().getPhysicalAddress().toString());

    for(auto& port : router->router()->getNAT().keys()) {
        ui->natList->addItem(router->router()->getGlobalIpAddress().toString() + " (" + QString::number(port.getPortNumber()) + ") <-> " + router->router()->getNAT().value(port).getIPAddress().toString() + " (" + QString::number(router->router()->getNAT().value(port).getPortNumber().getPortNumber()) + ")");
    }
    for(auto& nat : router->router()->getNAT2Port().keys()) {
        ui->natList->addItem(nat.getIPAddress().getAddressAsDecString() + " (" + QString::number(nat.getPortNumber().getPortNumber()) + ")" + " <-> " + router->router()->getGlobalIpAddress().getAddressAsDecString() + " (" + QString::number(router->router()->getNAT2Port().value(nat).getPortNumber()) + ")");
    }
    for(auto& ipAddress : router->router()->getMacTable().keys()) {
        ui->connectionsList->addItem(ipAddress.toString() + " -> " + router->router()->getMacTable().value(ipAddress).toString());
    }
    for(auto& cable : router->router()->getHostCable().keys()) {
        ui->cablesList->addItem("Cable to " + cable.toString());
    }
    for(auto& cable : router->router()->getRouterCable().keys()) {
        ui->cablesList->addItem("Cable to " + cable.toString());
    }
}

Router_Dialog::~Router_Dialog()
{
    delete ui;
}
