#ifndef LOG4QT_HELPER_BY_CODING_H
#define LOG4QT_HELPER_BY_CODING_H

#include "log4qt/logger.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/logmanager.h"

//layouts
#include "log4qt/ttcclayout.h"

//appenders
#include "log4qt/consoleappender.h"
#include "log4qt/fileappender.h"
#include "log4qt/rollingfileappender.h"

#include <QDebug>


extern void SetupLog4QtByCodingWithLogSavingDirAbsPath(QString log_saving_dir_abs_path);
extern void ShutDownLog4QtByCoding();


#endif // LOG4QT_HELPER_H
