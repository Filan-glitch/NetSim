#include "packagetablemodel.h"
#include "src/protocols/ipheader.h"

PackageTableModel::PackageTableModel(QList<Package> *packageList, QObject *parent)
    : QAbstractTableModel(parent), m_packageList(packageList)
{

}

QVariant PackageTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0:
                return tr("Source");
            case 1:
                return tr("Destination");
            case 2:
                return tr("Size");
            case 3:
                return tr("Info");
            }
        } else {
            return QString::number(section + 1);
        }
    }
    return QVariant();
}

int PackageTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_packageList->size();
}

int PackageTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 4;
}

QVariant PackageTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole) {
        const Package &package = m_packageList->at(index.row());

        switch(index.column()) {
        case 0:
            return dynamic_cast<IPHeader*>(package.getHeaderByType(HeaderType::IP))->getSourceAddress().getAddressAsDecString();
        case 1:
            return dynamic_cast<IPHeader*>(package.getHeaderByType(HeaderType::IP))->getDestinationAddress().getAddressAsDecString();
        }
        //TODO: add other columns
    }
    return QVariant();
}

void PackageTableModel::addPackage(const Package& package) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_packageList->append(package);

    endInsertRows();
}
