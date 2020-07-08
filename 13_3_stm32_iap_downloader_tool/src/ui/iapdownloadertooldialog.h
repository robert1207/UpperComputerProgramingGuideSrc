#ifndef IAPDOWNLOADERTOOLDIALOG_H
#define IAPDOWNLOADERTOOLDIALOG_H

#include <QDialog>
#include "../core/core.h"
#include "../uart/myserialport.h"
#include "../finding_serial_device/findingserialdevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IapDownloaderToolDialog; }
QT_END_NAMESPACE

class IapDownloaderToolDialog : public QDialog
{
    Q_OBJECT

public:
    IapDownloaderToolDialog(QWidget *parent = nullptr);
    ~IapDownloaderToolDialog();

private slots:
    void on_pushButtonChoseFile_clicked();

    void on_pushButtonDownload_clicked();

private:
    void OnFoundDevice(QString found_device_port_name);
    void OnDownloadProgress(bool is_finish, bool is_successed, int percent, QString note);

private:
    void SetUiDisable(bool disable);

private:
    Ui::IapDownloaderToolDialog *ui;

    Core core_;
    FindingSerialDevice finding_serial_device_;


};
#endif // IAPDOWNLOADERTOOLDIALOG_H
