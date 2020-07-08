#include "findingserialdevice.h"

#include <QDebug>
#include "../protocol/command.h"

/*
 * 经过各种方法验证，最终测试发现这种实现方式，可用，稳定，好用
 * 设计思想：给所以查找出的设备，new一个对象，把这些对象的串口接收回调函数都指向同一个函数。并调用这些对象的参数设置函数，
 * 打开函数，发生函数等，并发送 握手数据包。在接收回调函数处等待，看那个设备给回复了数据，并且回复的数据满足握手协议。那么这个
 * 就是要查找的设备。使用signal 把找到的设备信息返回给调用者。技术实现上注意；要在串口回调函数中，返回设备识别信息
 * 否则不知道是哪个设备给回复的消息。
 */



FindingSerialDevice::FindingSerialDevice()
{
    baudRate_ = QSerialPort::BaudRate::Baud9600;
    is_busy_ = false;
}

FindingSerialDevice::~FindingSerialDevice()
{
    StopFind();
}


void FindingSerialDevice::onRecv(QByteArray &data, void *extra_data) {

    Q_UNUSED(extra_data)

    QSerialPortInfo *info = static_cast<QSerialPortInfo*>(extra_data);

    //qDebug() << "onRecv" << data << " device = " << info->portName();

    int recv_data_len = data.length();
    if(recv_data_len < 3) return;
    char *temp_data = data.data();

    /*
    printf("%02x ", temp_data[0]);
    printf("%02x ", temp_data[1]);
    printf("%02x ", temp_data[2]);
    printf("%02x ", temp_data[3]);
*/

    if(   (temp_data[0] & 0xff) == head[0] &&
            (temp_data[2] & 0xff) == Command::CommandType::SetValue &&
            (temp_data[3] & 0xff) == 0x01
        ) {
        //qDebug() << "ok found a device ";

        QString name = info->portName();
        emit OnFoundDevice(name);
    }
}


void FindingSerialDevice::StartFind() {
    StopFind();

    is_busy_ = true;

    QList<QSerialPortInfo>  serial_device_list = MySerialPort::GetAvailablePorts();
    for (int a = 0; a < serial_device_list.count(); a ++) {
        QSerialPortInfo info = serial_device_list.at(a);

        MySerialPort* device;

        device = new MySerialPort();
        device->SetBaudRate(baudRate_);
        device->SetDataBits(QSerialPort::DataBits::Data8);
        device->SetParity(QSerialPort::Parity::NoParity);
        device->SetStopBits(QSerialPort::StopBits::OneStop);
        connect(device, &MySerialPort::onRecv, this, &FindingSerialDevice::onRecv);

        qDebug() << "info = " << info.portName();
        device->SetPort(info);
        QByteArray* data = Command::SearchDevice();
        if(device->Open() == true) {
           // qDebug() << "send data : " << *data;
             device->Send(*data);
        }

        serial_device_list_.append(device);
    }
}

void FindingSerialDevice::StopFind() {

    int count = serial_device_list_.count();
    MySerialPort* device;

    for (int a = 0; a < count; a ++) {
         device = serial_device_list_.at(a);
         //qDebug() << "close device index  = " << a;
         if(device->IsOpen()) {
           //  qDebug() << "close device index  22 2 close = " << a;
             device->Close();
         }
         delete device;
    }
    serial_device_list_.clear();
    is_busy_ = false;
}

