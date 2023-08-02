#include "simulationwindow.h"
#include "src/views/widgets/clientwidget.h"
#include "src/views/widgets/serverwidget.h"
#include "src/views/widgets/routerwidget.h"
#include "src/management/packagedatabase.h"
#include "ui_simulationwindow.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QGridLayout>

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

    //Connections
    connect(this->ui->actionDocumentation, &QAction::triggered, this, &SimulationWindow::openDocumentation);

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
    this->ui->networkTab->setLayout(mainLayout);

    for(auto i = 0; i < manager->getServerAmount(); i++) {
        ServerWidget* serverWidget = new ServerWidget(manager->getServer().at(i), this);
        mainLayout->addWidget(serverWidget, i, 0);
    }

    for(auto i = 1; i <= manager->getServerAmount(); i++) {
        RouterWidget* routerWidget = new RouterWidget(manager->getRouters().at(i), this);
        mainLayout->addWidget(routerWidget, i - 1, 1);
    }

    // Mainrouter
    auto mainRouter = new RouterWidget(this->manager->getRouters().at(0), this);
    switch(this->manager->getClientsAmount()) {
    case 1:
        mainLayout->addWidget(mainRouter, 0, 2);
        break;
    case 2:
        mainLayout->addWidget(mainRouter, 1, 2);
    case 3:
    case 4:
    case 5:
        mainLayout->addWidget(mainRouter, 2, 2);
        break;
    }

    for(auto i = 0; i < manager->getClientsAmount(); i++) {
        ClientWidget* clientWidget = new ClientWidget(manager->getClients().at(i), this);
        mainLayout->addWidget(clientWidget, i, 3);
    }
}


void SimulationWindow::openDocumentation() {
    QDesktopServices::openUrl(QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}

