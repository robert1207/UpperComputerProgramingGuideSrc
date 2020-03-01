#Config
#CONFIG += static
CONFIG += release
macx {
    CONFIG += c++11
}
CONFIG += warn_on thread exceptions rtti stl

#qt
QT -= gui
QT += core

#output
OBJECTS_DIR = _build/obj
MOC_DIR = _build
#mv built lib into *.pro's directory
DESTDIR = $$PWD
#DESTDIR = $$OUT_PWD


# test config
LIST = thread exceptions rtti stl
for(f, LIST) {
    !CONFIG($$f) {
        warning("Add '$$f' to CONFIG, or you will meet some problems.")
    }
}

