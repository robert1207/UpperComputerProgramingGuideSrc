message("Breakpad_src_been_attached")


## google-breakpad
include($$PWD/thirdparty/breakpad.pri)


INCLUDEPATH += $$PWD/src

#CONFIG += debug_and_release
#CONFIG += warn_on
CONFIG += thread exceptions rtti stl

SOURCES += \
        $$PWD/src/BreakpadHandler.cpp \
        $$PWD/src/BreakpadHttpUploader.cpp


HEADERS += \
        $$PWD/src/BreakpadHandler.h \
        $$PWD/src/BreakpadHttpUploader.h


CONFIG += warn_on
CONFIG += thread exceptions rtti stl

#  for generate dpb files at windows
win32-msvc* {
    QMAKE_LFLAGS_RELEASE += /MAP
    QMAKE_CFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /debug /opt:ref
}

* {
    QMAKE_CFLAGS_RELEASE += -g
    QMAKE_CXXFLAGS_RELEASE += -g
    QMAKE_CFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE -= -O2
    #QMAKE_LFLAGS_RELEASE = -mthreads -Wl
}

# without c++11 & AppKit library compiler can't solve address for symbols
CONFIG += c++11
macx: LIBS += -framework AppKit
