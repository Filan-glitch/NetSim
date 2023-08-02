#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include "src/network/server.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ServerWidget(const Server &server, QWidget *parent = nullptr);

private:
    Server m_server;

    //Widgets
    QPushButton* m_button;
    QLabel* m_ipLabel;
    QLabel* m_macLabel;

    //Layout
    QVBoxLayout* m_layout;
};

#endif // SERVERWIDGET_H
