#ifndef ROUTERWIDGET_H
#define ROUTERWIDGET_H

#include "src/network/router.h"
#include <QPushButton>

class RouterWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit RouterWidget(const Router &router, QWidget *parent = nullptr);

private:
    Router router;
};

#endif // ROUTERWIDGET_H
