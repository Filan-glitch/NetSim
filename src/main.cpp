#include "views/widgets/mainwindow.h"

#include <QApplication>
#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    bool state = a.exec();

    Logger::clean();
    return state;
}
