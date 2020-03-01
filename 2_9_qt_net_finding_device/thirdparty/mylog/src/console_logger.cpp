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

#include "console_logger.h"
#include "printf_color.h"

namespace MyLogNS {

ConsoleLogger::ConsoleLogger()
{

}

ConsoleLogger::~ConsoleLogger()
{

}

void ConsoleLogger::open() {
    //qDebug("ConsoleLogger::open()");
}

void ConsoleLogger::close() {
    //qDebug("ConsoleLogger::close()");
}

void ConsoleLogger::write(LogLevel level, const QString &msg, bool is_shift_to_next_line) {
    if (level == Info) {
        printf(YELLOW"%s" NONE, qPrintable(msg));
    } else if (level == Debug) {
        printf(GREEN"%s" NONE, qPrintable(msg));
    } else if(level == Error){
        printf(RED"%s" NONE, qPrintable(msg));
    }
    if (is_shift_to_next_line) printf("\r\n");
    fflush(stdout);
}

} //namespace MyLogNS

