QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/protocols/header.cpp \
    src/protocols/headerAttribute.cpp \
    src/protocols/headernotfoundexception.cpp \
    src/protocols/protocol.cpp \
    src/protocols/tcp.cpp \
    src/protocols/udp.cpp \
    src/views/widgets/mainwindow.cpp

HEADERS += \
    src/protocols/header.h \
    src/protocols/headerAttribute.h \
    src/protocols/headernotfoundexception.h \
    src/protocols/protocol.h \
    src/protocols/tcp.h \
    src/protocols/udp.h \
    src/views/widgets/mainwindow.h

FORMS += \
    src/views/widgets/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
