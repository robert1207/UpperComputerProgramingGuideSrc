#ifndef FINDINGSERIALDEVICE_H
#define FINDINGSERIALDEVICE_H

#include <QThread>
#include <QSerialPortInfo>
#include "../uart/myserialport.h"


class FindingSerialDevice : public QObject
{
    Q_OBJECT
public:
    FindingSerialDevice();
    ~FindingSerialDevice() override;

    void SetBaudRate(qint32 baudRate) {
        baudRate_ = baudRate;
    }
    bool isBusyingOnFinding() { return is_busy_;}
    void StartFind();
    void StopFind();//解除对串口设备资源的占用

signals:
    void  OnFoundDevice(QString found_device_port_name);


private:
    void onRecv(QByteArray &data, void *extra_data);


private:
    QList<MySerialPort *> serial_device_list_;
    qint32 baudRate_;
    bool is_busy_;
};

#endif // FINDINGSERIALDEVICE_H
