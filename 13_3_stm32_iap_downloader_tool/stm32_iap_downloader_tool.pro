QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

TRANSLATIONS = src/res/tr/app_zh_CN.ts

# for support hanzi
# https://blog.csdn.net/libaineu2004/article/details/19245205
win32: {
    QMAKE_CXXFLAGS += /utf-8
}

CONFIG += c++11

SOURCES += \
    src/core/core.cpp \
    src/core/hexfilereader.cpp \
    src/file/binaryfile.cpp \
    src/file/directoryutil.cpp \
    src/finding_serial_device/findingserialdevice.cpp \
    src/main.cpp \
    src/protocol/comm_interface.cpp \
    src/protocol/command.cpp \
    src/protocol/crc.cpp \
    src/protocol/protocolmanager.cpp \
    src/protocol/work.cpp \
    src/protocol/workmanager.cpp \
    src/uart/myserialport.cpp \
    src/ui/iapdownloadertooldialog.cpp \
    src/utils/byteutil.cpp \
    src/utils/stringutil.cpp

HEADERS += \
    src/core/core.h \
    src/core/hexfilereader.h \
    src/file/binaryfile.h \
    src/file/directoryutil.h \
    src/finding_serial_device/findingserialdevice.h \
    src/protocol/comm_interface.h \
    src/protocol/command.h \
    src/protocol/crc.h \
    src/protocol/protocolmanager.h \
    src/protocol/work.h \
    src/protocol/workmanager.h \
    src/uart/myserialport.h \
    src/ui/iapdownloadertooldialog.h \
    src/utils/byteutil.h \
    src/utils/stringutil.h

FORMS += \
    src/ui/iapdownloadertooldialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res/res.qrc

DISTFILES += \
    src/res/qss/theme.qss

