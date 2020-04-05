#include "log4qt_init_helper_by_config.h"


static void PrintLogHead() {
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          START                               #"));
    logger->info(QStringLiteral("################################################################"));
}

static void PrintLogTail() {
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          STOP                                #"));
    logger->info(QStringLiteral("################################################################"));
}

void SetupLog4QtByConfigWithConfigFileAbsPath(QString config_file_abs_path)
{
    if (QFile::exists(config_file_abs_path)) {
        //configureAndWatch
        Log4Qt::PropertyConfigurator::configure(config_file_abs_path);
    } else {
        qDebug() << "Can't find log4qt-config-file path:" << config_file_abs_path;
    }

    PrintLogHead();
}

void ShutDownLog4QtByConfig()
{
    auto logger = Log4Qt::Logger::rootLogger();
    PrintLogTail();
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}
