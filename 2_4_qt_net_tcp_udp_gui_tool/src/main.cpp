/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */

#include "ui/netdialog.h"
#include <QApplication>

#include "my_log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyLogIns.installer_logger(new MyLogNS::ConsoleLogger());
    MyLogIns.is_show_function_name = false;

    KcpDialog w;
    w.show();

    return a.exec();
}
