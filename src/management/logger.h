#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QFile>
#include <QHash>

//! \file logger.h
//! \ingroup NetSimLogger
//! \brief Contains the Logger class definition.

namespace NetSim {

//! \defgroup NetSimLogger NetSim Logger
//! \brief Provides logging utilities for the NetSim project.

/**
 * @class Logger
 * @ingroup NetSimLogger
 * @brief A utility class that provides static methods for logging messages.
 *
 * The Logger class handles the initialization, cleanup, and output of logging
 * messages. It uses a QHash to associate QtMsgTypes with their respective
 * context names.
 */
class Logger {
public:
  /**
   * @brief Initializes the logger.
   *
   * This method should be called once before using the other logging methods.
   */
  static void init();

  /**
   * @brief Cleans up resources used by the logger.
   *
   * This method should be called once after all logging is done.
   */
  static void clean();

  /**
   * @brief Outputs log messages based on their type and context.
   *
   * @param type The type of the message (e.g., debug, warning, error).
   * @param context Information about the source code location of the message.
   * @param msg The actual log message.
   */
  static void messageOutput(QtMsgType type, const QMessageLogContext &context,
                            const QString &msg);

private:
  //! @brief The file where log messages are written.
  static QFile *logFile;

  //! @brief Indicates if the logger has been initialized.
  static bool isInit;

  //! @brief Maps QtMsgTypes to their context names.
  static QHash<QtMsgType, QString> contextNames;
};
} // namespace NetSim

#endif // LOGGER_H
