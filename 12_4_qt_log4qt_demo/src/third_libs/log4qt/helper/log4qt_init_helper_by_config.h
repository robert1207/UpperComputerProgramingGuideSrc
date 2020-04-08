#ifndef LOG4QT_HELPER_BY_CONFIG_H
#define LOG4QT_HELPER_BY_CONFIG_H

#include "log4qt/logger.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/loggerrepository.h"
#include "log4qt/consoleappender.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/logmanager.h"
#include "log4qt/fileappender.h"

#include <QDebug>


extern void SetupLog4QtByConfigWithConfigFileAbsPath(QString config_file_abs_path);
extern void ShutDownLog4QtByConfig();



#endif // LOG4QT_HELPER_H
