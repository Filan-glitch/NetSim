#ifndef HEADERATTRIBUTE_H
#define HEADERATTRIBUTE_H

//! \file headerAttribute.h
//! \ingroup NetSimAttribute
//! \brief Contains the HeaderAttribute class definition.

#include <QString>
#include <QVector>

namespace NetSim {

//! \defgroup NetSimAttribute Attribute
//! \brief Contains all classes related to attributes.

/**
 * @class HeaderAttribute
 * @ingroup NetSimAttribute
 * @brief Class representing an attribute of a header.
 */
class HeaderAttribute {
public:
  /**
   * @brief Constructor for QVector<quint8> content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Content in bytes.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit,
                  const QVector<quint8> &content);

  /**
   * @brief Constructor for quint8 content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Single byte content.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit, quint8 content);

  /**
   * @brief Constructor for quint16 content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Double byte content.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit, quint16 content);

  /**
   * @brief Constructor for quint32 content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Four byte content.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit, quint32 content);

  /**
   * @brief Constructor for quint64 content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Eight byte content.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit, quint64 content);

  /**
   * @brief Constructor for QString content.
   *
   * @param name Attribute name.
   * @param sizeInBit Size of the content in bits.
   * @param content Content as QString.
   */
  HeaderAttribute(const QString &name, quint32 sizeInBit,
                  const QString &content);

  /**
   * @brief Default constructor.
   */
  HeaderAttribute() = default;

  /**
   * @brief Returns the name of the attribute.
   *
   * @retval QString Name of the attribute.
   */
  QString name() const;

  /**
   * @brief Returns the size of the attribute content in bits.
   *
   * @retval quint32 Size in bits.
   */
  quint32 size() const;

  /**
   * @brief Converts the content to an integer.
   *
   * @retval quint64 Content as an integer.
   */
  quint64 toInt() const;

  /**
   * @brief Converts the content to a byte array.
   *
   * @retval QVector<quint8> Content as a byte array.
   */
  QVector<quint8> toArray() const;

  /**
   * @brief Sets the content using a byte array.
   *
   * @param content Content to be set.
   */
  void setContent(QVector<quint8> content);

private:
  QString m_name{};            //!< Name of the attribute.
  quint32 m_sizeInBit{0};      //!< Size of the content in bits.
  QVector<quint8> m_content{}; //!< Content in bytes.
};

} // namespace NetSim

#endif // HEADERATTRIBUTE_H
