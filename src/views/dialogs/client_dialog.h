#ifndef CLIENT_DIALOG_H
#define CLIENT_DIALOG_H

#include "src/views/widgets/clientwidget.h"
#include <QDialog>

namespace Ui {
class Client_Dialog;
}

class Client_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Client_Dialog(ClientWidget *client, QWidget *parent = nullptr);
    ~Client_Dialog();

private:
    Ui::Client_Dialog *ui;
    ClientWidget* client;
};

#endif // CLIENT_DIALOG_H
