QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/management/logger.cpp \
    src/management/packagedatabase.cpp \
    src/management/packagetablemodel.cpp \
    src/management/simulationmanager.cpp \
    src/models/dnsentry.cpp \
    src/models/package.cpp \
    src/models/process.cpp \
    src/network/cablenotfoundexception.cpp \
    src/network/client.cpp \
    src/network/host.cpp \
    src/network/natentry.cpp \
    src/network/networkcard.cpp \
    src/network/router.cpp \
    src/network/server.cpp \
    src/models/ipaddress.cpp \
    src/models/macaddress.cpp \
    src/models/port.cpp \
    src/network/socket.cpp \
    src/protocols/dns.cpp \
    src/protocols/header.cpp \
    src/protocols/headerAttribute.cpp \
    src/protocols/headerattributenotfoundexception.cpp \
    src/protocols/headernotfoundexception.cpp \
    src/protocols/headerutil.cpp \
    src/protocols/http.cpp \
    src/protocols/ipv4.cpp \
    src/protocols/mac.cpp \
    src/protocols/tcp.cpp \
    src/protocols/udp.cpp \
    src/views/dialogs/about_dialog.cpp \
    src/views/dialogs/client_dialog.cpp \
    src/views/dialogs/router_dialog.cpp \
    src/views/dialogs/server_dialog.cpp \
    src/views/dialogs/settingsdialog.cpp \
    src/views/widgets/clientwidget.cpp \
    src/views/widgets/networktab.cpp \
    src/views/widgets/routerwidget.cpp \
    src/views/widgets/serverwidget.cpp \
    src/views/windows/simulationwindow.cpp \
    src/views/windows/welcomewindow.cpp


HEADERS += \
    src/management/logger.h \
    src/management/packagedatabase.h \
    src/management/packagetablemodel.h \
    src/management/simulationmanager.h \
    src/models/dnsentry.h \
    src/models/package.h \
    src/models/process.h \
    src/network/cablenotfoundexception.h \
    src/network/client.h \
    src/network/host.h \
    src/network/natentry.h \
    src/network/networkcard.h \
    src/network/router.h \
    src/network/server.h \
    src/models/ipaddress.h \
    src/models/macaddress.h \
    src/models/port.h \
    src/network/socket.h \
    src/protocols/dns.h \
    src/protocols/header.h \
    src/protocols/headerAttribute.h \
    src/protocols/headerattributenotfoundexception.h \
    src/protocols/headernotfoundexception.h \
    src/protocols/headerutil.h \
    src/protocols/http.h \
    src/protocols/ipv4.h \
    src/protocols/mac.h \
    src/protocols/tcp.h \
    src/protocols/udp.h \
    src/views/dialogs/about_dialog.h \
    src/views/dialogs/client_dialog.h \
    src/views/dialogs/router_dialog.h \
    src/views/dialogs/server_dialog.h \
    src/views/dialogs/settingsdialog.h \
    src/views/widgets/clientwidget.h \
    src/views/widgets/networktab.h \
    src/views/widgets/routerwidget.h \
    src/views/widgets/serverwidget.h \
    src/views/windows/simulationwindow.h \
    src/views/windows/welcomewindow.h


FORMS += \
    src/views/dialogs/about_dialog.ui \
    src/views/dialogs/client_dialog.ui \
    src/views/dialogs/router_dialog.ui \
    src/views/dialogs/server_dialog.ui \
    src/views/dialogs/settingsdialog.ui \
    src/views/windows/simulationwindow.ui \
    src/views/windows/welcomewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/ressources.qrc \
    docs.qrc
