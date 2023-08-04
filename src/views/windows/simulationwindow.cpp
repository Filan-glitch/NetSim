#include "simulationwindow.h"
#include "src/protocols/headerutil.h"
#include "src/views/widgets/clientwidget.h"
#include "src/views/widgets/networktab.h"
#include "src/views/widgets/serverwidget.h"
#include "src/views/widgets/routerwidget.h"
#include "src/management/packagedatabase.h"
#include "ui_simulationwindow.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QGridLayout>
#include <QStringList>

SimulationWindow::SimulationWindow(SimulationManager *manager, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationWindow),
    manager(manager)
{
    //Initial Setup
    ui->setupUi(this);
    showFullScreen();
    setupNetwork();

    //Model Initialization
    m_packageModel = new PackageTableModel(PackageDatabase::instance()->packageList(), this);
    ui->packagesTableView->setModel(m_packageModel);
    ui->packagesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //TreeWidget Initialization
    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setColumnCount(1);
    m_treeWidget->setHeaderHidden(true);
    this->ui->packageTab->layout()->addWidget(m_treeWidget);

    //Connections
    connect(this->ui->actionDocumentation, &QAction::triggered, this, &SimulationWindow::openDocumentation);
    connect(this->ui->packagesTableView, &QTableView::doubleClicked, this, &SimulationWindow::updateTreeWidget);

}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void SimulationWindow::setupNetwork()
{
    // Mainlayout
    auto mainLayout = new QGridLayout(this);
    NetworkTab *networkTab = new NetworkTab(this);
    networkTab->setLayout(mainLayout);
    this->ui->tabWidget->insertTab(0, networkTab, QIcon(":/network.svg"), "Network");

    // Mainrouter
    auto mainRouter = new RouterWidget(this->manager->getRouters().at(0), this);
    switch(this->manager->getClientsAmount()) {
    case 1:
        mainLayout->addWidget(mainRouter, 0, 3);
        break;
    case 2:
    case 3:
        mainLayout->addWidget(mainRouter, 2, 3);
        break;
    case 4:
    case 5:
        mainLayout->addWidget(mainRouter, 2, 3);
        break;
    }
    networkTab->addRouter(mainRouter);

    for(auto i = 0; i < manager->getServerAmount(); i++) {
        ServerWidget* serverWidget = new ServerWidget(manager->getServer().at(i), this);
        mainLayout->addWidget(serverWidget, i, 0);
        networkTab->addServer(serverWidget);
    }

    for(auto i = 1; i <= manager->getServerAmount(); i++) {
        RouterWidget* routerWidget = new RouterWidget(manager->getRouters().at(i), this);
        mainLayout->addWidget(routerWidget, i - 1, 1);
        networkTab->addRouter(routerWidget);
    }

    for(auto i = 0; i < manager->getClientsAmount(); i++) {
        ClientWidget* clientWidget = new ClientWidget(manager->getClients().at(i), this);
        mainLayout->addWidget(clientWidget, i, 4);
        networkTab->addClient(clientWidget);
    }
    this->ui->tabWidget->setCurrentIndex(0);
}


