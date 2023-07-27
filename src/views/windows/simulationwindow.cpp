#include "simulationwindow.h"
#include "ui_simulationwindow.h"
#include <QLabel>
#include <QKeyEvent>
#include <QDesktopServices>

SimulationWindow::SimulationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulationWindow)
{
    //Initial Setup
    ui->setupUi(this);
    showFullScreen();

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

void SimulationWindow::openDocumentation() {
    QDesktopServices::openUrl(QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}
void SimulationWindow::on_clientButton_clicked()
{
    ui->instanceLabel->setText("Client");
    ui->requestLabel->setText("Requesttype:");
    ui->requestContentLabel->setText("GET");
}


void SimulationWindow::on_serverButton_clicked()
{
    ui->instanceLabel->setText("Server");
    ui->requestLabel->setText("Response:");
    ui->requestContentLabel->setText("OK");
}


void SimulationWindow::on_router1Button_clicked()
{
    //TODO setting the other labels
    ui->instanceLabel->setText("Client Router");
}


void SimulationWindow::on_router2Button_clicked()
{
    //TODO setting the other labels
    ui->instanceLabel->setText(("Server Router"));
}

