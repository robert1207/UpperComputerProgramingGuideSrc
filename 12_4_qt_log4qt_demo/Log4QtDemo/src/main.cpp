#include "ui/demodialog.h"

#include <QApplication>

#include "log4qt_init_helper_by_coding.h"

#include "loggerstatic.h"
#include "loggerobject.h"
#include "loggerobjectprio.h"


#include "log4qt/logger.h" //每个使用log4qt的类都需要包含此头文件

//在类的cpp文件中，使用此静态方法声明logger（此方法比较通用）
//第二个参数写类名字，因此，输出的log条目中包含其对应的类名
LOG4QT_DECLARE_STATIC_LOGGER(logger, Main)


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DemoDialog w;
    w.show();

    /*
    //使用config 配置Log4Qt
    //把源代码目录中的"log4qt.properties"文件复制到编译好的可执行文件所在的目录
    //QString configFileAbsPath = QCoreApplication::applicationFilePath() + QStringLiteral(".log4qt.properties");
    QString configFileAbsPath  = QCoreApplication::applicationDirPath() +"/"+ QStringLiteral("log4qt.properties");
    SetupLog4QtByConfigWithConfigFileAbsPath(configFileAbsPath);
    */


    //使用纯代码配置Log4Qt
    QString logSavingDirAbsPath  = QCoreApplication::applicationDirPath();
    SetupLog4QtByCodingWithLogSavingDirAbsPath(logSavingDirAbsPath);


    //可以使用以下三种方式编写Log输出条目
    //1.log4qt基本的logger输出
    logger()->debug() << "example ####11#####  logger()->debug()";
    logger()->error() << "example ####11#####  logger()->error()";

    //2.log4qt基本的宏定义输出
    l4qError() << "example ####22#####  l4qError() ";
    l4qError(QStringLiteral("example ####22#####  l4qError()  %1"), 10);

    //3.使用qt平台的Log库输出，（Log4Qt会监听qt的log的输出，并统一输出到Log文件中）
    qDebug() << "example ####33#####  qDebug()\n\n\n";


    //此三个类为log4qt源码中的example中的代码，此处借用的目的是，展示在类中怎样引入logger
    LoggerObject object1;
    LoggerObjectPrio object2;
    LoggerStatic object3;

    int ret =  a.exec();

    //ShutDownLog4QtByConfig();//exec()执行完成后，才关闭logger
    ShutDownLog4QtByCoding();//exec()执行完成后，才关闭logger
    return ret;
}





