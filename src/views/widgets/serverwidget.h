#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include "src/network/server.h"
#include <QPushButton>

class ServerWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit ServerWidget(const Server &server, QWidget *parent = nullptr);

private:
    Server server;

};

#endif // SERVERWIDGET_H
