#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Connections
    connect(ui->clientsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setClientsAmount(int)));
    connect(ui->serverSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setServerAmount(int)));

    ui->domainLabel_2->setVisible(false);
    ui->domainLineEdit_2->setVisible(false);
    ui->domainLabel_3->setVisible(false);
    ui->domainLineEdit_3->setVisible(false);
    ui->domainLabel_4->setVisible(false);
    ui->domainLineEdit_4->setVisible(false);
    ui->domainLabel_5->setVisible(false);
    ui->domainLineEdit_5->setVisible(false);
    ui->startPushButton->setEnabled(false);
    QRect rect = parent->geometry();
    rect.setHeight(0);
    this->setGeometry(rect);
    this->setFixedSize(size());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->domainLineEdit_1, &QLineEdit::textChanged, this, &SettingsDialog::textChanged1);
    connect(ui->domainLineEdit_2, &QLineEdit::textChanged, this, &SettingsDialog::textChanged2);
    connect(ui->domainLineEdit_3, &QLineEdit::textChanged, this, &SettingsDialog::textChanged3);
    connect(ui->domainLineEdit_4, &QLineEdit::textChanged, this, &SettingsDialog::textChanged4);
    connect(ui->domainLineEdit_5, &QLineEdit::textChanged, this, &SettingsDialog::textChanged5);
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setClientsAmount(int amount)
{
    clientsAmount = static_cast<quint8>(amount);
}

void SettingsDialog::setServerAmount(int amount)
{
    serverAmount = static_cast<quint8>(amount);
    QRect rect;
    switch(amount) {
    case 1:
        ui->domainLabel_2->setVisible(false);
        ui->domainLineEdit_2->setVisible(false);
        ui->domainLabel_3->setVisible(false);
        ui->domainLineEdit_3->setVisible(false);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        rect = static_cast<QWidget*>(this->parent())->geometry();
        rect.setX(this->geometry().x());
        rect.setY(this->geometry().y());
        rect.setHeight(0);
        this->setGeometry(rect);
        break;
    case 2:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(false);
        ui->domainLineEdit_3->setVisible(false);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        rect = static_cast<QWidget*>(this->parent())->geometry();
        rect.setX(this->geometry().x());
        rect.setY(this->geometry().y());
        rect.setHeight(0);
        this->setGeometry(rect);
        break;
    case 3:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(false);
        ui->domainLineEdit_4->setVisible(false);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        rect = static_cast<QWidget*>(this->parent())->geometry();
        rect.setX(this->geometry().x());
        rect.setY(this->geometry().y());
        rect.setHeight(0);
        this->setGeometry(rect);
        break;
    case 4:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(true);
        ui->domainLineEdit_4->setVisible(true);
        ui->domainLabel_5->setVisible(false);
        ui->domainLineEdit_5->setVisible(false);
        rect = static_cast<QWidget*>(this->parent())->geometry();
        rect.setX(this->geometry().x());
        rect.setY(this->geometry().y());
        rect.setHeight(0);
        this->setGeometry(rect);
        break;
    case 5:
        ui->domainLabel_2->setVisible(true);
        ui->domainLineEdit_2->setVisible(true);
        ui->domainLabel_3->setVisible(true);
        ui->domainLineEdit_3->setVisible(true);
        ui->domainLabel_4->setVisible(true);
        ui->domainLineEdit_4->setVisible(true);
        ui->domainLabel_5->setVisible(true);
        ui->domainLineEdit_5->setVisible(true);
        rect = static_cast<QWidget*>(this->parent())->geometry();
        rect.setX(this->geometry().x());
        rect.setY(this->geometry().y());
        rect.setHeight(0);
        this->setGeometry(rect);
        break;
    }

    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}

quint8 SettingsDialog::getClientsAmount() const
{
    return clientsAmount;
}

quint8 SettingsDialog::getServerAmount() const
{
    return serverAmount;
}

void SettingsDialog::textChanged1(const QString &data)
{
    m_domain1 = data;
    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}

void SettingsDialog::textChanged2(const QString &data)
{
    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}

void SettingsDialog::textChanged3(const QString &data)
{
    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}

void SettingsDialog::textChanged4(const QString &data)
{
    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}

void SettingsDialog::textChanged5(const QString &data)
{
    if(allVisibleLineEditsFilled()){
        ui->startPushButton->setEnabled(true);
    }
    else{
        ui->startPushButton->setEnabled(false);
    }
}


QList<QString> SettingsDialog::domains() const {
    switch(serverAmount) {
    case 1:
        return QList<QString>() << m_domain1;
    case 2:
        return QList<QString>() << m_domain1 << m_domain2;
    case 3:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3;
    case 4:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3 << m_domain4;
    case 5:
        return QList<QString>() << m_domain1 << m_domain2 << m_domain3 << m_domain4 << m_domain5;
    default:
        return QList<QString>() << m_domain1;
    }
}

bool SettingsDialog::allVisibleLineEditsFilled(){
    switch(serverAmount){
    case 0:
        return false;
    case 1:
        return ui->domainLineEdit_1->text().size() > 0;
    case 2:
        return (ui->domainLineEdit_1->text().size() > 0) && (ui->domainLineEdit_2->text().size() > 0);
    case 3:
        return (ui->domainLineEdit_1->text().size() > 0) && (ui->domainLineEdit_2->text().size() > 0) && (ui->domainLineEdit_3->text().size() > 0);
    case 4:
        return (ui->domainLineEdit_1->text().size() > 0) && (ui->domainLineEdit_2->text().size() > 0) && (ui->domainLineEdit_3->text().size() > 0) && (ui->domainLineEdit_4->text().size() > 0);
    case 5:
        return (ui->domainLineEdit_1->text().size() > 0) && (ui->domainLineEdit_2->text().size() > 0) && (ui->domainLineEdit_3->text().size() > 0) && (ui->domainLineEdit_4->text().size() > 0) && (ui->domainLineEdit_5->text().size() > 0);
    }
    return false;
}

