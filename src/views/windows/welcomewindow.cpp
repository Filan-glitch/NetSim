#include "welcomewindow.h"
#include "simulationwindow.h"
#include "src/views/dialogs/about_dialog.h"
#include "src/views/dialogs/settingsdialog.h"
#include "ui_welcomewindow.h"
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WelcomeWindow) {
  // Initial Setup
  ui->setupUi(this);

  // Connections
  connect(this->ui->startButton, &QPushButton::clicked, this,
          &WelcomeWindow::startSimulation);
  connect(this->ui->helpButton, &QPushButton::clicked, this,
          &WelcomeWindow::openDocumentation);
  connect(this->ui->aboutButton, &QPushButton::clicked, this,
          &WelcomeWindow::about);
}

WelcomeWindow::~WelcomeWindow() { delete ui; }

void WelcomeWindow::startSimulation() {
  SettingsDialog settings(this);
  if (settings.exec() == QDialog::Accepted) {
    // Schließe das aktuelle Fenster (Startmenü).
    close();

    // Manager initialisieren.
    SimulationManager *manager =
        new SimulationManager(settings.clientsAmount(),
                                                       settings.serversAmount(), settings.domains());

    // Öffne das Fenster für die Simulation.
    SimulationWindow *simWindow = new SimulationWindow(manager, this);
    simWindow->show();
  }
}

void WelcomeWindow::openDocumentation() {
  QDesktopServices::openUrl(
      QUrl("https://github.com/Filan-glitch/NetSim/wiki"));
}

void WelcomeWindow::about() {
  About_Dialog aboutDialog(this);
  aboutDialog.exec();
}
