#ifndef ROUTER_DIALOG_H
#define ROUTER_DIALOG_H

#include "src/views/widgets/routerwidget.h"
#include <QDialog>

namespace Ui {
class Router_Dialog;
}

class Router_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Router_Dialog(RouterWidget *router, QWidget *parent = nullptr);
    ~Router_Dialog();

private:
    Ui::Router_Dialog *ui;
    RouterWidget *router;
};

#endif // ROUTER_DIALOG_H
