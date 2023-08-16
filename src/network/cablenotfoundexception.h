#ifndef CABLENOTFOUNDEXCEPTION_H
#define CABLENOTFOUNDEXCEPTION_H

#include <QString>

//! \file cablenotfoundexception.h
//! \ingroup NetSimCablenotFoundException
//! \brief Contains the CableNotFoundException class definition.

namespace NetSim {

//! \defgroup NetSimCablenotFoundException CableNotFoundException
//! \brief Provides exception for when a cable connection is not found.
/**
 * @class CableNotFoundException
 * @ingroup NetSimCablenotFoundException
 * @brief The CableNotFoundException class
 *
 * This exception is thrown whenever there's an operation that requires
 * accessing a network cable and said cable isn't found or isn't accessible.
 */
class CableNotFoundException {
public:
  /**
   * @brief Constructor that initializes the exception with an error message.
   *
   * @param errorMessage Description of the error that caused this exception.
   */
  CableNotFoundException(const QString &errorMessage);

  /**
   * @brief Fetches the error message associated with this exception.
   *
   * @retval QString The description of the error.
   */
  QString errorMessage() const;

private:
  //! @brief Holds the description of the error.
  QString m_errorMessage{};
};
} // namespace NetSim

#endif // CABLENOTFOUNDEXCEPTION_H
