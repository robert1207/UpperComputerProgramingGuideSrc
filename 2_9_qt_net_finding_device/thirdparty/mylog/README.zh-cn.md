MyLog 是一个给Qt跨平台应用程序使用的log库。MyLog稳定易用。

*使用其他语言阅读本文: [English][1], [简体中文][2]*

# 特点：
1. 颜色丰富的终端log打印；
2. 支持log的等级有 "info debug error”，每个有单独开关；
3. 多线程使用安全;
4. 多线程调用不会造成内存使用量持续增长；
5. 支持打印输出到终端、文件、以及自定义的logger；
6. 支持实现自己的logger；
7. MyLog 是一个开源的项目；
8. 打印的额外信息包括“等级”、“时间戳”、“代码文件名”、“函数名字”、“代码行号”；
9. 使用起来和"qDebug()"一样方便，一样强大（因为MyLog是基于QDebug类开发的）；

# 使用方法：
在你打印任何log之前应该初始化MyLog的配置
比如在主函数内初始化MyLog
注意：
不要直接在主函数内开启多个线程并且在线程内调用MyLog打印。应该在UI线程内开启多线程。比如在主窗口的构造函数内。否则在软件退出的时候，主函数内直接开启的线程会不正常停止。导致qt应用程序不能正常释放资源。从而导致和指针相关的各类奔溃。

1.在你的Qt工程文件xxx.pro中使用lib方式或src方式添加引用
```Makefile
#using MyLog as the src (使用你自己的目录)
#include($$PWD/my_lib/MyLog/MyLogSrc.pri)

#using MyLog as a lib (使用你自己的目录)
include($$PWD/my_lib/MyLog/MyLogLib.pri)
```
2. 包括头文件
```cpp
#include "my_log.h"
```
3. 安装文件打印记录器
```cpp
QCoreApplication::setApplicationName("myappname");
QCoreApplication::setApplicationVersion("0.0.1");
QCoreApplication::setOrganizationName("com.company.myappname"); //设置程序名称，保存文件时候用到
QCoreApplication::setOrganizationDomain("com.company.myappname");

MyLogNS::FileLogger *fileLog = new MyLogNS::FileLogger();
int result = fileLog->open_log_file_at_dir("log");
if(result != 0) {
    qDebug("error: %s", fileLog->get_error_str(result));
}
qDebug("log file path=%s", fileLog->get_log_file_abs_path());
MyLogIns.installer_logger(fileLog);
```
4. 安装终端打印记录器
```cpp
MyLogIns.installer_logger(new MyLogNS::ConsoleLogger());
```
5. 配置功能控制变量
这些配置默认都是开启的不需要配置。当你需要关闭其中的属性时，配置为false即可。
```cpp
MyLogIns.is_enable_auto_new_line= true;     //default is true
MyLogIns.is_show_level_str= true;           //default is true
MyLogIns.is_show_timestamp= true;           //default is true
MyLogIns.is_show_file_name= true;           //default is false
MyLogIns.is_show_function_name= true;       //default is true
MyLogIns.is_show_line_number= true;         //default is true
```
6. 打印记录 (和使用”qDebug()”的方法一样)
```cpp
I << "str value=" << 1;     //log info
D << "str value=" << 2;     //log debug
E << "str value=" << 3;     //log error
D << "Date:" << QDate::currentDate();
D << "Types:" << QString("String") << QChar('x') << QRect(0, 10, 50, 40);
```
7. 控制记录总开关
在“MyLogSrc.pri”或“MyLogLib.pri”文件中有各个等级的log控制开关：
```Makefile
#DEFINES += MYLOG_NO_I_OUTPUT
#DEFINES += MYLOG_NO_D_OUTPUT
#DEFINES += MYLOG_NO_E_OUTPUT
```
8. 输出效果

![out-put-example][image-1]

# 实现自己的打印记录器
1. 继承接口实现自己的打印记录器
接口类在文件”logger\_interface.h”中。
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
2. 制作你自己的记录器
```cpp
#include "logger_interface.h"
class NetLogger : public MyLogNS::LoggerInterface
{
public:
    NetLogger();
    virtual void open();//安装记录器的时候被调用，用于初始化
    virtual void close();//在程序关闭的时候被调用，用于关闭文件
    virtual void write(MyLogNS::LogLevel level, const QString &msg, bool is_shift_to_next_line);
    //参数分别是:打印等级，打印字符串，是否自动换行
};
```
3. 使用你自己制作的记录器
```cpp
MyLogIns.installer_logger(new  NetLogger());
```

[1]:	README.md
[2]:	README.zh-cn.md

[image-1]:	https://github.com/robert1207/MyLog/blob/master/doc/out_put_example.png