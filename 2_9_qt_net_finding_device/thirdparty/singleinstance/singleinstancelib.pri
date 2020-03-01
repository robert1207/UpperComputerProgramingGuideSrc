

message("singleinstance_lib_been_attached")

CONFIG += thread exceptions rtti stl

INCLUDEPATH += $$PWD/src/

HEADERS += \
        $$PWD/src/singleinstance.h


LIBS += \
        -L$$PWD -lsingleinstance


