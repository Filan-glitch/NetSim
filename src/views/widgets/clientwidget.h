#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include "src/network/client.h"
#include <QPushButton>

class ClientWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit ClientWidget(const Client &client, QWidget *parent = nullptr);

private:
    Client client;
};

#endif // CLIENTWIDGET_H
