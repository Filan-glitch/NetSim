QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Protocols/header.cpp \
    Protocols/headerAttribute.cpp \
    Protocols/headernotfoundexception.cpp \
    Protocols/tcp.cpp \
    Protocols/udp.cpp \
    main.cpp \
    process.cpp \
    Ansichten/mainwindow.cpp


HEADERS += \
    Ansichten/mainwindow.h \
    Protocols/header.h \
    Protocols/headerAttribute.h \
    Protocols/headernotfoundexception.h \
    Protocols/tcp.h \
    Protocols/udp.h \
    process.h


FORMS += \
    Ansichten/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
