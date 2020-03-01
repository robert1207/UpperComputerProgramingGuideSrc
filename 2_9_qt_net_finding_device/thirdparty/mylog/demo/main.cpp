#include "mainwindow.h"
#include <QApplication>

#include "my_log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //file logger
    MyLogNS::FileLogger *fileLog = new MyLogNS::FileLogger();
    int result = fileLog->open_log_file_at_dir("log");
    if(result != 0) {
        qDebug("error: %s", fileLog->get_error_str(result));
    }
    qDebug("log file path=%s", fileLog->get_log_file_abs_path());
    MyLogIns.installer_logger(fileLog);

    //console logger
    MyLogIns.installer_logger(new MyLogNS::ConsoleLogger());

    //log settings
    MyLogIns.is_show_function_name = false;

    I << "app startup test" << QPoint(3,5);
    D << "app startup test" << QRect(1,2,3,4);
    E << "app startup test" << 5;

    MainWindow w;
    w.show();

    return a.exec();
}
