#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QHBoxLayout>

SimulationWindow::SimulationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationWindow)
{
    //Initial Setup
    ui->setupUi(this);
    showFullScreen();

    //Connections
    connect(this->ui->actionDocumentation, &QAction::triggered, this, &SimulationWindow::openDocumentation);

    QLayout *centralLayout = new QHBoxLayout();
    this->centralWidget()->setLayout(centralLayout);

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

void SimulationWindow::setupNetwork(qint8 clientsAmount, qint8 serverAmount)
{

}

void SimulationWindow::openDocumentation() {
    QDesktopServices::openUrl(QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}

