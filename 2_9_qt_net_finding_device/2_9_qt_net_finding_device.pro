QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#MyLog lib
#git clone https://github.com/robert1207/MyLog
include($$PWD/thirdparty/mylog/mylogsrc.pri)

#singleinstance
include($$PWD/thirdparty/singleinstance/singleinstancesrc.pri)



SOURCES += \
    command/command.cpp \
    command/crc.cpp \
    device_finding/devicefinder.cpp \
    device_finding/deviceinfo.cpp \
    device_finding/protocolfindingdevicemanager.cpp \
    main.cpp \
    net/comm.cpp \
    net/netmanager.cpp \
    net/tcpcomm.cpp \
    net/udpcomm.cpp \
    ui/device_connect_dialog/deviceconnectdialog.cpp \
    utils/byteutil.cpp

HEADERS += \
    command/command.h \
    command/crc.h \
    device_finding/devicefinder.h \
    device_finding/deviceinfo.h \
    device_finding/protocolfindingdevicemanager.h \
    net/comm.h \
    net/netmanager.h \
    net/tcpcomm.h \
    net/udpcomm.h \
    ui/device_connect_dialog/deviceconnectdialog.h \
    utils/byteutil.h

FORMS += \
    ui/device_connect_dialog/deviceconnectdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
