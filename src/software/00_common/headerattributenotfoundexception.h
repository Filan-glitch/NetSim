#ifndef HEADERATTRIBUTENOTFOUNDEXCEPTION_H
#define HEADERATTRIBUTENOTFOUNDEXCEPTION_H

//! \file headerattributenotfoundexception.h
//! \ingroup NetSimHeaderAttributeNotFoundException
//! \brief Contains the HeaderAttributeNotFoundException class definition.

#include <QString>

namespace NetSim {

//! \defgroup NetSimHeaderAttributeNotFoundException
//! HeaderAttributeNotFoundException
//! \brief Contains all the exceptions used in
//! the NetSim application.

/**
 * @class HeaderAttributeNotFoundException
 * @ingroup NetSimException
 * @brief Exception class for header attribute not found scenarios.
 */
class HeaderAttributeNotFoundException {
public:
  /**
   * @brief Constructs the exception with an error message.
   *
   * @param errorMessage Message describing the error.
   */
  HeaderAttributeNotFoundException(const QString &errorMessage);

  /**
   * @brief Fetches the error message for the exception.
   *
   * @retval QString The error message.
   */
  QString errorMessage() const;

private:
  QString m_errorMessage{}; //!< Message describing the error.
};

} // namespace NetSim

#endif // HEADERATTRIBUTENOTFOUNDEXCEPTION_H
