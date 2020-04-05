/******************************************************************************
 *
 * This file is part of Log4Qt library.
 *
 * Copyright (C) 2007 - 2020 Log4Qt contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#include "loggerstatic.h"

#include "log4qt/logger.h"//每个使用log4qt的类都需要包含此头文件
#include "log4qt/logmanager.h"


//在类的cpp文件中，使用此静态方法声明logger（此方法比较通用）
//第二个参数写类名字，因此，输出的log条目中包含其对应的类名
LOG4QT_DECLARE_STATIC_LOGGER(logger, LoggerStatic)

LoggerStatic::LoggerStatic()
{
    logger()->trace() << "ctor Debug output";
    logger()->info() << "Log4Qt Version String: " << Log4Qt::LogManager::version();
    logger()->info() << "Log4Qt Version Number: " << Log4Qt::LogManager::versionNumber().toString();
}

LoggerStatic::~LoggerStatic()
{
    logger()->trace() << "dtor Debug output";
}
