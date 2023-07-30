#ifndef PACKAGETABLEMODEL_H
#define PACKAGETABLEMODEL_H

#include "src/models/package.h"
#include <QAbstractTableModel>

class PackageTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PackageTableModel(QList<Package>* packageList, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    void addPackage(const Package& package);

private:
    QList<Package>* m_packageList;
};

#endif // PACKAGETABLEMODEL_H
