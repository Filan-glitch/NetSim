#include "routerwidget.h"

RouterWidget::RouterWidget(Router *router, QWidget *parent)
    : QWidget{parent}, m_router{router}
{
    //Erstelle die Widgets
    m_button = new QPushButton(this);

    //Set the Icon
    m_button->setIcon(QIcon(":/router.svg"));
    m_button->setIconSize(QSize(64, 64));
    m_button->setFixedSize(QSize(64, 64));

}
