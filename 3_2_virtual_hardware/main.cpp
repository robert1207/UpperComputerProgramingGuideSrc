#include "virtualhardwaredialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VirtualHardwareDialog w;
    w.show();
    return a.exec();
}
