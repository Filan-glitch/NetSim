#include "welcomewindow.h"
#include "simulationwindow.h"
#include "src/ui/dialogs/about_dialog.h"
#include "src/ui/dialogs/settingsdialog.h"
#include "ui_welcomewindow.h"
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

using namespace NetSim;

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
    // Close the current window
    close();

    // Manager initialisation
    SimulationManager *manager = new SimulationManager(settings.praktikum());

    // Open the window for the simulation.
    SimulationWindow *simWindow = new SimulationWindow(manager);
    simWindow->setAttribute(Qt::WA_DeleteOnClose);
    simWindow->setAttribute(Qt::WA_QuitOnClose);
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
