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
    QString getURI() const;
    QString getDomain() const;

private slots:
    void on_serverDomainLineEdit_textChanged(const QString &arg1);

    void on_pathLineEdit_textChanged(const QString &arg1);

private:
    Ui::Client_Dialog *ui;
    ClientWidget* client;
};

#endif // CLIENT_DIALOG_H
