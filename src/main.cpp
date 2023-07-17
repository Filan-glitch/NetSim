#include "views/widgets/mainwindow.h"

#include <QApplication>
#include "management/logger.h"

int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);
    qInfo() << "Application started";
    MainWindow w;
    w.show();
    bool state = a.exec();

    Logger::clean();
    return state;
}
