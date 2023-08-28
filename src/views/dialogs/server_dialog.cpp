#include "server_dialog.h"
#include "ui_server_dialog.h"

using namespace NetSim;

Server_Dialog::Server_Dialog(ServerWidget *server, QWidget *parent)
    : QDialog(parent), ui(new Ui::Server_Dialog), m_server(server) {
  ui->setupUi(this);
  // Skip if nullptr
  if (!server) {
    return;
  }
  // Set the labels
  ui->domainLabel->setText(server->server()->domain());
  ui->ipLabel->setText(
      server->server()->networkCard().networkAddress().toString());
  ui->macLabel->setText(
      server->server()->networkCard().physicalAddress().toString());
  // Set the processes list widget
  for (auto &process : server->server()->processTable()) {
    ui->processesList->addItem(process.toString());
  }
  // Set the domains list widget
  const auto &domainTable = server->server()->domainTable();
  for (auto it = domainTable.constBegin(); it != domainTable.constEnd(); ++it) {
    QString domain = it.key();
    QString value = it.value().toString();
    ui->domainsList->addItem(domain + " (" + value + ")");
  }
  if (server->server()->domainTable().empty()) {
    ui->domainsLabel->setVisible(false);
    ui->domainsList->setVisible(false);
  }
  // Set the connections list widget
  const auto &hostTable = server->server()->hostTable();
  for (auto it = hostTable.constBegin(); it != hostTable.constEnd(); ++it) {
    QString ipAddress = it.key().toString();
    QString value = it.value().toString();
    ui->connectionsList->addItem(ipAddress + " -> " + value);
  }
  // Set the cables list widget
  const auto &cables = server->server()->cables();
  for (auto it = cables.constBegin(); it != cables.constEnd(); ++it) {
    QString cable = it.key().toString();
    ui->cablesList->addItem("Cable to " + cable);
  }

  // Setting the geometry
  QRect rect = this->geometry();
  rect.setHeight(0);
  this->setGeometry(rect);
}

Server_Dialog::~Server_Dialog() { delete ui; }
