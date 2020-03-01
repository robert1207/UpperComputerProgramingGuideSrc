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

#include "file_logger.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QTextCodec>
#include <QStandardPaths>

namespace MyLogNS {

FileLogger::FileLogger()
{

}

FileLogger::~FileLogger() {

}

void FileLogger::open() {

}

void FileLogger::close() {
    if (f.isOpen()) {
        f.close();
    }
}

void FileLogger::write(LogLevel level, const QString &msg, bool is_shift_to_next_line) {
    Q_UNUSED(level);

    if(is_shift_to_next_line) {
         out << msg << endl;
    } else {
        out << msg;
        out.flush();
    }
}

QString get_data_time_for_file_name() {
    QString datatime = QDateTime::currentDateTime().toString("yyyy-MM-dd_HHmmsszzz");
    return datatime;
}

int FileLogger::open_log_file_at_dir(const QString &path) {
    QString absPath = path;
    if(!QDir::isAbsolutePath(absPath)) {
        QStringList path_list = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
        QString writeable_path = path_list[0];

        //QString appDirPath = qApp->applicationDirPath();
       absPath = QDir::cleanPath(writeable_path + "/" + path);
    }
    Q_ASSERT(QDir::isAbsolutePath(absPath));

    QDir().mkpath(absPath);

    QDir dir(absPath);
    if(!dir.exists()) {
        m_saved_error_dir =  qPrintable(absPath);
       return DirNotExist;
    }

    QString file_name = "Log_" + get_data_time_for_file_name() +".log";
    QString absFilePath = dir.absoluteFilePath(file_name);

    f.setFileName(absFilePath);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        m_saved_file_path = qPrintable(absFilePath);
        return OpenFileFailed;
    }

    out.setDevice(&f);
    out.setCodec(QTextCodec::codecForName("UTF-8"));

    m_log_file_abs_path = qPrintable(absFilePath);

    return 0;
}

const char* FileLogger::get_error_str(int result_code) {
    QString result;
      switch (result_code) {
          case DirNotExist : result = QString("directory is not exist, path:") + m_saved_error_dir; break;
          case OpenFileFailed : result = QString("open file failed, path:" ) + m_saved_file_path; break;
          case NoError : result = "no error"; break;

          default: result = "unknow error"; break;
      }

      return qPrintable(result);
}

const char* FileLogger::get_log_file_abs_path() {
    return m_log_file_abs_path;
}

} //namespace MyLogNS
