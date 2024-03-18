#include "routerwidget.h"

using namespace NetSim;

RouterWidget::RouterWidget(Router *router, QWidget *parent)
    : QWidget{parent}, m_router{router} {
  // create the widgets
  m_button = new QPushButton(this);
  m_localIpLabel = new QLabel(this);
  m_globalIpLabel = new QLabel(this);
  m_macLabel = new QLabel(this);

  // Set the Icon
  m_button->setIcon(QIcon(":/router.svg"));
  m_button->setIconSize(QSize(64, 64));
  m_button->setFixedSize(QSize(64, 64));

  // Set the label
  m_localIpLabel->setText("Lokale IP-Adresse: " +
                          m_router->networkCard().networkAddress().toString());
  m_localIpLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_localIpLabel->setGeometry(m_localIpLabel->geometry().x(),
                              m_localIpLabel->geometry().y(), 0, 0);
  m_localIpLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_globalIpLabel->setText("Global IP-Adresse: " +
                           m_router->globalIpAddress().toString());
  m_globalIpLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_globalIpLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_globalIpLabel->setGeometry(m_globalIpLabel->geometry().x(),
                               m_globalIpLabel->geometry().y(), 0, 0);
  m_macLabel->setText("MAC-Adresse: " +
                      m_router->networkCard().physicalAddress().toString());
  m_macLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_macLabel->setGeometry(m_macLabel->geometry().x(),
                          m_macLabel->geometry().y(), 0, 0);
  m_macLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  // create the layout
  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_button);
  m_layout->addWidget(m_globalIpLabel);
  m_layout->addWidget(m_localIpLabel);
  m_layout->addWidget(m_macLabel);
  m_layout->setContentsMargins(QMargins(2, 2, 2, 2));
  this->setFixedSize(QSize(qFloor(parent->size().height() / 6 + 100),
                           qFloor(parent->size().height() / 6)));

  // Connections
  connect(m_button, &QPushButton::clicked, this,
          &RouterWidget::onButtonClicked);
}

RouterWidget::~RouterWidget() {
  delete m_layout;
  delete m_button;
  delete m_globalIpLabel;
  delete m_localIpLabel;
  delete m_macLabel;
}

Router *RouterWidget::router() { return m_router; }

QPushButton *RouterWidget::button() const { return m_button; }

void RouterWidget::onButtonClicked() { emit clicked(this); }
