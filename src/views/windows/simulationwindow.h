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
    void setupNetwork(qint8 clientsAmount, qint8 serverAmount);

private slots:
    void openDocumentation();
};

#endif // SIMULATIONWINDOW_H
