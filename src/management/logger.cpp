#include "logger.h"

#include <QDateTime>
#include <QDir>

using namespace NetSim;

// Static member to store the log file instance
QFile *Logger::logFile = Q_NULLPTR;

// Static member that indicates if the logger is initialized
bool Logger::isInit = false;

// Static mapping of log message types to their string representation
QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg, "Debug"},
    {QtMsgType::QtInfoMsg, "Info"},
    {QtMsgType::QtWarningMsg, "Warning"},
    {QtMsgType::QtCriticalMsg, "Critical"},
    {QtMsgType::QtFatalMsg, "Fatal"}};

void Logger::init() {
    // Skip initialization if already initialized
  if (isInit) {
    return;
  }

  // Set up the log file with current timestamp
  QDir dir = QDir();
  dir.mkdir("logs");
  logFile = new QFile();
  logFile->setFileName(
      "logs/NetSim_log_" +
      QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss") + ".log");
  logFile->open(QIODevice::Append | QIODevice::Text);

  // Redirect the default Qt log messages to custom handler
  qInstallMessageHandler(Logger::messageOutput);

  Logger::isInit = true;
}

void Logger::clean() {
  // Closing the ressource and deleting the file
  if (logFile != Q_NULLPTR) {
    logFile->close();
    delete logFile;
  }
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext &context,
                           const QString &msg) {
  // Construct the log message
  QString log =
      QObject::tr("[%1] [%2] [%3] [%4] %5\n")
          .arg(QDateTime::currentDateTime().toString("hh:mm:ss:msmsms"),
               Logger::contextNames.value(type),
               QString(context.file).section('\\', -1),
               QString::number(context.line), msg);

  // Write the log message to the log file and flush it
  logFile->write(log.toUtf8());
  logFile->flush();
}
