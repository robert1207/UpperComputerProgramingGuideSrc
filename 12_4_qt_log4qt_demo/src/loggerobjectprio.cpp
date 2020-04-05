#include "loggerobjectprio.h"

#include <QTimer>

#include "log4qt/logger.h"//每个使用log4qt的类都需要包含此头文件

//在类的cpp文件中，使用此静态方法声明logger（此方法比较通用）
//第二个参数写类名字，因此，输出的log条目中包含其对应的类名
LOG4QT_DECLARE_STATIC_LOGGER(logger, LoggerObjectPrio)

LoggerObjectPrio::LoggerObjectPrio(QObject *parent) : QObject(parent)
{
    auto *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LoggerObjectPrio::onTimeout);
    timer->start(1);
}

void LoggerObjectPrio::onTimeout()
{
    logger()->debug() << "Debug output";
    logger()->error() << "Error output";
}

