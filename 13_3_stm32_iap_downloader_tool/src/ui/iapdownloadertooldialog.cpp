#include "iapdownloadertooldialog.h"
#include "ui_iapdownloadertooldialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>

#include "../protocol/command.h"
#include "../utils/stringutil.h"
#include "../file/directoryutil.h"


IapDownloaderToolDialog::IapDownloaderToolDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IapDownloaderToolDialog)
{
    ui->setupUi(this);

    connect(&finding_serial_device_, &FindingSerialDevice::OnFoundDevice,
            this, &IapDownloaderToolDialog::OnFoundDevice, Qt::ConnectionType::QueuedConnection);
    connect(&core_, &Core::onDownloadProgress,
            this, &IapDownloaderToolDialog::OnDownloadProgress);

    //remove question mark
    Qt::WindowFlags flags= this->windowFlags();
    setWindowFlags(flags&~Qt::WindowContextHelpButtonHint);

    //update theme
   // ui->pushButtonChoseFile->setProperty("cancel_btn", true);
  //  ui->pushButtonDownload->setProperty("ok_btn", true);
    ui->progressBar->setValue(0);
}

IapDownloaderToolDialog::~IapDownloaderToolDialog()
{
    delete ui;
}


void IapDownloaderToolDialog::on_pushButtonChoseFile_clicked()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
          QApplication::translate("IapDownloaderToolDialog", "Open Bin File"), //title
          "./", //path
          "Video files (*.bin);;All files (*.*)"); //filter

    if(filename.isEmpty()) {

        OnDownloadProgress(false, false, 0, QApplication::translate("IapDownloaderToolDialog",
                                                                    "No bin file had been selected !"));

        //QMessageBox::warning(this, QApplication::translate("IapDownloaderToolDialog", "Error"),
                            // QApplication::translate("IapDownloaderToolDialog", "No hex or bin file has selected !"));
        return;
    }

    ui->textEditFileName->setText(filename);
    core_.SetHexFileAbsPath(filename);
}

void IapDownloaderToolDialog::on_pushButtonDownload_clicked()
{
    if(!DirectoryUtil::IsFileExist(core_.GetHexFileAbsPath())) {
        OnDownloadProgress(false, false, 0, QApplication::translate("IapDownloaderToolDialog",
                                                                    "Please choose a bin file first!!"));
        //QMessageBox::critical(this, QApplication::translate("IapDownloaderToolDialog", "Error"),
                            // QApplication::translate("IapDownloaderToolDialog", "Please choose a bin file first!!"));
        return;
    }

    if(finding_serial_device_.isBusyingOnFinding()) {
        OnDownloadProgress(false, false, 0, QApplication::translate("IapDownloaderToolDialog",
                                                                    "busying on finding device"));
        //QMessageBox::critical(this, QApplication::translate("IapDownloaderToolDialog", "Error"),
                             //QApplication::translate("IapDownloaderToolDialog", "busying on finding device"));
        return;
    }

    SetUiDisable(true);

    finding_serial_device_.SetBaudRate(QSerialPort::BaudRate::Baud9600);
    finding_serial_device_.StartFind();

    OnDownloadProgress(false, false, 0, QApplication::translate("IapDownloaderToolDialog", "start finding device"));
}

void IapDownloaderToolDialog::OnFoundDevice(QString found_device_port_name) {
    qDebug() << "OnFoundDevice" <<  found_device_port_name;

    finding_serial_device_.StopFind();

    //启动新的线程来处理数据
    core_.SetBaudRate(QSerialPort::BaudRate::Baud9600);
    //core_.SetQSerialPortInfo(serialPortInfo);
    core_.SetPortName(found_device_port_name);
    core_.StartWorkingThread();
}

void IapDownloaderToolDialog::OnDownloadProgress(bool is_finish, bool is_successed, int percent, QString note) {
    Q_UNUSED(is_successed)
    if(is_finish) {
        SetUiDisable(false);
    }

    ui->labelStatus->setText(note);
    ui->progressBar->setValue(percent);
    // qDebug() << "is_finish=" << is_finish;
   // qDebug() << "percent=" << percent;
  //  qDebug() << "note=" << note;
}

void IapDownloaderToolDialog::SetUiDisable(bool disable) {
    ui->pushButtonChoseFile->setDisabled(disable);
    ui->pushButtonDownload->setDisabled(disable);
}

