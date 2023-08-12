#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include "src/management/packagetablemodel.h"
#include "src/management/simulationmanager.h"
#include "src/views/widgets/clientwidget.h"
#include "src/views/widgets/routerwidget.h"
#include "src/views/widgets/serverwidget.h"
#include <QKeyEvent>
#include <QMainWindow>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class SimulationWindow;
}
QT_END_NAMESPACE

namespace NetSim {

class SimulationWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit SimulationWindow(SimulationManager *manager,
                            QWidget *parent = nullptr);

  ~SimulationWindow();

  void keyPressEvent(QKeyEvent *event) override;

private:
  Ui::SimulationWindow *ui;

  SimulationManager *m_manager;

  PackageTableModel *m_packageModel;

  QTreeWidget *m_treeWidget;

  void setupNetwork();

private slots:
  void openDocumentation();

  void updateTreeWidget(const QModelIndex &index);

  void about();

  void clientDialog(ClientWidget *client);

  void routerDialog(RouterWidget *router);

  void serverDialog(ServerWidget *server);
};
} // namespace NetSim

#endif // SIMULATIONWINDOW_H
