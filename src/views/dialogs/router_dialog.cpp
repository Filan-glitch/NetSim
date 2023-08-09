#include "router_dialog.h"
#include "ui_router_dialog.h"

Router_Dialog::Router_Dialog(RouterWidget* router, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Router_Dialog),
    router(router)
{
    ui->setupUi(this);
}

Router_Dialog::~Router_Dialog()
{
    delete ui;
}
