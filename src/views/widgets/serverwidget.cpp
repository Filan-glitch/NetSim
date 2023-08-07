#include "serverwidget.h"

ServerWidget::ServerWidget(const Server &server, QWidget *parent)
    : QWidget{parent}, m_server{server}
{
    //Erstelle die Widgets
    m_button = new QPushButton(this);
    m_ipLabel = new QLabel(this);
    m_macLabel = new QLabel(this);

    //Set the Icon
    m_button->setIcon(QIcon(":/server.svg"));
    m_button->setIconSize(QSize(64, 64));
    m_button->setFixedSize(QSize(64, 64));

    m_ipLabel->setText("IP-Adresse: " + m_server.getNetworkCard().getNetworkAddress().getAddressAsDecString());
    m_ipLabel->setStyleSheet("QLabel { background-color : #f9f9f9; }");
    m_macLabel->setText("MAC-Adresse: " + m_server.getNetworkCard().getPhysicalAddress().getAddressAsString());
    m_macLabel->setStyleSheet("QLabel { background-color : #f9f9f9; }");

    //Erstelle Layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_button);
    m_layout->addWidget(m_ipLabel);
    m_layout->addWidget(m_macLabel);

    this->setFixedSize(QSize(256, 128));
}

QPushButton *ServerWidget::button() const
{
    return m_button;
}
