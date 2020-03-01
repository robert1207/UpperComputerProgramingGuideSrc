MyLog is a log-lib for Qt cross-platform applications. MyLog is stable and easy to use.

*Read this in other languages: [English][1], [简体中文][2]*

# Features
1. Colorful text console output ;
2. Support log levels of "info debug error";
3. Multi-thread safe;
4. Multi-threaded calls will not cause infinite memory growth;
5. Support write log into a file, console and self-made-logger;
6. Support self-implement logger;
7. MyLog is an open-source project;
8. Using MyLog is as easy as "qDebug()" and as powerfull as "qDebug()"(Cause MyLog is base on QDebug class);
9. Could log(output) extra details, such as "level", "timestamp", "code file name" , "function name", "line number";

# Usage
you should init MyLog before you log-out any string.
e.g. Init the MyLog at the main function.
Note:
Don't start a thread which using "MyLog" to log-out at main function directly

1.Include the lib or src at your xxx.pro
```Makefile
#using MyLog as the src (using your own path)
#include($$PWD/my_lib/MyLog/MyLogSrc.pri)

#using MyLog as a lib (using your own path)
include($$PWD/my_lib/MyLog/MyLogLib.pri)
```
2. Include header
```cpp
#include "my_log.h"
```
3. Init for file log
```cpp
QCoreApplication::setApplicationName("myappname");
QCoreApplication::setApplicationVersion("0.0.1");
QCoreApplication::setOrganizationName("com.company.myappname"); //set app name for log-file-path
QCoreApplication::setOrganizationDomain("com.company.myappname");

MyLogNS::FileLogger *fileLog = new MyLogNS::FileLogger();
int result = fileLog->open_log_file_at_dir("log");
if(result != 0) {
    qDebug("error: %s", fileLog->get_error_str(result));
}
qDebug("log file path=%s", fileLog->get_log_file_abs_path());
MyLogIns.installer_logger(fileLog);
```
4. Init for console log
```cpp
MyLogIns.installer_logger(new MyLogNS::ConsoleLogger());
```
5. Features control variables
using the variables when you need change the features only.
```cpp
MyLogIns.is_enable_auto_new_line= true;     //default is true
MyLogIns.is_show_level_str= true;           //default is true
MyLogIns.is_show_timestamp= true;           //default is true
MyLogIns.is_show_file_name= true;           //default is false
MyLogIns.is_show_function_name= true;       //default is true
MyLogIns.is_show_line_number= true;         //default is true
```
6. Write log (use it as the way using the "qDebug()")
```cpp
I << "str value=" << 1;     //log info
D << "str value=" << 2;     //log debug
E << "str value=" << 3;     //log error
D << "Date:" << QDate::currentDate();
D << "Types:" << QString("String") << QChar('x') << QRect(0, 10, 50, 40);
```
7. Switch about each level of log
you can find the macro at “MyLogSrc.pri” or “MyLogLib.pri”
```Makefile
#DEFINES += MYLOG_NO_I_OUTPUT
#DEFINES += MYLOG_NO_D_OUTPUT
#DEFINES += MYLOG_NO_E_OUTPUT
```
8. Log  example on console

![out-put-example][image-1]

# Making your own Logger
1. Method of making a self-implemented logger
inherit this interface and make your own logger.
you can find this inferface at file "logger\_interface.h"
```cpp
class LoggerInterface
{
public:
    LoggerInterface();
    virtual ~LoggerInterface();
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void write(LogLevel level, const QString &msg, bool is_shift_to_next_line) = 0;
};
```
2. Create your own logger
```cpp
#include "logger_interface.h"
class NetLogger : public MyLogNS::LoggerInterface
{
public:
    NetLogger();
    virtual void open();
    virtual void close();
    virtual void write(MyLogNS::LogLevel level, const QString &msg, bool is_shift_to_next_line);
};
```
3. Using your own logger
```cpp
MyLogIns.installer_logger(new  NetLogger());
```

[1]:	README.md
[2]:	README.zh-cn.md

[image-1]:	https://github.com/robert1207/MyLog/blob/master/doc/out_put_example.png