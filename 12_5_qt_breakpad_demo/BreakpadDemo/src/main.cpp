#include "ui/demodialog.h"

#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QDir>
#include <QThread>

#include <QDebug>

#include "BreakpadHandler.h"
#include "BreakpadHttpUploader.h"

#include "ui/crashreportdialog/crashreportdialog.h"

void ShowDir(QString filePath) {
    QProcess process;
#if defined(Q_OS_WIN32)
    filePath.replace("/", "\\");
    QString win32_cmd = QString("explorer.exe  \"%1\"").arg(filePath);
    process.startDetached(win32_cmd);
#elif defined(Q_OS_MAC)
    QString macx_cmd = QString("open \"%1\"").arg(filePath);
    process.startDetached(macx_cmd);
#else
    QDesktopServices::openUrl(QUrl(filePath));
#endif
}

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    //those settings are need by QStandardPaths and breakpad
    QCoreApplication::setApplicationName("BreakpadDemo");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setOrganizationDomain("name.org");

    BreakpadHandler *breakpad_instance = BreakpadHandler::GetInstance();
    QStringList path_list2 = QStandardPaths::standardLocations(QStandardPaths::DataLocation);
    QString std_base_path =  path_list2[0];
    QString my_crash_path = std_base_path + "/crashs";
    breakpad_instance->SetupBreakPad(my_crash_path);//or just using "crashes"

    //run app
    DemoDialog w;
    w.show();


    if(breakpad_instance->IsHadCrashedDumpFiles()) { //last time running was crashed
        //1. copy out the dmp files
        QString desktop_path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString dump_file_dst_path = desktop_path + "/" + "ReportBug";
        QDir().mkpath(dump_file_dst_path);
        if (QDir().exists(dump_file_dst_path)) {

            QStringList dump_list = breakpad_instance->GetDumpFileList();
            QString base_path = breakpad_instance->GetBreakPadDumpPath();
            foreach(QString itDmpFileName, dump_list) {
                //can log this "itDmpFileName" name into log
                QString src_file_full_path = base_path + "/" + itDmpFileName ;
                QString des_file_full_path = dump_file_dst_path  + "/" + itDmpFileName ;
                if(QFile::exists(src_file_full_path)) {
                    QFile::copy(src_file_full_path, des_file_full_path);
                }
            }
        }

        //2. show user the error report dialog (model dialog)
        CrashReportDialog * crash_report_dialog = new CrashReportDialog();
        crash_report_dialog->setModal(true);
        crash_report_dialog->exec();

        //3. show copyed dir
        ShowDir(dump_file_dst_path);

        //4. delete all of the dmp files
        breakpad_instance->DeleteAllOfTheDumpFiles();

        //5. you may choose to upload this dump file to your server by http
        //QBreakpadHttpUploader uploder;
        //uploder.setUrl(QUrl("http://xxx.abc.net/upload_log"));
        //QString fake_dump_file_path = "";
        //uploder.uploadDump(fake_dump_file_path);
    }

    return app.exec();
}
