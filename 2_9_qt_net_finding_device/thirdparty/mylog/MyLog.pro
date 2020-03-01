# MyLog is a log-lib for Qt applications.
# Copyright (C) <2019>  <Robert Zhang> e-mail:robert.cysy@gmail.com

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

include($$PWD/config.pri)

TARGET = mylog
TEMPLATE = lib
VERSION = 1.0.1

DEFINES += MY_LOG_LIBRARY

SOURCES += \
        src/console_logger.cpp \
        src/file_logger.cpp \
        src/log_level.cpp \
        src/logger_interface.cpp \
        src/my_log_export.cpp

HEADERS += \
        src/console_logger.h \
        src/file_logger.h \
        src/log_level.h \
        src/logger_interface.h \
        src/my_log.h \
        src/my_log_export.h \
        src/my_log_export_global.h \
        src/printf_color.h \
        src/singletone/call_once.h \
        src/singletone/singleton.h

DISTFILES += \
        todo \
        version_changes \
        LICENSE \
        README.md \
        README.zh-cn.md

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
