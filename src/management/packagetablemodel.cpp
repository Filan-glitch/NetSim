#include "packagetablemodel.h"
#include "src/software/00_common/headerutil.h"

using namespace NetSim;

PackageTableModel::PackageTableModel(QList<Package> *packageList,
                                     QObject *parent)
    : QAbstractTableModel(parent), m_packageList(packageList) {}

QVariant PackageTableModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role == Qt::DisplayRole) {
    // Setting the header strings
    if (orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return tr("Source");
      case 1:
        return tr("Destination");
      case 2:
        return tr("Protocol");
      case 3:
        return tr("Size");
      case 4:
        return tr("Info");
      }
    } else {
      // Inverting the counting of the entries so it starts from the bottom one
      return QString::number(m_packageList->size() - section);
    }
  }
  return QVariant();
}

int PackageTableModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return m_packageList->size();
}

int PackageTableModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid())
    return 0;

  return 5;
}

QVariant PackageTableModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role == Qt::DisplayRole) {
    // Inverting the counting of the entries so it starts from the bottom one
    const Package package =
        m_packageList->at(m_packageList->size() - index.row() - 1);

    switch (index.column()) {
    case 0:
      return HeaderUtil::getIPAddress(package, true);
    case 1:
      return HeaderUtil::getIPAddress(package, false);
    case 2: {
      switch (HeaderUtil::getTopProtocol(package)) {
      case DNS:
        return "DNS";
        break;
      case HTTP:
        return "HTTP";
        break;
      case TCP:
        return "TCP";
        break;
      case UDP:
        return "UDP";
        break;
      case IP:
        return "IP";
        break;
      case MAC:
        return "MAC";
        break;
      default:
        return "Unknown";
        break;
      }
    }
    case 3:
      return HeaderUtil::getPackageLength(package);
    case 4:
      return package.info();
    }
  }
  return QVariant();
}

void PackageTableModel::addPackage(const Package &package) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());

  m_packageList->append(package);

  endInsertRows();
}
