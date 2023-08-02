#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "src/management/packagetablemodel.h"
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
    explicit SimulationWindow(SimulationManager* manager, QWidget *parent = nullptr);
    ~SimulationWindow();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SimulationWindow *ui;
    SimulationManager* manager;
    PackageTableModel* m_packageModel;
    void setupNetwork();

private slots:
    void openDocumentation();


};

#endif // SIMULATIONWINDOW_H
