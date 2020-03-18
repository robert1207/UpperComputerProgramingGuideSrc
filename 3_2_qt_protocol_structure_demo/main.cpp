#include "ui/demodialog/demodialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DemoDialog w;
    w.show();
    return a.exec();
}