void SimulationWindow::openDocumentation() {
    QDesktopServices::openUrl(QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}

void SimulationWindow::updateTreeWidget(const QModelIndex &index)
{
    if (!m_packageModel->hasIndex(index.row(), index.column(), index.parent())) return;

    Package package = PackageDatabase::instance()->packageList()->at(PackageDatabase::instance()->packageList()->size() - index.row() - 1);

    this->m_treeWidget->clear();

    // Mac Header
    QTreeWidgetItem *macHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("Ethernet II")));
    macHeader->addChild(new QTreeWidgetItem(macHeader, QStringList(QString("Destination: %1").arg(HeaderUtil::getMacAddress(package, false)))));
    macHeader->addChild(new QTreeWidgetItem(macHeader, QStringList(QString("Source: %1").arg(HeaderUtil::getMacAddress(package, true)))));
    macHeader->addChild(new QTreeWidgetItem(macHeader, QStringList(QString("Type: %1").arg(HeaderUtil::getEtherType(package)))));

    this->m_treeWidget->addTopLevelItem(macHeader);

    // IP Header
    QTreeWidgetItem *ipHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("Internet Protocol Version 4")));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Version: 4"))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Header Length: %1").arg(HeaderUtil::getIPHeaderLength(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Differentiated Services Field: %1").arg(HeaderUtil::getIPTOS(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Total Length: %1").arg(HeaderUtil::getIPTotalLength(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Identification: %1").arg(HeaderUtil::getIPIdentification(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Don't Fragment: %1").arg(HeaderUtil::getIPFlag(package, "DF")))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("More Fragments: %1").arg(HeaderUtil::getIPFlag(package, "MF")))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Fragment Offset: %1").arg(HeaderUtil::getIPFragmentOffset(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Time To Live: %1").arg(HeaderUtil::getIPTTL(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Protocol: %1").arg(HeaderUtil::getIPNextProtocol(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Header Checksum: %1").arg(HeaderUtil::getIPChecksum(package)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Source Address: %1").arg(HeaderUtil::getIPAddress(package, true)))));
    ipHeader->addChild(new QTreeWidgetItem(ipHeader, QStringList(QString("Destination Address: %1").arg(HeaderUtil::getIPAddress(package, false)))));

    this->m_treeWidget->addTopLevelItem(ipHeader);

    // Transport Header (if existant)
    QTreeWidgetItem* transportHeader;
    if(HeaderUtil::getIPNextProtocol(package) == "TCP") {
        transportHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("Transmission Control Protocol")));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Source Port: %1").arg(HeaderUtil::getPort(package, true)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Destination Port: %1").arg(HeaderUtil::getPort(package, false)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Sequence Number: %1").arg(HeaderUtil::getTCPSequenceNumber(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Acknowledgement Number: %1").arg(HeaderUtil::getTCPAcknowledgementNumber(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Header Length: %1").arg(HeaderUtil::getTCPHeaderLength(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("FLAG: Acknowledgment: %1").arg(HeaderUtil::getTCPFlag(package, "ACK")))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("FLAG: Reset: %1").arg(HeaderUtil::getTCPFlag(package, "RST")))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("FLAG: Syn: %1").arg(HeaderUtil::getTCPFlag(package, "SYN")))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("FLAG: Fin: %1").arg(HeaderUtil::getTCPFlag(package, "FIN")))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Window: %1").arg(HeaderUtil::getTCPWindow(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Checksum: %1").arg(HeaderUtil::getTCPChecksum(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Urgent Pointer: %1").arg(HeaderUtil::getTCPUrgentPointer(package)))));

    } else {
        transportHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("User Datagram Protocol")));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Source Port: %1").arg(HeaderUtil::getPort(package, true)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Destination Port: %1").arg(HeaderUtil::getPort(package, false)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Length: %1").arg(HeaderUtil::getUDPLength(package)))));
        transportHeader->addChild(new QTreeWidgetItem(transportHeader, QStringList(QString("Checksum: %1").arg(HeaderUtil::getUDPChecksum(package)))));
    }


    this->m_treeWidget->addTopLevelItem(transportHeader);

    // Application Header (if existant)
    if(HeaderUtil::getApplicationProtocol(package) == HeaderType::HTTP) {
        QTreeWidgetItem* applicationHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("Hypertext Transfer Protocol")));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("%1 %2 %3"))));

        this->m_treeWidget->addTopLevelItem(applicationHeader);
    } else if (HeaderUtil::getApplicationProtocol(package) == HeaderType::DNS) {
        QTreeWidgetItem* applicationHeader = new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("Domain Name System")));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Transaction ID: %1").arg(HeaderUtil::getDNSID(package)))));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Flags: %1").arg(HeaderUtil::getDNSFlag(package)))));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Questions: %1").arg(HeaderUtil::getDNSQuestions(package)))));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Answer RRs: %1").arg(HeaderUtil::getDNSAnswerRRs(package)))));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Authority RRs: %1").arg(HeaderUtil::getDNSAuthorityRRs(package)))));
        applicationHeader->addChild(new QTreeWidgetItem(applicationHeader, QStringList(QString("Additional RRs: %1").arg(HeaderUtil::getDNSAdditionalRRs(package)))));
        QTreeWidgetItem* queriesItem = new QTreeWidgetItem(applicationHeader, QStringList(QString("Queries")));
        applicationHeader->addChild(queriesItem);
        for (auto i = 0; i < HeaderUtil::getDNSQuestions(package).toInt(); i++) {
            queriesItem->addChild(new QTreeWidgetItem(queriesItem, QStringList(HeaderUtil::getDNSQuery(package, i))));
        }

        QTreeWidgetItem* answersItem = new QTreeWidgetItem(applicationHeader, QStringList(QString("Answers")));
        applicationHeader->addChild(answersItem);
        for (auto i = 0; i < HeaderUtil::getDNSAnswerRRs(package).toInt(); i++) {
            queriesItem->addChild(new QTreeWidgetItem(answersItem, QStringList(HeaderUtil::getDNSAnswer(package, i))));
        }

        QTreeWidgetItem* authoritativeNameserversItem = new QTreeWidgetItem(applicationHeader, QStringList(QString("Authoritative nameservers")));
        applicationHeader->addChild(authoritativeNameserversItem);
        for (auto i = 0; i < HeaderUtil::getDNSAuthorityRRs(package).toInt(); i++) {
            queriesItem->addChild(new QTreeWidgetItem(authoritativeNameserversItem, QStringList(HeaderUtil::getDNSAuthoritativeNameserver(package, i))));
        }

        QTreeWidgetItem* additionalRecordsItem = new QTreeWidgetItem(applicationHeader, QStringList(QString("Additional records")));
        applicationHeader->addChild(additionalRecordsItem);
        for (auto i = 0; i < HeaderUtil::getDNSAdditionalRRs(package).toInt(); i++) {
            queriesItem->addChild(new QTreeWidgetItem(additionalRecordsItem, QStringList(HeaderUtil::getDNSAdditionalRecord(package, i))));
        }

        this->m_treeWidget->addTopLevelItem(applicationHeader);
    }


}

