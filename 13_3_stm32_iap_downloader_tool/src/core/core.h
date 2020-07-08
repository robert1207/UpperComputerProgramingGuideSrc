#ifndef CORE_H
#define CORE_H

#include <QObject>

#include <QThread>
#include <QSerialPortInfo>
#include "../uart/myserialport.h"
#include "../protocol/protocolmanager.h"
#include "hexfilereader.h"

class Core : public QThread
{
    Q_OBJECT
public:
    Core();
    ~Core() override;

    void SetHexFileAbsPath(QString file_path);
    QString GetHexFileAbsPath();

    void SetBaudRate(qint32 baudRate) {
        baudRate_ = baudRate;
    }
    void SetPortName(QString port_name);
    void StartWorkingThread();

signals:
    void onDownloadProgress(bool is_finish, bool is_successed, int percent, QString note);

private slots:
    void OnProtocolError(int error_type, QString error_string);
    void OnDispatchPackage(quint8 *pkg, int len);
    void OnCommInitCallback();

private:
    void run() override;


private:
    QString hex_file_abs_path_;
   // QSerialPortInfo serial_device_info_;

    ProtocolManager* protocol_manager_p;
    HexFileReader hex_reader_;

    qint32 baudRate_;

    QString port_name_;


};

#endif // CORE_H
