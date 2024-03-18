#include "ui/windows/welcomewindow.h"

#include "management/logger.h"
#include <QApplication>

using namespace NetSim;

int main(int argc, char *argv[]) {
  Logger::init();

  QApplication a(argc, argv);
  qInfo() << "Application started";
  WelcomeWindow w;
  w.show();
  bool state = a.exec();
  qInfo() << "Application finished";

  Logger::clean();
  return state;
}
