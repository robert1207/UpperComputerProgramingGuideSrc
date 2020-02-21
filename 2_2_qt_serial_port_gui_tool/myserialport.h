#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    MySerialPort();
    ~MySerialPort();

   public:
       static QList<QSerialPortInfo> GetAvailablePorts();
       bool Open();
       void Close();
       bool IsOpen();
       qint64 SendData(const QByteArray &data);

       void SetPort(const QSerialPortInfo &serialPortInfo);

       bool SetBaudRate(qint32 baudRate);
       static QList<QString> GetBaudRateStrList();
       static qint32 GetBaudRateValueByIndex(int index);

       bool SetDataBits(QSerialPort::DataBits dataBits);
       static QList<QString> GetDatabitsStrList();
       static QSerialPort::DataBits GetDatabitsValueByIndex(int index);

       bool SetParity(QSerialPort::Parity parity);
       static QList<QString> GetParityStrList();
       static QSerialPort::Parity GetParityValueByIndex(int index);

       bool SetStopBits(QSerialPort::StopBits stopBits);
       static QList<QString> GetStopbitsStrList();
       static QSerialPort::StopBits GetStopbitsValueByIndex(int index);

   signals:
       void ReceivedData(const QByteArray &data);

private slots:
       void ReadyRead();
private:

       QSerialPort *serial_port_p;

       const static QList<QString> baudrate_str_list_;
       const static QList<QString> databits_str_list_;
       const static QList<QString> parity_str_list_;
       const static QList<QString> stopbits_str_list_;

};

#endif // MYSERIALPORT_H
