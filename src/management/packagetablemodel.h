#ifndef PACKAGETABLEMODEL_H
#define PACKAGETABLEMODEL_H

#include "src/models/package.h"
#include <QAbstractTableModel>

namespace NetSim {
class PackageTableModel;
}

class PackageTableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit PackageTableModel(QList<Package> *packageList,
                             QObject *parent = nullptr);

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addPackage(const Package &package);

private:
  QList<Package> *m_packageList;
};

#endif // PACKAGETABLEMODEL_H
