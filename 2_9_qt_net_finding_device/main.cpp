
#include <QApplication>

#include "my_log.h"
#include "ui/device_connect_dialog/deviceconnectdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MyLogIns.installer_logger(new MyLogNS::ConsoleLogger());
    MyLogIns.is_show_function_name = false;
    MyLogIns.is_show_timestamp = false;
    I << "log test";

    DeviceConnectDialog d;
    d.show();

    return a.exec();
}
