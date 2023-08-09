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
    explicit ServerWidget(Server* server, QWidget *parent = nullptr);
    Server* server();

    QPushButton *button() const;

private:
    Server* m_server;

    //Widgets
    QPushButton* m_button;
    QLabel* m_domainLabel;
    QLabel* m_ipLabel;
    QLabel* m_macLabel;

    //Layout
    QVBoxLayout* m_layout;

private slots:
    void onButtonClicked();

signals:
    void clicked(ServerWidget* server);
};

#endif // SERVERWIDGET_H
