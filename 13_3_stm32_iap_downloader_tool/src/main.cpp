#include "ui/iapdownloadertooldialog.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);

    //translate for this application
    QTranslator* translator_zh_p;
    translator_zh_p = new QTranslator();
    translator_zh_p->load(":/tr/tr/app_zh_CN.qm");
    qApp->installTranslator(translator_zh_p);

    IapDownloaderToolDialog w;
    w.show();


    //theme
    QFile qssFile;
    qssFile.setFileName(":/qss/qss/theme.qss");

    QString qss = "";
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
       // qss = QLatin1String(qssFile.readAll());
       qss = QByteArray(qssFile.readAll());
      //  qDebug() << "qss = " << qss;
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    return a.exec();
}
