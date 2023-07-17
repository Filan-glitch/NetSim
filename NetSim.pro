QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/management/logger.cpp \
    src/models/package.cpp \
    src/models/process.cpp \
    src/network/client.cpp \
    src/network/host.cpp \
    src/network/router.cpp \
    src/network/server.cpp \
    src/models/ipaddress.cpp \
    src/models/macaddress.cpp \
    src/models/port.cpp \
    src/protocols/header.cpp \
    src/protocols/headerAttribute.cpp \
    src/protocols/headernotfoundexception.cpp \
    src/protocols/http.cpp \
    src/protocols/ipv4.cpp \
    src/protocols/mac.cpp \
    src/protocols/tcp.cpp \
    src/protocols/udp.cpp \\
    src/views/widgets/mainwindow.cpp


HEADERS += \
    src/management/logger.h \
    src/models/package.h \
    src/models/process.h \
    src/network/client.h \
    src/network/host.h \
    src/network/router.h \
    src/network/server.h \
    src/models/ipaddress.h \
    src/models/macaddress.h \
    src/models/port.h \
    src/protocols/header.h \
    src/protocols/headerAttribute.h \
    src/protocols/headernotfoundexception.h \
    src/protocols/http.h \
    src/protocols/ipv4.h \
    src/protocols/mac.h \
    src/protocols/tcp.h \
    src/protocols/udp.h \
    src/views/widgets/mainwindow.h


FORMS += \
    src/views/widgets/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/ressources.qrc
