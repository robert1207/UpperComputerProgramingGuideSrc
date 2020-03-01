#Config
#CONFIG += static
CONFIG += release
macx {
    CONFIG += c++11
}
win32 {
    CONFIG += c++11
}
CONFIG += warn_on thread exceptions rtti stl

#output
OBJECTS_DIR = _build/obj
MOC_DIR = _build
#move the lib file in to project folder
macx {
    DESTDIR = $$PWD
}
win32 {
    DESTDIR = $$PWD
}

# test config
LIST = thread exceptions rtti stl
for(f, LIST) {
    !CONFIG($$f) {
        warning("Add '$$f' to CONFIG, or you will meet some problems.")
    }
}

