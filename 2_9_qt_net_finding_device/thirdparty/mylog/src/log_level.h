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

#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

namespace MyLogNS {

enum LogLevel {
    Info = 0,
    Debug,
    Error
};

static const char level_info[]  = "INFO ";
static const char level_debug[] = "DEBUG";
static const char level_error[] = "ERROR";

extern const char* LevelToText(LogLevel level);

} //namespace MyLogNS

#endif // LOG_LEVEL_H
