#include "logger.h"

#include <QDateTime>
#include <QDir>

using namespace NetSim;

QFile *Logger::logFile = Q_NULLPTR;

bool Logger::isInit = false;

QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg, "Debug"},
    {QtMsgType::QtInfoMsg, "Info"},
    {QtMsgType::QtWarningMsg, "Warning"},
    {QtMsgType::QtCriticalMsg, "Critical"},
    {QtMsgType::QtFatalMsg, "Fatal"}};

void Logger::init() {
  if (isInit) {
    return;
  }

  QDir dir = QDir();
  dir.mkdir("logs");
  logFile = new QFile();
  logFile->setFileName(
      "logs/NetSim_log_" +
      QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss") + ".log");
  logFile->open(QIODevice::Append | QIODevice::Text);

  // Redirect logs to messageOutput
  qInstallMessageHandler(Logger::messageOutput);

  Logger::isInit = true;
}

void Logger::clean() {
  if (logFile != Q_NULLPTR) {
    logFile->close();
    delete logFile;
  }
}

void Logger::messageOutput(QtMsgType type, const QMessageLogContext &context,
                           const QString &msg) {
  QString log =
      QObject::tr("[%1] [%2] [%3] [%4] %5\n")
          .arg(QDateTime::currentDateTime().toString("hh:mm:ss:msmsms"),
               Logger::contextNames.value(type),
               QString(context.file).section('\\', -1),
               QString::number(context.line), msg);
  logFile->write(log.toUtf8());
  logFile->flush();
}
