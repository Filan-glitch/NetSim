#ifndef PACKAGETABLEMODEL_H
#define PACKAGETABLEMODEL_H

#include "src/models/package.h"
#include <QAbstractTableModel>

//! \file packagetablemodel.h
//! \ingroup Management
//! \brief Contains the PackageTableModel class definition.

namespace NetSim {

//! \defgroup NetSimPackageTable Package Table
//! \brief Provides utilities to model a table view for `Package` objects.

/**
 * @class PackageTableModel
 * @ingroup NetSimPackageTable
 * @brief Custom table model to represent a list of `Package` objects.
 *
 * The PackageTableModel class provides functionalities to represent and manage
 * a list of `Package` objects in a table view, building upon Qt's
 * QAbstractTableModel.
 */
class PackageTableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  /**
   * @brief Constructs a new table model with a given list of packages and
   * parent.
   *
   * @param packageList Pointer to the list of packages.
   * @param parent The parent QObject.
   */
  explicit PackageTableModel(QList<Package> *packageList,
                             QObject *parent = nullptr);

  /**
   * @brief Returns the data for the given role and section in the header with
   * the specified orientation.
   *
   * @param section The section of the header.
   * @param orientation Horizontal or Vertical.
   * @param role The role of the data.
   * @retval QVariant Data for the given role and section.
   */
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  /**
   * @brief Returns the number of rows under the given parent.
   *
   * @param parent The parent QModelIndex.
   * @retval int Number of rows.
   */
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  /**
   * @brief Returns the number of columns under the given parent.
   *
   * @param parent The parent QModelIndex.
   * @retval int Number of columns.
   */
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  /**
   * @brief Returns the data stored under the given role for the item referred
   * to by the index.
   *
   * @param index The QModelIndex.
   * @param role The role of the data.
   * @retval QVariant Data for the given role and index.
   */
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  /**
   * @brief Adds a new package to the table model.
   *
   * @param package The package to add.
   */
  void addPackage(const Package &package);

private:
  //! @brief A list storing all the `Package` objects that the model represents.
  QList<Package> *m_packageList{nullptr};
};
} // namespace NetSim

#endif // PACKAGETABLEMODEL_H
