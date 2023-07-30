#include "routerwidget.h"

RouterWidget::RouterWidget(const Router &router, QWidget *parent)
    : QPushButton{parent}, router{router}
{
    this->icon().addFile(":/router.svg");
}
