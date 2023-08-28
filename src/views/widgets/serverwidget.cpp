#include "serverwidget.h"

using namespace NetSim;

ServerWidget::ServerWidget(Server *server, QWidget *parent)
    : QWidget{parent}, m_server{server} {
  // Create the widgets
  m_button = new QPushButton(this);
  m_domainLabel = new QLabel(this);
  m_ipLabel = new QLabel(this);
  m_macLabel = new QLabel(this);

  // Set the Icon
  m_button->setIcon(QIcon(":/server.svg"));
  m_button->setIconSize(QSize(64, 64));
  m_button->setFixedSize(QSize(64, 64));

  m_domainLabel->setText("Domain: " + m_server->domain());
  m_domainLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_domainLabel->setGeometry(m_domainLabel->geometry().x(),
                             m_domainLabel->geometry().y(), 0, 0);
  m_domainLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_ipLabel->setText("IP-Adresse: " +
                     m_server->networkCard().networkAddress().toString());
  m_ipLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_ipLabel->setGeometry(m_ipLabel->geometry().x(), m_ipLabel->geometry().y(),
                         0, 0);
  m_ipLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_macLabel->setText("MAC-Adresse: " +
                      m_server->networkCard().physicalAddress().toString());
  m_macLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_macLabel->setGeometry(m_macLabel->geometry().x(),
                          m_macLabel->geometry().y(), 0, 0);
  m_macLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  // Create Layout
  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_button);
  m_layout->addWidget(m_domainLabel);
  m_layout->addWidget(m_ipLabel);
  m_layout->addWidget(m_macLabel);
  m_layout->setContentsMargins(QMargins(2, 2, 2, 2));
  this->setFixedSize(QSize(qFloor(parent->size().height() / 6 + 100),
                           qFloor(parent->size().height() / 6)));

  // Connections
  connect(m_button, &QPushButton::clicked, this,
          &ServerWidget::onButtonClicked);
}

ServerWidget::~ServerWidget() {
  delete m_button;
  delete m_domainLabel;
  delete m_ipLabel;
  delete m_macLabel;
  delete m_layout;
}

Server *ServerWidget::server() { return m_server; }

QPushButton *ServerWidget::button() const { return m_button; }

void ServerWidget::onButtonClicked() { emit clicked(this); }
