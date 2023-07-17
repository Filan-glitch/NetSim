#include "logger.h"

#include <QDir>
#include <QTime>

QFile* Logger::logFile = Q_NULLPTR;
bool Logger::isInit = false;

QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg, "Debug"},
    {QtMsgType::QtInfoMsg, "Info"},
    {QtMsgType::QtWarningMsg, "Warning"},
    {QtMsgType::QtCriticalMsg, "Critical"},
    {QtMsgType::QtFatalMsg, "Fatal"}
};

void Logger::init() {
    if (isInit) {
        return;
    }

    // Create log file
    QDir dir = QDir();
    dir.cdUp();
    dir.mkdir("logs");
    dir.cd("logs");
    logFile = new QFile(dir.path());
    logFile->setFileName(QTime::currentTime().toString("dd-mm-yyyy-ss-mm-hh") + ".log");
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

void Logger::messageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    QString log = QObject::tr("[%1] [%2] [%3] [%4] %5")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss:msmsms"))
                      .arg(Logger::contextNames.value(type))
                      .arg(QString(context.file).section('\\', -1))
                      .arg(context.line)
                      .arg(msg);
    logFile->write(log.toUtf8());
    logFile->flush();
}
