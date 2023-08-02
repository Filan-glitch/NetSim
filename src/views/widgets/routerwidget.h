#ifndef ROUTERWIDGET_H
#define ROUTERWIDGET_H

#include "qlabel.h"
#include "src/network/router.h"
#include <QPushButton>
#include <QVBoxLayout>

class RouterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RouterWidget(const Router &router, QWidget *parent = nullptr);

private:
    Router m_router;

    //Widgets
    QPushButton* m_button;
    QLabel* m_localIpLabel;
    QLabel* m_globalIpLabel;
    QLabel* m_macLabel;

    //Layout
    QVBoxLayout* m_layout;
};

#endif // ROUTERWIDGET_H
