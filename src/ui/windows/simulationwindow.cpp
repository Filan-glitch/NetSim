#include "simulationwindow.h"
#include "src/management/packagedatabase.h"
#include "src/software/00_common/headerutil.h"
#include "src/ui/dialogs/about_dialog.h"
#include "src/ui/dialogs/client_dialog.h"
#include "src/ui/dialogs/router_dialog.h"
#include "src/ui/dialogs/server_dialog.h"
#include "src/ui/widgets/clientwidget.h"
#include "src/ui/widgets/networktab.h"
#include "src/ui/widgets/routerwidget.h"
#include "src/ui/widgets/serverwidget.h"
#include "ui_simulationwindow.h"
#include <QDesktopServices>
#include <QGridLayout>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QStringList>

using namespace NetSim;

SimulationWindow::SimulationWindow(SimulationManager *manager, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SimulationWindow), m_manager(manager) {
  // Initial Setup
  ui->setupUi(this);
  showFullScreen();
  setupNetwork(manager->praktikum());

  // Model Initialization
  m_packageModel =
      new PackageTableModel(PackageDatabase::instance()->packageList(), manager->praktikum(), this);
  m_manager->setPackages(m_packageModel);
  ui->packagesTableView->setModel(m_packageModel);
  ui->packagesTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
  ui->packagesTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->packagesTableView->verticalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  // TreeWidget Initialization
  m_treeWidget = new QTreeWidget(this);
  m_treeWidget->setColumnCount(1);
  m_treeWidget->setHeaderHidden(true);
  this->ui->packageTab->layout()->addWidget(m_treeWidget);

  // StatusBar
  m_simTimeLabel = new QLabel("00:00:00.0", this);
  ui->statusbar->setFixedHeight(30);
  ui->statusbar->addWidget(m_simTimeLabel);
  ui->statusbar->setSizeGripEnabled(false);

  // Connections
  connect(this->ui->actionDocumentation, &QAction::triggered, this,
          &SimulationWindow::openDocumentation);
  connect(this->ui->packagesTableView, &QTableView::doubleClicked, this,
          &SimulationWindow::updateTreeWidget);
  connect(this->ui->actionAbout_NetSim, &QAction::triggered, this,
          &SimulationWindow::about);

  // Timer
  startTimer(100);
}

SimulationWindow::~SimulationWindow() {
  delete ui;
  delete m_manager;
  delete PackageDatabase::instance();
}

void SimulationWindow::keyPressEvent(QKeyEvent *event) {
  // Adding the feature to close the window by pressing the escape key
  if (event->key() == Qt::Key_Escape) {
    close();
  }
}

void SimulationWindow::setupNetwork(Praktikum praktikum) {
  // Mainlayout
  auto mainLayout = new QGridLayout(this);

  // Adding the network tab to the tablist
  NetworkTab *networkTab = new NetworkTab(this);
  networkTab->setLayout(mainLayout);
  this->ui->tabWidget->insertTab(0, networkTab, QIcon(":/network.svg"),
                                 "Network");
  // Setting the current index, so the window starts right at this tab
  this->ui->tabWidget->setCurrentIndex(0);

  switch(praktikum) {
      case HTTP_Praktikum:
          {
              // Mainrouter
              RouterWidget* mainRouter = new RouterWidget(&(*m_manager->routers())[0], this);
              connect(mainRouter, &RouterWidget::clicked, this,
                      &SimulationWindow::routerDialog);
              mainLayout->addWidget(mainRouter, 2, 2);
              networkTab->addRouter(mainRouter);

              // Server
              ServerWidget* serverWidget = new ServerWidget(&(*m_manager->servers())[0], this);
              connect(serverWidget, &ServerWidget::clicked, this,
                      &SimulationWindow::serverDialog);
              mainLayout->addWidget(serverWidget, 2, 0);
              networkTab->addServer(serverWidget);

              // Serverrouter
              RouterWidget* serverRouter = new RouterWidget(&(*m_manager->routers())[1], this);
              connect(serverRouter, &RouterWidget::clicked, this,
                      &SimulationWindow::routerDialog);
              mainLayout->addWidget(serverRouter, 2, 1);
              networkTab->addRouter(serverRouter);

              // Client
              ClientWidget* clientWidget = new ClientWidget(&(*m_manager->clients())[0], "Client", this);
              connect(clientWidget, &ClientWidget::clicked, this,
                      &SimulationWindow::clientDialog);
              networkTab->addClient(clientWidget);
              mainLayout->addWidget(clientWidget, 2, 3);
              break;
          }
      case DNS_Praktikum:
          {
              // Mainrouter
              RouterWidget* mainRouter = new RouterWidget(&(*m_manager->routers())[0], this);
              connect(mainRouter, &RouterWidget::clicked, this,
                      &SimulationWindow::routerDialog);
              networkTab->addRouter(mainRouter);
              // DNS Server
              ServerWidget* dnsServer = new ServerWidget(&(*m_manager->servers())[0], this);
              connect(dnsServer, &ServerWidget::clicked, this,
                      &SimulationWindow::serverDialog);
              networkTab->addServer(dnsServer);
              break;
          }
      case UDP_Praktikum:
      case TCP_Praktikum:
      case ICMP_Praktikum:
      case IP_Praktikum:
      case DHCP_Praktikum:
      case ARP_Praktikum:
          break;
  }
}

