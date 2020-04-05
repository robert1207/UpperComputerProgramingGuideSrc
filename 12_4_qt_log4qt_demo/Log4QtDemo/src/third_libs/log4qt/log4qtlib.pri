message("log4qt_lib_been_attached")

SOURCES += \
        $$PWD/helper/log4qt_init_helper_by_coding.cpp \
        $$PWD/helper/log4qt_init_helper_by_config.cpp

HEADERS += \
        $$PWD/helper/log4qt_init_helper_by_coding.h \
        $$PWD/helper/log4qt_init_helper_by_config.h

macx {
    INCLUDEPATH += $$PWD/helper
    INCLUDEPATH += $$PWD/include
    DEPENDPATH += $$PWD/include

    macx: LIBS += -L$$PWD/bin/ -llog4qt.1
}

win32 {
    INCLUDEPATH += $$PWD/helper
    INCLUDEPATH += $$PWD/include
    DEPENDPATH += $$PWD/include
       
    win32: LIBS += -L$$PWD/bin/ -llog4qt
}

DISTFILES += \
    $$PWD/log4qt.properties



