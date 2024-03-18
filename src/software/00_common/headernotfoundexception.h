#ifndef HEADERNOTFOUNDEXCEPTION_H
#define HEADERNOTFOUNDEXCEPTION_H

#include <QString>

//! \file headernotfoundexception.h
//! \ingroup NetSimHeaderNotFoundException
//! \brief Contains the HeaderNotFoundException class definition.

namespace NetSim {

//! \defgroup NetSimHeaderNotFoundException HeaderNotFoundException
//! \brief Provides exceptions for scenarios when a header is not found.

/**
 * @class HeaderNotFoundException
 * @ingroup NetSimHeaderNotFoundException
 * @brief Exception class for scenarios when a header is not found.
 *
 * The HeaderNotFoundException is thrown when an operation attempts to access
 * a header that does not exist. This helps in error handling and ensuring
 * that the software does not encounter unexpected failures.
 */
class HeaderNotFoundException {
public:
  /**
   * @brief Constructs the exception with an error message.
   *
   * @param errorMessage Description of the error encountered.
   */
  HeaderNotFoundException(const QString &errorMessage);

  //! Simple Getter for the error message
  QString errorMessage() const;

private:
  //! @brief Message describing the specific error.
  QString m_errorMessage;
};

} // namespace NetSim

#endif // HEADERNOTFOUNDEXCEPTION_H
