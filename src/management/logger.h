#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QFile>
#include <QHash>

namespace NetSim {
class Logger;
}

class Logger {
public:
  static void init();

  static void clean();

  static void messageOutput(QtMsgType type, const QMessageLogContext &context,
                            const QString &msg);

private:
  static QFile *logFile;

  static bool isInit;

  static QHash<QtMsgType, QString> contextNames;
};

#endif // LOGGER_H
