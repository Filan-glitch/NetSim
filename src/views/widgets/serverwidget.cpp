#include "serverwidget.h"

ServerWidget::ServerWidget(const Server &server, QWidget *parent)
    : QPushButton{parent}, server{server}
{
    this->icon().addFile(":/server.svg");
}
