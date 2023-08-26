#include "clientwidget.h"
#include <QtMath>

using namespace NetSim;

ClientWidget::ClientWidget(Client *client, const QString &name, QWidget *parent)
    : QWidget{parent}, m_client{client} {
  // Erstelle die Widgets
  m_button = new QPushButton(this);
  m_nameLabel = new QLabel(this);
  m_ipLabel = new QLabel(this);
  m_macLabel = new QLabel(this);

  // Set the Icon
  m_button->setIcon(QIcon(":/client.svg"));
  m_button->setIconSize(QSize(64, 64));
  m_button->setFixedSize(QSize(64, 64));

  m_nameLabel->setText(name);
  m_nameLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_nameLabel->setGeometry(m_nameLabel->geometry().x(),
                           m_nameLabel->geometry().y(), 0, 0);
  m_nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_ipLabel->setText("IP-Adresse: " +
                     m_client->networkCard().networkAddress().toString());
  m_ipLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_ipLabel->setGeometry(m_ipLabel->geometry().x(), m_ipLabel->geometry().y(),
                         0, 0);
  m_ipLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  m_macLabel->setText("MAC-Adresse: " +
                      m_client->networkCard().physicalAddress().toString());
  m_macLabel->setStyleSheet(
      "QLabel { color: #a9b7c6; background-color : #1e1d23; }");
  m_macLabel->setGeometry(m_macLabel->geometry().x(),
                          m_macLabel->geometry().y(), 0, 0);
  m_macLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  // Erstelle Layout
  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_button);
  m_layout->addWidget(m_nameLabel);
  m_layout->addWidget(m_ipLabel);
  m_layout->addWidget(m_macLabel);
  m_layout->setContentsMargins(QMargins(2, 2, 2, 2));
  this->setFixedSize(QSize(qFloor(parent->size().height() / 6 + 100), qFloor(parent->size().height() / 6)));

  // Connections
  connect(m_button, &QPushButton::clicked, this,
          &ClientWidget::onButtonClicked);
}

ClientWidget::~ClientWidget() {
  delete m_button;
  delete m_nameLabel;
  delete m_ipLabel;
  delete m_macLabel;
  delete m_layout;
}

Client *ClientWidget::client() { return m_client; }

QPushButton *ClientWidget::button() const { return m_button; }

void ClientWidget::onButtonClicked() { emit clicked(this); }

QString ClientWidget::name() const { return m_nameLabel->text(); }
