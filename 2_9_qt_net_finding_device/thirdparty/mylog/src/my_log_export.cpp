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

#include "my_log_export.h"

#include <QDebug>
#include <QString>
#include <QDateTime>

#include "my_log.h"

namespace MyLogNS {

/***************************** Logger ****************************/
static bool is_alive = false;

MyLogExport::MyLogExport() :
    is_enable_auto_new_line(true),
    is_show_level_str(true),
    is_show_timestamp(true),
    is_show_file_name(false),
    is_show_function_name(true),
    is_show_line_number(true),
    mutex_log_count(0)
{
    mutex = new QMutex();
    is_alive = true;
}

MyLogExport::~MyLogExport() {

    is_alive = false;
    while(mutex_log_count != 0) {;}

    foreach(LoggerInterface *p, m_logger_list) {
        if(p != nullptr) {
            p->close();
            delete p;
            p = nullptr;
        }
    }

    delete mutex;
}

void MyLogExport::installer_logger(LoggerInterface *logger) {
    if(logger != nullptr) {
        logger->open();
        m_logger_list.append(logger);
    }
}

bool MyLogExport::is_has_logger() {
    if(m_logger_list.size() > 0) {
        return true;
    } else {
        return false;
    }
}

QString get_format_data_time() {
    QString datatime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    return datatime;
}

void MyLogExport::log_out(const QString &msg) {

    QString out_put_msg;

    out_put_msg.append("#");

    //level str
    if(is_show_level_str) out_put_msg.append(QString(LevelToText(m_log_level))+" ");

    //timestamp
    if(is_show_timestamp) out_put_msg.append(get_format_data_time()+" ");

    if (is_show_file_name) {
        out_put_msg.append(QString(m_file_name)+" ");
    }

    if (is_show_function_name) {
        out_put_msg.append("["+QString(m_func_name)+"] ");
    }

    if(is_show_line_number) {
        out_put_msg.append(QString::number(m_line_number)+": ");
    }

    //log content
    out_put_msg.append(msg);

    do_write(m_log_level, out_put_msg);
}

void MyLogExport::do_write(LogLevel log_level, const QString &msg) {
    foreach(LoggerInterface *p, m_logger_list) {
        if(p != nullptr) {
            p->write(log_level, msg, is_enable_auto_new_line);
        }
    }
}


/***************************** Helper ****************************/

MyLogExport::Helper::~Helper()
{
    if (m_no_log) return;

    if (is_alive == false) return;

    if (!MyLogIns.is_has_logger()) { return; }

    try {
        write_log();
    }
    catch(std::exception&) {
        Q_ASSERT(false);// catch to add details about the crash
        throw;
    }
}

void MyLogExport::Helper::write_log()
{
    MyLogIns.mutex->lock();
    MyLogIns.mutex_log_count += 1;

    if(is_alive) {
        MyLogIns.set_file_line(m_log_level, m_file_name, m_line_number, m_func_name);
        MyLogIns.log_out(buffer);
    }
    MyLogIns.mutex_log_count -= 1;
    MyLogIns.mutex->unlock();
}

} //namespace MyLogNS

