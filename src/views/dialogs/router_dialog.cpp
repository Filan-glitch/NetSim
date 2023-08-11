#include "router_dialog.h"
#include "ui_router_dialog.h"

Router_Dialog::Router_Dialog(RouterWidget *router, QWidget *parent)
    : QDialog(parent), ui(new Ui::Router_Dialog), m_router(router) {
  ui->setupUi(this);
  ui->globalIPLabel->setText(router->router()->globalIpAddress().toString());
  ui->localIPLabel->setText(
      router->router()->networkCard().networkAddress().toString());
  ui->macLabel->setText(
      router->router()->networkCard().physicalAddress().toString());

  const auto &natTable = router->router()->NAT();
  for (auto it = natTable.constBegin(); it != natTable.constEnd(); ++it) {
    const auto &port = it.key();
    const auto &entry = it.value();
    ui->natList->addItem(router->router()->globalIpAddress().toString() + " (" +
                         QString::number(port.portNumber()) + ") <-> " +
                         entry.address().toString() + " (" +
                         QString::number(entry.port().portNumber()) + ")");
  }
  const auto &macTable = router->router()->macTable();
  for (auto it = macTable.constBegin(); it != macTable.constEnd(); ++it) {
    QString ipAddress = it.key().toString();
    QString value = it.value().toString();
    ui->connectionsList->addItem(ipAddress + " -> " + value);
  }
  const auto &hostCables = router->router()->hostCable();
  for (auto it = hostCables.constBegin(); it != hostCables.constEnd(); ++it) {
    QString cable = it.key().toString();
    ui->cablesList->addItem("Cable to " + cable);
  }
  const auto &routerCables = router->router()->routerCable();
  for (auto it = routerCables.constBegin(); it != routerCables.constEnd();
       ++it) {
    QString cable = it.key().toString();
    ui->cablesList->addItem("Cable to " + cable);
  }

  QRect rect = this->geometry();
  rect.setHeight(0);
  this->setGeometry(rect);
}

Router_Dialog::~Router_Dialog() { delete ui; }
