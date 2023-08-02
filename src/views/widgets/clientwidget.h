#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include "src/network/client.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class ClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClientWidget(const Client &client, QWidget *parent = nullptr);

private:
    Client m_client;

    //Widgets
    QPushButton* m_button;
    QLabel* m_ipLabel;
    QLabel* m_macLabel;

    //Layout
    QVBoxLayout* m_layout;
};

#endif // CLIENTWIDGET_H
