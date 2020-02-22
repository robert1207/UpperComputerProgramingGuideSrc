
message("singleinstance_src_attached")

CONFIG += thread exceptions rtti stl

INCLUDEPATH += $$PWD/src/


SOURCES += \
        $$PWD/src/singleinstance.cpp
       


HEADERS += \
        $$PWD/src/singleinstance.h \
        $$PWD/src/singletone/singleton.h \
        $$PWD/src/singletone/call_once.h


