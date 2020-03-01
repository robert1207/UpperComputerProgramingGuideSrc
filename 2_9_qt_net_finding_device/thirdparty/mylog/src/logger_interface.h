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

#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#include <QDebug>
#include "log_level.h"

namespace MyLogNS {

class LoggerInterface
{
public:
    LoggerInterface();
    virtual ~LoggerInterface();
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void write(MyLogNS::LogLevel level, const QString &msg, bool is_shift_to_next_line) = 0;
};

} //namespace MyLogNS

#endif // LOGGER_INTERFACE_H
