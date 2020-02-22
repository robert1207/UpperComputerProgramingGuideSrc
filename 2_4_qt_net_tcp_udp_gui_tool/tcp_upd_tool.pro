#-------------------------------------------------
#
# Project created by QtCreator 2019-07-31T11:10:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tcp_udp_tool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

#MyLog lib
#git clone https://github.com/robert1207/MyLog
include($$PWD/src/thirdparty/mylog/mylogsrc.pri)

#singleinstance
include($$PWD/src/thirdparty/singleinstance/singleinstancesrc.pri)

SOURCES += \
        src/main.cpp \
        src/net/comm.cpp \
        src/net/netmanager.cpp \
        src/net/tcpcomm.cpp \
        src/net/udpcomm.cpp \
        src/ui/netdialog.cpp \
        src/utils/stringutil.cpp \
        src/views/toast/toast.cpp

HEADERS += \
        src/net/tcpcomm.h \
        src/net/comm.h \
        src/net/netmanager.h \
        src/net/udpcomm.h \
        src/ui/netdialog.h \
        src/utils/stringutil.h \
        src/views/toast/toast.h

FORMS += \
        src/ui/dialog.ui \
        src/views/toast/toast.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/thirdparty/readme.txt
