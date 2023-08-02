#ifndef ROUTERWIDGET_H
#define ROUTERWIDGET_H

#include "src/network/router.h"
#include <QPushButton>
#include <QVBoxLayout>

class RouterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RouterWidget(Router *router, QWidget *parent = nullptr);

private:
    Router* m_router;

    //Widgets
    QPushButton* m_button;

    //Layout
    QVBoxLayout* m_layout;
};

#endif // ROUTERWIDGET_H
