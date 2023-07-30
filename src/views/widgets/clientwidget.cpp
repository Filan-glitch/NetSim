#include "clientwidget.h"

ClientWidget::ClientWidget(const Client &client, QWidget *parent)
    : QPushButton{parent}, client{client}
{
    this->icon().addFile(":/client.svg");
}
