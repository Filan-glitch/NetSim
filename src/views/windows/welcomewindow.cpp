#include "welcomewindow.h"
#include "src/views/dialogs/settingsdialog.h"
#include "ui_welcomewindow.h"
#include "simulationwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WelcomeWindow)
{
    //Initial Setup
    ui->setupUi(this);


    //Connections
    connect(this->ui->startButton, &QPushButton::clicked, this, &WelcomeWindow::startSimulation);
    connect(this->ui->helpButton, &QPushButton::clicked, this, &WelcomeWindow::openDocumentation);
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::startSimulation() {
    SettingsDialog settings;
    if(settings.exec() == QDialog::Accepted) {
        // Schließe das aktuelle Fenster (Startmenü).
        close();

        // Manager initialisieren.
        SimulationManager* manager = new SimulationManager(settings.getClientsAmount(), settings.getServerAmount(), settings.domains());

        // Öffne das Fenster für die Simulation.
        SimulationWindow* simWindow = new SimulationWindow(manager, this);
        simWindow->show();
    }
}

void WelcomeWindow::openDocumentation()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}
