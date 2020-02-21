#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include "myserialport.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SerialDialog; }
QT_END_NAMESPACE



class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    SerialDialog(QWidget *parent = nullptr);
    ~SerialDialog();


private slots:
    void on_pushButtonSerialOpen_clicked();

    void on_pushButtonSerialSend_clicked();

    void ReceivedData(const QByteArray &data);

private:
    void InitUi();
    void SetSerialSettings();

    void DisableEditingUi();
    void EnableEditingUi();

private:
    Ui::SerialDialog *ui;
    QList<QSerialPortInfo> port_info_list_;

    MySerialPort *my_serial_port_p;
};
#endif // SERIALDIALOG_H
