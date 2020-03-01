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

message("MyLog_src_attached")

#DEFINES += MYLOG_NO_I_OUTPUT
#DEFINES += MYLOG_NO_D_OUTPUT
#DEFINES += MYLOG_NO_E_OUTPUT

CONFIG += thread exceptions rtti stl

INCLUDEPATH += $$PWD/src/

SOURCES += \
        $$PWD/src/console_logger.cpp \
        $$PWD/src/file_logger.cpp \
        $$PWD/src/log_level.cpp \
        $$PWD/src/my_log_export.cpp \
        $$PWD/src/logger_interface.cpp

HEADERS += \
        $$PWD/src/console_logger.h \
        $$PWD/src/file_logger.h \
        $$PWD/src/my_log.h \
        $$PWD/src/log_level.h \
        $$PWD/src/logger_interface.h \
        $$PWD/src/printf_color.h \
        $$PWD/src/singletone/call_once.h \
        $$PWD/src/singletone/singleton.h \
        $$PWD/src/my_log_export.h \
        $$PWD/src/my_log_export_global.h
        

OTHER_FILES += \
        $$PWD/todo \
        $$PWD/version_changes \
        $$PWD/LICENSE \
        $$PWD/README.md \
        $$PWD/README.zh-cn.md
