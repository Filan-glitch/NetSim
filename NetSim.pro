QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++21

VERSION = 2.0.0.0

TARGET= NetSim

RC_ICONS = icon.ico
ICON = icon.icns

DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES += \
    src/main.cpp \
    src/management/logger.cpp \
    src/management/packagedatabase.cpp \
    src/management/packagetablemodel.cpp \
    src/management/simulationmanager.cpp \
    src/hardware/cablenotfoundexception.cpp \
    src/hardware/client.cpp \
    src/hardware/host.cpp \
    src/hardware/networkcard.cpp \
    src/hardware/router.cpp \
    src/hardware/server.cpp \
    src/software/00_common/strategies/dnsstrategy.cpp \
    src/software/00_common/strategies/httpstrategy.cpp \
    src/software/00_common/strategies/tcpclientconnectionclosestrategy.cpp \
    src/software/00_common/strategies/tcpclienthandshakestrategy.cpp \
    src/software/00_common/strategies/tcpserverconnectionclosestrategy.cpp \
    src/software/00_common/strategies/tcpserverhandshakestrategy.cpp \
    src/software/00_common/header.cpp \
    src/software/00_common/headerAttribute.cpp \
    src/software/00_common/headerattributenotfoundexception.cpp \
    src/software/00_common/headernotfoundexception.cpp \
    src/software/00_common/headerutil.cpp \
    src/software/00_common/package.cpp \
    src/software/00_common/process.cpp \
    src/software/01_application_layer/dns.cpp \
    src/software/01_application_layer/http.cpp \
    src/software/01_application_layer/dnsentry.cpp \
    src/software/02_transport_layer/port.cpp \
    src/software/02_transport_layer/socket.cpp \
    src/software/02_transport_layer/tcp.cpp \
    src/software/02_transport_layer/udp.cpp \
    src/software/03_network_layer/ipaddress.cpp \
    src/software/03_network_layer/ipv4.cpp \
    src/software/03_network_layer/natentry.cpp \
    src/software/04_network_access_layer/mac.cpp \
    src/software/04_network_access_layer/macaddress.cpp \
    src/ui/dialogs/about_dialog.cpp \
    src/ui/dialogs/client_dialog.cpp \
    src/ui/dialogs/router_dialog.cpp \
    src/ui/dialogs/server_dialog.cpp \
    src/ui/dialogs/settingsdialog.cpp \
    src/ui/widgets/clientwidget.cpp \
    src/ui/widgets/networktab.cpp \
    src/ui/widgets/routerwidget.cpp \
    src/ui/widgets/serverwidget.cpp \
    src/ui/windows/simulationwindow.cpp \
    src/ui/windows/welcomewindow.cpp


HEADERS += \
    src/management/logger.h \
    src/management/packagedatabase.h \
    src/management/packagetablemodel.h \
    src/management/simulationmanager.h \
    src/hardware/cablenotfoundexception.h \
    src/hardware/client.h \
    src/hardware/host.h \
    src/hardware/networkcard.h \
    src/hardware/router.h \
    src/hardware/server.h \
    src/software/00_common/strategies/dnsstrategy.h \
    src/software/00_common/strategies/httpstrategy.h \
    src/software/00_common/strategies/ipackagestrategy.h \
    src/software/00_common/strategies/tcpclientconnectionclosestrategy.h \
    src/software/00_common/strategies/tcpclienthandshakestrategy.h \
    src/software/00_common/strategies/tcpserverconnectionclosestrategy.h \
    src/software/00_common/strategies/tcpserverhandshakestrategy.h \
    src/software/00_common/header.h \
    src/software/00_common/headerAttribute.h \
    src/software/00_common/headerattributenotfoundexception.h \
    src/software/00_common/headernotfoundexception.h \
    src/software/00_common/headerutil.h \
    src/software/00_common/package.h \
    src/software/00_common/process.h \
    src/software/01_application_layer/dns.h \
    src/software/01_application_layer/http.h \
    src/software/01_application_layer/dnsentry.h \
    src/software/02_transport_layer/port.h \
    src/software/02_transport_layer/socket.h \
    src/software/02_transport_layer/tcp.h \
    src/software/02_transport_layer/udp.h \
    src/software/03_network_layer/ipaddress.h \
    src/software/03_network_layer/ipv4.h \
    src/software/03_network_layer/natentry.h \
    src/software/04_network_access_layer/mac.h \
    src/software/04_network_access_layer/macaddress.h \
    src/ui/dialogs/about_dialog.h \
    src/ui/dialogs/client_dialog.h \
    src/ui/dialogs/router_dialog.h \
    src/ui/dialogs/server_dialog.h \
    src/ui/dialogs/settingsdialog.h \
    src/ui/widgets/clientwidget.h \
    src/ui/widgets/networktab.h \
    src/ui/widgets/routerwidget.h \
    src/ui/widgets/serverwidget.h \
    src/ui/windows/simulationwindow.h \
    src/ui/windows/welcomewindow.h


FORMS += \
    src/ui/dialogs/about_dialog.ui \
    src/ui/dialogs/client_dialog.ui \
    src/ui/dialogs/router_dialog.ui \
    src/ui/dialogs/server_dialog.ui \
    src/ui/dialogs/settingsdialog.ui \
    src/ui/windows/simulationwindow.ui \
    src/ui/windows/welcomewindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/ressources.qrc \
    docs.qrc
