#include "log4qt_init_helper_by_coding.h"


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

void SetupLog4QtByCodingWithLogSavingDirAbsPath(QString log_saving_dir_abs_path)
{

    auto rootLogger = Log4Qt::Logger::rootLogger();


    //get this document by reading the log4qt source code

    //All the layouts that can be used are list as below:
    //BinaryLayout
    //BinaryToTextLayout
    //DatabaseLayout : he class DatabaseLayout outputs loggin event into sql table.
    //PatternLayout : The class PatternLayout outputs a logging event based on a  pattern string.
                    //for patterns, such as:  F : file name    M : method name   L : line number
    //SimpleLayout : The class SimpleLayout outputs the level and message of a logging event.
    //SimpleTimeLayout : The class SimpleTimeLayout outputs the time, logger name, thread, level and message of a loggin  event.
    //TTCCLayout : The class TTCCLayout outputs the time, thread, logger and nested
                    // diagnostic context information of a logging event.
    //XMLLayout :

    // Create a layout
    auto *layout = new Log4Qt::TTCCLayout();
    layout->setName(QStringLiteral("My Layout"));
    layout->setDateFormat("dd.MM.yyyy hh:mm:ss.zzz");
    layout->activateOptions();


    //All the appenders that can be used are list as below:
    //AsyncAppender : The class AsyncAppender lets users log events asynchronously.
    //BinaryFileAppender : Log binary arrays
    //BinaryWriterAppender
    //ColorConsoleAppender : only work at win32
    //ConsoleAppender ::The class ConsoleAppender appends to stdout or stderr.
    //DailyFileAppender
    //DailyRollingFileAppender : The class DailyRollingFileAppender extends FileAppender so that the
                            //underlying file is rolled over at a specified frequency.
    //DatabaseAppender : The class DatabaseAppender appends log events to a sql database.
    //FileAppender : The class FileAppender appends log events to a file.
    //MainThreadAppender : The class MainThreadAppender uses the QEvent system to write
                            //log from not main threads within the main thread.
    //RollingBinaryFileAppender
    //RollingFileAppender : The class RollingFileAppender extends FileAppender to backup
                            //the log files when they reach a certain size.
    //SignalAppender
    //SystemLogAppender
    //TelnetAppender : The class TelnetAppender appends log events to a read-only socket (telnet)
    //WDCAppender : only work at win32
    //WriterAppender : The class WriterAppender appends log events to a QTextStream.


    // Create a console appender
    Log4Qt::ConsoleAppender *consoleAppender =
            new Log4Qt::ConsoleAppender(layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
    consoleAppender->setName(QStringLiteral("My console Appender"));
    consoleAppender->activateOptions();
    rootLogger->addAppender(consoleAppender);

    /*
    // Create a file appender
    Log4Qt::FileAppender *fileAppender =
            new Log4Qt::FileAppender(layout, saving_path + "/basic.log", true);//true for append
    fileAppender->setName(QStringLiteral("My file appender"));
    fileAppender->activateOptions();
    rootLogger->addAppender(fileAppender);
    */

    //Create a rolling file appender
    Log4Qt::RollingFileAppender *rollingFileAppender =
            new Log4Qt::RollingFileAppender(layout, log_saving_dir_abs_path + "/basic.log", true);
    rollingFileAppender->setName(QStringLiteral("My rolling file appender"));
    rollingFileAppender->activateOptions();
    rootLogger->addAppender(rollingFileAppender);


    rootLogger->setLevel(Log4Qt::Level::ALL_INT);
    Log4Qt::LogManager::setHandleQtMessages(true);

    PrintLogHead();
}

void ShutDownLog4QtByCoding()
{
    auto logger = Log4Qt::Logger::rootLogger();
    PrintLogTail();
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}
