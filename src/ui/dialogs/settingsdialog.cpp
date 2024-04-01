#include "settingsdialog.h"
#include "ui_settingsdialog.h"

using namespace NetSim;

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog) {
  ui->setupUi(this);


  // Setting the geometry
  QRect rect = parent->geometry();
  rect.setHeight(0);
  this->setGeometry(rect);
  this->setFixedSize(size());

  // Setting the window flags
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  // Setting the radio buttons
  ui->httpRadioButton->setChecked(true);
  ui->dnsRadioButton->setEnabled(false);
  ui->udpRadioButton->setEnabled(false);
  ui->tcpRadioButton->setEnabled(false);
  ui->icmpRadioButton->setEnabled(false);
  ui->ipRadioButton->setEnabled(false);
  ui->dhcpRadioButton->setEnabled(false);
  ui->arpRadioButton->setEnabled(false);

  // Connecting the signals and slots
  connect(ui->httpRadioButton, SIGNAL(clicked()), this, SLOT(onhttpRadioButtonChecked()));
  connect(ui->dnsRadioButton, SIGNAL(clicked()), this, SLOT(ondnsRadioButtonChecked()));
  connect(ui->udpRadioButton, SIGNAL(clicked()), this, SLOT(onudpRadioButtonChecked()));
  connect(ui->tcpRadioButton, SIGNAL(clicked()), this, SLOT(ontcpRadioButtonChecked()));
  connect(ui->icmpRadioButton, SIGNAL(clicked()), this, SLOT(onicmpRadioButtonChecked()));
  connect(ui->ipRadioButton, SIGNAL(clicked()), this, SLOT(onipRadioButtonChecked()));
  connect(ui->dhcpRadioButton, SIGNAL(clicked()), this, SLOT(ondhcpRadioButtonChecked()));
  connect(ui->arpRadioButton, SIGNAL(clicked()), this, SLOT(onarpRadioButtonChecked()));

}

Praktikum SettingsDialog::praktikum() const
{
    Praktikum praktikum;
    if (ui->httpRadioButton->isChecked())
        praktikum = Praktikum::HTTP_Praktikum;
    else if (ui->dnsRadioButton->isChecked())
        praktikum = Praktikum::DNS_Praktikum;
    else if (ui->udpRadioButton->isChecked())
        praktikum = Praktikum::UDP_Praktikum;
    else if (ui->tcpRadioButton->isChecked())
        praktikum = Praktikum::TCP_Praktikum;
    else if (ui->icmpRadioButton->isChecked())
        praktikum = Praktikum::ICMP_Praktikum;
    else if (ui->ipRadioButton->isChecked())
        praktikum = Praktikum::IP_Praktikum;
    else if (ui->dhcpRadioButton->isChecked())
        praktikum = Praktikum::DHCP_Praktikum;
    else praktikum = Praktikum::ARP_Praktikum;
    return praktikum;
}

SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::onhttpRadioButtonChecked()
{
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::ondnsRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::onudpRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::ontcpRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::onicmpRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::onipRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::ondhcpRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->arpRadioButton->setChecked(false);
}

void SettingsDialog::onarpRadioButtonChecked()
{
    ui->httpRadioButton->setChecked(false);
    ui->dnsRadioButton->setChecked(false);
    ui->udpRadioButton->setChecked(false);
    ui->tcpRadioButton->setChecked(false);
    ui->icmpRadioButton->setChecked(false);
    ui->ipRadioButton->setChecked(false);
    ui->dhcpRadioButton->setChecked(false);
}


