#include "myserialport.h"

#include <QDebug>
/*

Baud1200 = 1200,
Baud2400 = 2400,
Baud4800 = 4800,
Baud9600 = 9600,
Baud19200 = 19200,
Baud38400 = 38400,
Baud57600 = 57600,
Baud115200 = 115200,

Data5 = 5,
Data6 = 6,
Data7 = 7,
Data8 = 8,

NoParity = 0,
EvenParity = 2,
OddParity = 3,
SpaceParity = 4,
MarkParity = 5,

OneStop = 1,
OneAndHalfStop = 3,
TwoStop = 2,

*/

const QList<QString> MySerialPort::baudrate_str_list_ = {"1200","2400","4800","9600","19200","38400","57600","115200"};
const QList<QString> MySerialPort::databits_str_list_ = {"5", "6", "7", "8"};
const QList<QString> MySerialPort::parity_str_list_ = {"None", "Even", "Odd", "Space", "Mark"};
const QList<QString> MySerialPort::stopbits_str_list_ = {"1", "1.5", "2"};


MySerialPort::MySerialPort()
{
    serial_port_p = new QSerialPort();

    connect(serial_port_p, &QSerialPort::readyRead, this, &MySerialPort::ReadyRead);
}

MySerialPort::~MySerialPort()
{
    if(serial_port_p != nullptr && serial_port_p->isOpen()) {
        serial_port_p->close();
    }
    disconnect(serial_port_p, &QSerialPort::readyRead, this,  &MySerialPort::ReadyRead);
    delete serial_port_p;
}

QList<QSerialPortInfo> MySerialPort::GetAvailablePorts() {
    return QSerialPortInfo::availablePorts();
}

bool MySerialPort::Open() {
    return serial_port_p->open(QIODevice::ReadWrite);
}

void MySerialPort::Close() {
    serial_port_p->close();
}

bool MySerialPort::IsOpen() {
    return serial_port_p->isOpen();
}


qint64 MySerialPort::SendData(const QByteArray &data) {
    qint64 res = serial_port_p->write(data);
    serial_port_p->flush();
    qDebug() << "send data: res = " << res;
    return res;
}

void MySerialPort::SetPort(const QSerialPortInfo &info) {
    serial_port_p->setPort(info);
  //  serial_port_p->setPortName("com1");//"/dev/ttys002"
    serial_port_p->setFlowControl(QSerialPort::NoFlowControl);
}

bool MySerialPort::SetBaudRate(qint32 baudRate) {
    return serial_port_p->setBaudRate(baudRate);
}

bool MySerialPort::SetDataBits(QSerialPort::DataBits dataBits) {
    return serial_port_p->setDataBits(dataBits);
}

bool MySerialPort::SetParity(QSerialPort::Parity parity) {
    return serial_port_p->setParity(parity);
}

bool MySerialPort::SetStopBits(QSerialPort::StopBits stopBits) {
    return serial_port_p->setStopBits(stopBits);
}

void MySerialPort::ReadyRead() {
    //qDebug() << "ReadyRead";
    while (!serial_port_p->atEnd()) {
        QByteArray data = serial_port_p->read(100);
        emit ReceivedData(data);
    }
}

QList<QString>  MySerialPort::GetBaudRateStrList() {
    return baudrate_str_list_;
}

qint32  MySerialPort::GetBaudRateValueByIndex(int index) {

    switch(index) {
        case 0 : return QSerialPort::BaudRate::Baud1200;
        case 1 : return QSerialPort::BaudRate::Baud2400;
        case 2 : return QSerialPort::BaudRate::Baud4800;
        case 3 : return QSerialPort::BaudRate::Baud9600;
        case 4 : return QSerialPort::BaudRate::Baud19200;
        case 5 : return QSerialPort::BaudRate::Baud38400;
        case 6 : return QSerialPort::BaudRate::Baud57600;
        case 7 : return QSerialPort::BaudRate::Baud115200;
    default:
        return QSerialPort::BaudRate::Baud9600;
    }
}

QList<QString>  MySerialPort::GetDatabitsStrList() {
    return databits_str_list_;
}

QSerialPort::DataBits  MySerialPort::GetDatabitsValueByIndex(int index) {
    switch(index) {
        case 0 : return QSerialPort::DataBits::Data5;
        case 1 : return QSerialPort::DataBits::Data6;
        case 2 : return QSerialPort::DataBits::Data7;
        case 3 : return QSerialPort::DataBits::Data8;
    default:
        return QSerialPort::DataBits::Data8;
    }
}

QList<QString>  MySerialPort::GetParityStrList() {
    return parity_str_list_;
}

QSerialPort::Parity  MySerialPort::GetParityValueByIndex(int index) {
    switch(index) {
        case 0 : return QSerialPort::Parity::NoParity;
        case 1 : return QSerialPort::Parity::EvenParity;
        case 2 : return QSerialPort::Parity::OddParity;
        case 3 : return QSerialPort::Parity::SpaceParity;
        case 4 : return QSerialPort::Parity::MarkParity;
    default:
        return QSerialPort::Parity::NoParity;
    }
}

QList<QString>  MySerialPort::GetStopbitsStrList() {
    return stopbits_str_list_;
}

QSerialPort::StopBits  MySerialPort::GetStopbitsValueByIndex(int index) {
    switch(index) {
        case 0 : return QSerialPort::StopBits::OneStop;
        case 1 : return QSerialPort::StopBits::OneAndHalfStop;
        case 2 : return QSerialPort::StopBits::TwoStop;

    default:
        return QSerialPort::StopBits::OneStop;
    }
}

