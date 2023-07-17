QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/logger.cpp \
    src/main.cpp \
    src/network/client.cpp \
    src/network/host.cpp \
    src/network/process.cpp \
    src/network/router.cpp \
    src/network/server.cpp \
    src/network/socket.cpp \
    src/protocols/ipaddress.cpp \
    src/protocols/macaddress.cpp \
    src/protocols/port.cpp \
    src/views/widgets/mainwindow.cpp


HEADERS += \
    src/logger.h \
    src/network/client.h \
    src/network/host.h \
    src/network/process.h \
    src/network/router.h \
    src/network/server.h \
    src/network/socket.h \
    src/protocols/ipaddress.h \
    src/protocols/macaddress.h \
    src/protocols/port.h \
    src/views/widgets/mainwindow.h


FORMS += \
    src/views/widgets/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/ressources.qrc
