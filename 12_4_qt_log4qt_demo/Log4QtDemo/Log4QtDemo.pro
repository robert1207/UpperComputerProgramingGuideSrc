QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

#log4qt
include($$PWD/src/third_libs/log4qt/log4qtlib.pri)

SOURCES += \
    src/main.cpp \
    src/loggerstatic.cpp \
    src/loggerobject.cpp \
    src/loggerobjectprio.cpp \
    src/ui/demodialog.cpp

HEADERS += \
    src/loggerstatic.h \
    src/loggerobject.h \
    src/loggerobjectprio.h \
    src/ui/demodialog.h

FORMS += \
    src/ui/demodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