void SimulationWindow::openDocumentation() {
  QDesktopServices::openUrl(
      QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}

void SimulationWindow::updateTreeWidget(const QModelIndex &index) {
  if (!m_packageModel->hasIndex(index.row(), index.column(), index.parent()))
    return;

  Package package = PackageDatabase::instance()->packageList()->at(
      PackageDatabase::instance()->packageList()->size() - index.row() - 1);

  // Clearing the tree widget
  this->m_treeWidget->clear();

  // Mac Header
  QTreeWidgetItem *macHeader =
      new QTreeWidgetItem(QStringList(QString("Ethernet II")));
  macHeader->addChild(new QTreeWidgetItem(
      macHeader,
      QStringList(QString("Destination: %1")
                      .arg(HeaderUtil::getMacAddress(package, false)))));
  macHeader->addChild(new QTreeWidgetItem(
      macHeader,
      QStringList(QString("Source: %1")
                      .arg(HeaderUtil::getMacAddress(package, true)))));
  macHeader->addChild(new QTreeWidgetItem(
      macHeader,
      QStringList(QString("Type: %1").arg(HeaderUtil::getEtherType(package)))));

  this->m_treeWidget->addTopLevelItem(macHeader);

  // IP Header
  QTreeWidgetItem *ipHeader =
      new QTreeWidgetItem(QStringList(QString("Internet Protocol Version 4")));
  ipHeader->addChild(
      new QTreeWidgetItem(ipHeader, QStringList(QString("Version: 4"))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader, QStringList(QString("Header Length: %1")
                                .arg(HeaderUtil::getIPHeaderLength(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader, QStringList(QString("Differentiated Services Field: %1")
                                .arg(HeaderUtil::getIPTOS(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader, QStringList(QString("Total Length: %1")
                                .arg(HeaderUtil::getIPTotalLength(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader,
      QStringList(QString("Identification: %1")
                      .arg(HeaderUtil::getIPIdentification(package)))));
  QTreeWidgetItem *ipFlags = new QTreeWidgetItem(
      ipHeader,
      QStringList(QString("Flags: %1").arg(HeaderUtil::getIPFlags(package))));
  ipHeader->addChild(ipFlags);
  ipFlags->addChild(new QTreeWidgetItem(
      ipFlags, QStringList(QString("Reserved Bit: Not Set"))));
  ipFlags->addChild(new QTreeWidgetItem(
      ipFlags, QStringList(QString("Don't Fragment: %1")
                               .arg(HeaderUtil::getIPFlag(
                                   package, NetSim::IPFlag::DF)))));
  ipFlags->addChild(new QTreeWidgetItem(
      ipFlags, QStringList(QString("More Fragments: %1")
                               .arg(HeaderUtil::getIPFlag(
                                   package, NetSim::IPFlag::MF)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader,
      QStringList(QString("Fragment Offset: %1")
                      .arg(HeaderUtil::getIPFragmentOffset(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader,
      QStringList(
          QString("Time To Live: %1").arg(HeaderUtil::getIPTTL(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader, QStringList(QString("Protocol: %1")
                                .arg(HeaderUtil::getIPNextProtocol(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader, QStringList(QString("Header Checksum: %1")
                                .arg(HeaderUtil::getIPChecksum(package)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader,
      QStringList(QString("Source Address: %1")
                      .arg(HeaderUtil::getIPAddress(package, true)))));
  ipHeader->addChild(new QTreeWidgetItem(
      ipHeader,
      QStringList(QString("Destination Address: %1")
                      .arg(HeaderUtil::getIPAddress(package, false)))));

  this->m_treeWidget->addTopLevelItem(ipHeader);

  // Transport Header (if existant)
  QTreeWidgetItem *transportHeader;
  if (HeaderUtil::getIPNextProtocol(package) == "TCP") {
    transportHeader = new QTreeWidgetItem(
        QStringList(QString("Transmission Control Protocol")));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Source Port: %1")
                        .arg(HeaderUtil::getPort(package, true)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Destination Port: %1")
                        .arg(HeaderUtil::getPort(package, false)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Sequence Number: %1")
                        .arg(HeaderUtil::getTCPSequenceNumber(package)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Acknowledgement Number: %1")
                .arg(HeaderUtil::getTCPAcknowledgementNumber(package)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Header Length: %1")
                        .arg(HeaderUtil::getTCPHeaderLength(package)))));
    QTreeWidgetItem *tcpFlags = new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Flags: %1").arg(HeaderUtil::getTCPFlags(package))));
    transportHeader->addChild(tcpFlags);
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Reserved: Not Set"))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Accurate ECN: Not Set"))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Congestion Window Reduced: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::CWR)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("ECN-Echo: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::ECE)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Urgent: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::URG)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Acknowledgment: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::ACK)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Push: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::PSH)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Reset: %1")
                                  .arg(HeaderUtil::getTCPFlag(
                                      package, NetSim::TCPFlag::RST)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Syn: %1").arg(
                      HeaderUtil::getTCPFlag(package, NetSim::TCPFlag::SYN)))));
    tcpFlags->addChild(new QTreeWidgetItem(
        tcpFlags, QStringList(QString("Fin: %1").arg(
                      HeaderUtil::getTCPFlag(package, NetSim::TCPFlag::FIN)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Window: %1").arg(HeaderUtil::getTCPWindow(package)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Checksum: %1").arg(HeaderUtil::getTCPChecksum(package)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Urgent Pointer: %1")
                        .arg(HeaderUtil::getTCPUrgentPointer(package)))));

  } else {
    transportHeader =
        new QTreeWidgetItem(QStringList(QString("User Datagram Protocol")));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Source Port: %1")
                        .arg(HeaderUtil::getPort(package, true)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(QString("Destination Port: %1")
                        .arg(HeaderUtil::getPort(package, false)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Length: %1").arg(HeaderUtil::getUDPLength(package)))));
    transportHeader->addChild(new QTreeWidgetItem(
        transportHeader,
        QStringList(
            QString("Checksum: %1").arg(HeaderUtil::getUDPChecksum(package)))));
  }

  this->m_treeWidget->addTopLevelItem(transportHeader);

  // Application Header (if existant)
  if (HeaderUtil::getTopProtocol(package) == NetSim::HeaderType::HTTP) {
    if (HeaderUtil::getHTTPIsResponse(package)) {
      QTreeWidgetItem *applicationHeader = new QTreeWidgetItem(
          QStringList(QString("Hypertext Transfer Protocol")));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Response Version: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Version")))));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Status Code: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Code")))));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Response Phrase: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Phrase")))));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Content-Type: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Content-Type")))));
      this->m_treeWidget->addTopLevelItem(applicationHeader);

      if (HeaderUtil::getHTTPAttribute(package, "Code") == "200") {
        QTreeWidgetItem *contentHeader = new QTreeWidgetItem(QStringList(
            QString("Line-based text data: %1")
                .arg(HeaderUtil::getHTTPAttribute(package, "Content-Type"))));
        contentHeader->addChild(
            new QTreeWidgetItem(contentHeader, QStringList(package.content())));
        this->m_treeWidget->addTopLevelItem(contentHeader);
      }
    } else {
      QTreeWidgetItem *applicationHeader = new QTreeWidgetItem(
          QStringList(QString("Hypertext Transfer Protocol")));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Request Method: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Method")))));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader,
          QStringList(QString("Request URI: %1")
                          .arg(HeaderUtil::getHTTPAttribute(package, "URI")))));
      applicationHeader->addChild(new QTreeWidgetItem(
          applicationHeader, QStringList(QString("Request Version: %1")
                                             .arg(HeaderUtil::getHTTPAttribute(
                                                 package, "Version")))));

      this->m_treeWidget->addTopLevelItem(applicationHeader);
    }

  } else if (HeaderUtil::getTopProtocol(package) == NetSim::HeaderType::DNS) {
    QTreeWidgetItem *applicationHeader =
        new QTreeWidgetItem(QStringList(QString("Domain Name System")));
    applicationHeader->addChild(new QTreeWidgetItem(
        applicationHeader,
        QStringList(
            QString("Transaction ID: %1").arg(HeaderUtil::getDNSID(package)))));
    QTreeWidgetItem *dnsFlags = new QTreeWidgetItem(
        applicationHeader,
        QStringList(
            QString("Flags: %1").arg(HeaderUtil::getDNSFlags(package))));
    applicationHeader->addChild(dnsFlags);
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags, QStringList(QString("Response: %1")
                                  .arg(HeaderUtil::getDNSFlag(
                                      package, NetSim::DNSFlag::RESPONSE)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags, QStringList(QString("Opcode: %1")
                                  .arg(HeaderUtil::getDNSFlag(
                                      package, NetSim::DNSFlag::OPCODE)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags,
        QStringList(QString("Authoritative: %1")
                        .arg(HeaderUtil::getDNSFlag(
                            package, NetSim::DNSFlag::AUTHORITATIVE)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags, QStringList(QString("Truncated: %1")
                                  .arg(HeaderUtil::getDNSFlag(
                                      package, NetSim::DNSFlag::TRUNCATED)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags,
        QStringList(QString("Recursion Desired: %1")
                        .arg(HeaderUtil::getDNSFlag(
                            package, NetSim::DNSFlag::RECURSION_DESIRED)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags,
        QStringList(QString("Recursion Available: %1")
                        .arg(HeaderUtil::getDNSFlag(
                            package, NetSim::DNSFlag::RECURSION_AVAILABLE)))));
    dnsFlags->addChild(
        new QTreeWidgetItem(dnsFlags, QStringList(QString("Z: reserved (0)"))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags,
        QStringList(QString("Answer authenticated: %1")
                        .arg(HeaderUtil::getDNSFlag(
                            package, NetSim::DNSFlag::ANSWER_AUTHENTICATED)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags,
        QStringList(
            QString("Non-authenticated data: %1")
                .arg(HeaderUtil::getDNSFlag(
                    package, NetSim::DNSFlag::NON_AUTHENTICATED_DATA)))));
    dnsFlags->addChild(new QTreeWidgetItem(
        dnsFlags, QStringList(QString("Reply code: %1")
                                  .arg(HeaderUtil::getDNSFlag(
                                      package, NetSim::DNSFlag::REPLY_CODE)))));
    applicationHeader->addChild(new QTreeWidgetItem(
        applicationHeader,
        QStringList(QString("Questions: %1")
                        .arg(HeaderUtil::getDNSQuestions(package)))));
    applicationHeader->addChild(new QTreeWidgetItem(
        applicationHeader,
        QStringList(QString("Answer RRs: %1")
                        .arg(HeaderUtil::getDNSAnswerRRs(package)))));

    QTreeWidgetItem *queriesItems =
        new QTreeWidgetItem(applicationHeader, QStringList(QString("Queries")));
    applicationHeader->addChild(queriesItems);
    for (auto i = 0; i < HeaderUtil::getDNSQuestions(package).toInt(); i++) {
      QTreeWidgetItem *query = new QTreeWidgetItem(
          queriesItems, QStringList(HeaderUtil::getDNSQuery(package, i)));
      query->addChild(new QTreeWidgetItem(
          query, QStringList(QString("Name: %1")
                                 .arg(HeaderUtil::getDNSQuery(
                                     package, i, NetSim::RRAttribute::NAME)))));
      query->addChild(new QTreeWidgetItem(
          query, QStringList(QString("Type: %1")
                                 .arg(HeaderUtil::getDNSQuery(
                                     package, i, NetSim::RRAttribute::TYPE)))));
      query->addChild(new QTreeWidgetItem(
          query,
          QStringList(QString("Class: %1")
                          .arg(HeaderUtil::getDNSQuery(
                              package, i, NetSim::RRAttribute::CLASS)))));
      queriesItems->addChild(query);
    }

    QTreeWidgetItem *answersItems =
        new QTreeWidgetItem(applicationHeader, QStringList(QString("Answers")));
    applicationHeader->addChild(answersItems);
    for (auto i = 0; i < HeaderUtil::getDNSAnswerRRs(package).toInt(); i++) {
      QTreeWidgetItem *answer = new QTreeWidgetItem(
          answersItems, QStringList(HeaderUtil::getDNSAnswer(package, i)));
      answer->addChild(new QTreeWidgetItem(
          answer,
          QStringList(QString("Name: %1")
                          .arg(HeaderUtil::getDNSAnswer(
                              package, i, NetSim::RRAttribute::NAME)))));
      answer->addChild(new QTreeWidgetItem(
          answer,
          QStringList(QString("Type: %1")
                          .arg(HeaderUtil::getDNSAnswer(
                              package, i, NetSim::RRAttribute::TYPE)))));
      answer->addChild(new QTreeWidgetItem(
          answer,
          QStringList(QString("Class: %1")
                          .arg(HeaderUtil::getDNSAnswer(
                              package, i, NetSim::RRAttribute::CLASS)))));
      answer->addChild(new QTreeWidgetItem(
          answer, QStringList(QString("Time to live: %1")
                                  .arg(HeaderUtil::getDNSAnswer(
                                      package, i, NetSim::RRAttribute::TTL)))));
      answer->addChild(new QTreeWidgetItem(
          answer,
          QStringList(QString("Data length: %1")
                          .arg(HeaderUtil::getDNSAnswer(
                              package, i, NetSim::RRAttribute::DATA_LENGTH)))));
      answer->addChild(new QTreeWidgetItem(
          answer,
          QStringList(QString("Address: %1")
                          .arg(HeaderUtil::getDNSAnswer(
                              package, i, NetSim::RRAttribute::DATA)))));
      queriesItems->addChild(answer);
    }

    this->m_treeWidget->addTopLevelItem(applicationHeader);
  }
}

void SimulationWindow::timerEvent(QTimerEvent *event) {
  m_simTimeLabel->setText(
      QTime::fromString(m_simTimeLabel->text(), "hh:mm:ss.z")
          .addMSecs(100)
          .toString("hh:mm:ss.z"));
}

void SimulationWindow::about() {
  About_Dialog aboutDialog(this);
  aboutDialog.exec();
}

void SimulationWindow::clientDialog(ClientWidget *client) {
  Client_Dialog clientDialog(client, this);
  if (clientDialog.exec() == QDialog::Accepted) {
    client->client()->execDomainResolution(clientDialog.domain());
    if (client->client()->domainTable().contains(clientDialog.domain())) {
      client->client()->execHandShake(
          client->client()->domainTable().value(clientDialog.domain()));
      client->client()->execHTTPRequest(
          client->client()->domainTable().value(clientDialog.domain()),
          clientDialog.uri());
      client->client()->execCloseConnection(
          client->client()->domainTable().value(clientDialog.domain()));
      qInfo() << "All package transfers were successful.";
      QMessageBox box(this);
      box.setText("All packages were sent. Please check the packages tab for "
                  "more information.");
      box.setIcon(QMessageBox::Information);
      box.addButton(QMessageBox::Ok);
      box.exec();
    } else {
      qDebug() << "DNS resolution failed.";
      QMessageBox box(this);
      box.setText(
          "DNS resolution failed. Please check the domain name and try again.");
      box.setIcon(QMessageBox::Warning);
      box.addButton("OK", QMessageBox::AcceptRole);
      box.exec();
    }
  }
}

void SimulationWindow::routerDialog(RouterWidget *router) {
  Router_Dialog routerDialog(router, this);
  routerDialog.exec();
}

void SimulationWindow::serverDialog(ServerWidget *server) {
  Server_Dialog serverDialog(server, this);
  serverDialog.exec();
}
