#include "client_dialog.h"
#include "ui_client_dialog.h"

Client_Dialog::Client_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client_Dialog)
{
    ui->setupUi(this);
}

Client_Dialog::~Client_Dialog()
{
    delete ui;
}
