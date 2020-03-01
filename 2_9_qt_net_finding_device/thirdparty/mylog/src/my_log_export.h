/* MyLog is a log-lib for Qt applications.
 * Copyright (C) <2019>  <Robert Zhang> e-mail:robert.cysy@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MY_LOG_EXPORT_H
#define MY_LOG_EXPORT_H

#include "my_log_export_global.h"

#include <QString>
#include <QTextStreamFunction>
#include <QDebug>
#include <QThreadPool>

#include "singletone/singleton.h"
#include "log_level.h"
#include "logger_interface.h"

//include header for user
#include "console_logger.h"
#include "file_logger.h"

namespace MyLogNS {

class MyLogExport
{
public:
    MyLogExport();
    ~MyLogExport();

    //each log calling is using an object of 'Helper'
    class Helper
    {
    public:
        explicit Helper() :
            qtDebug(&buffer),
            m_no_log(false)
        {}
        ~Helper();
        //making sure the single 'Helper' object is hold itself's log settings at multi-thread
        inline Helper& set_file_line(const char *file, int line, const char *func_name) {
            m_file_name = file;
            m_line_number = line;
            m_func_name = func_name;
            return *this;
        }

        QDebug& info() { m_log_level = LogLevel::Info; return qtDebug; }
        QDebug& debug(){ m_log_level = LogLevel::Debug; return qtDebug; }
        QDebug& error(){ m_log_level = LogLevel::Error; return qtDebug; }
        QDebug& no_log(){ m_no_log = true; return qtDebug; }
    private:
        void write_log();
        QString buffer;
        QDebug qtDebug;

        //code file name and line number
        LogLevel m_log_level;
        const char *m_file_name;
        int m_line_number;
        const char *m_func_name;

        bool m_no_log;
    };

public:
    bool is_enable_auto_new_line;       //default true
    bool is_show_level_str;                 //default true
    bool is_show_timestamp;                 //default true
    bool is_show_file_name;                 //default false
    bool is_show_function_name;          //default true
    bool is_show_line_number;             //default true

    int mutex_log_count;
    QMutex *mutex;

    void installer_logger(LoggerInterface *logger);
    bool is_has_logger();

    void log_out(const QString &msg);
    void do_write(LogLevel log_level, const QString &msg);

    inline void set_file_line(LogLevel level, const char *file, int line, const char *func_name) {
        m_log_level = level;
        m_file_name = file;
        m_line_number = line;
        m_func_name = func_name;
    }

private:

    //code file name and line number
    LogLevel m_log_level;
    const char *m_file_name;
    int m_line_number;
    const char *m_func_name;

    QList<LoggerInterface *> m_logger_list;

};

} //namespace MyLogNS

#endif // MY_LOG_EXPORT_H
