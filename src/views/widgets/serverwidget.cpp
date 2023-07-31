#include "serverwidget.h"

ServerWidget::ServerWidget(Server *server, QWidget *parent)
    : QWidget{parent}, m_server{server}
{
    //Erstelle die Widgets
    m_button = new QPushButton(this);
    m_ipLabel = new QLabel(this);
    m_macLabel = new QLabel(this);

    //Set the Icon
    m_button->setIcon(QIcon(":/server.svg"));
    m_button->setIconSize(QSize(64, 64));

    m_ipLabel->setText("IP-Adresse: " + m_server->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    m_macLabel->setText("MAC-Adresse: " + m_server->getNetworkCard().getPhysicalAddress().getAddressAsString());
}
