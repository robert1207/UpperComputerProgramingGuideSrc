QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = BreakpadDemo
TEMPLATE = app

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# link qBreakpad library
include($$PWD/third_libs/breakpad/breakpadsrc.pri)


SOURCES += \
    src/main.cpp \
    src/ui/crashreportdialog/crashreportdialog.cpp \
    src/ui/demodialog.cpp

HEADERS += \
    src/ui/crashreportdialog/crashreportdialog.h \
    src/ui/demodialog.h

FORMS += \
    src/ui/crashreportdialog/crashreportdialog.ui \
    src/ui/demodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
