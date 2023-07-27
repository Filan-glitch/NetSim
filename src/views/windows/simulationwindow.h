#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "src/management/simulationmanager.h"
#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimulationWindow(QWidget *parent = nullptr);
    ~SimulationWindow();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SimulationWindow *ui;
    SimulationManager* manager;

private slots:
    void openDocumentation();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_clientButton_clicked();
    void on_serverButton_clicked();
    void on_router1Button_clicked();
    void on_router2Button_clicked();
};

#endif // SIMULATIONWINDOW_H
