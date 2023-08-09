#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeWindow; }
QT_END_NAMESPACE

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private:
    Ui::WelcomeWindow *ui;
    void startSimulation();

private slots:
    void openDocumentation();
    void about();
};
#endif // WELCOMEWINDOW_H
