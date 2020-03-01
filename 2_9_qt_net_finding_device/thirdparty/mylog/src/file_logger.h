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

#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "logger_interface.h"

#include <QString>
#include <QFile>
#include <QTextStream>
namespace MyLogNS {

class FileLogger : public LoggerInterface
{
public:
    FileLogger();
    virtual ~FileLogger();

    enum OPEN_FILE_ERROR {
            NoError = 0,
            DirNotExist = -1,
            OpenFileFailed = -2,
        };

    virtual void open();
    virtual void close();
    virtual void write(LogLevel level, const QString &msg, bool is_shift_to_next_line);

    int open_log_file_at_dir(const QString &path);
    const char* get_error_str(int result_code);
    const char* get_log_file_abs_path();

private:
    QFile f;
    QTextStream out;

    const char* m_saved_error_dir;
    const char* m_saved_file_path;
    const char* m_log_file_abs_path;
};

} //namespace MyLogNS

#endif // FILE_LOGGER_H
