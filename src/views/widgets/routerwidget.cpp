#include "routerwidget.h"

RouterWidget::RouterWidget(Router* router, QWidget *parent)
    : QWidget{parent}, m_router{router}
{
    //Erstelle die Widgets
    m_button = new QPushButton(this);
    m_localIpLabel = new QLabel(this);
    m_globalIpLabel = new QLabel(this);
    m_macLabel = new QLabel(this);

    //Set the Icon
    m_button->setIcon(QIcon(":/router.svg"));
    m_button->setIconSize(QSize(64, 64));
    m_button->setFixedSize(QSize(64, 64));

    //Set the label
    m_localIpLabel->setText("Lokale IP-Adresse: " + m_router->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    m_localIpLabel->setStyleSheet("QLabel { background-color : #f9f9f9; }");
    m_globalIpLabel->setText("Global IP-Adresse: " + m_router->getGlobalIpAddress().getAddressAsDecString());
    m_globalIpLabel->setStyleSheet("QLabel { background-color : #f9f9f9; }");
    m_macLabel->setText("MAC-Adresse: " + m_router->getNetworkCard().getPhysicalAddress().getAddressAsString());
    m_macLabel->setStyleSheet("QLabel { background-color : #f9f9f9; }");

    //Erstelle das Layout
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_button);
    m_layout->addWidget(m_localIpLabel);
    m_layout->addWidget(m_globalIpLabel);
    m_layout->addWidget(m_macLabel);

    this->setFixedSize(QSize(256, 156));
    
}

Router *RouterWidget::router()
{
    return m_router;
}

QPushButton *RouterWidget::button() const
{
    return m_button;
}
