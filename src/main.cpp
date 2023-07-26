#include "views/windows/welcomewindow.h"

#include <QApplication>
#include "management/logger.h"

int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);
    qInfo() << "Application started";
    WelcomeWindow w;
    w.show();
    bool state = a.exec();

    Logger::clean();
    return state;
}
