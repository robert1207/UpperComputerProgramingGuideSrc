#-------------------------------------------------
#
# Project created by QtCreator 2019-07-08T11:06:49
#
#-------------------------------------------------
include($$PWD/config.pri)
QT       += core

TARGET = singleinstance
TEMPLATE = lib
#VERSION = 1.0.0

DEFINES += SINGLEINSTANCE_LIBRARY

SOURCES += \
    


HEADERS += \
        
unix {
    target.path = /usr/lib
    INSTALLS += target
}



