#include "serialdialog.h"
#include "ui_serialdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QTextCursor>
#include "stringutil.h"

#define DEFAULT_BAUD_INDEX  3
#define DEFAULT_DATABITS_INDEX  3
#define DEFAULT_PARITY_INDEX  0
#define DEFAULT_STOPBITS_INDEX  0

SerialDialog::SerialDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SerialDialog)
{
    ui->setupUi(this);

    port_info_list_ = MySerialPort::GetAvailablePorts();
    my_serial_port_p = new MySerialPort();
    connect(my_serial_port_p, &MySerialPort::ReceivedData, this, &SerialDialog::ReceivedData);

    InitUi();
    EnableEditingUi();
}

SerialDialog::~SerialDialog()
{
    delete ui;
    disconnect(my_serial_port_p, &MySerialPort::ReceivedData, this, &SerialDialog::ReceivedData);
    delete my_serial_port_p;
}

void SerialDialog::InitUi() {

    for (int a = 0; a < port_info_list_.count(); a ++) {
        QString port_name = port_info_list_.at(a).portName();
        ui->comboBoxSerialPort->addItem(port_name);
    }
    ui->comboBoxSerialBaud->addItems(MySerialPort::GetBaudRateStrList());
    ui->comboBoxSerialDataBits->addItems(MySerialPort::GetDatabitsStrList());
    ui->comboBoxSerialStopBits->addItems(MySerialPort::GetParityStrList());
    ui->comboBoxSerialParity->addItems(MySerialPort::GetStopbitsStrList());

    ui->comboBoxSerialPort->setCurrentIndex(0);
    ui->comboBoxSerialBaud->setCurrentIndex(DEFAULT_BAUD_INDEX);
    ui->comboBoxSerialDataBits->setCurrentIndex(DEFAULT_DATABITS_INDEX);
    ui->comboBoxSerialStopBits->setCurrentIndex(DEFAULT_STOPBITS_INDEX);
    ui->comboBoxSerialParity->setCurrentIndex(DEFAULT_PARITY_INDEX);
}

void SerialDialog::DisableEditingUi() {
    ui->comboBoxSerialPort->setDisabled(true);
    ui->comboBoxSerialBaud->setDisabled(true);
    ui->comboBoxSerialDataBits->setDisabled(true);
    ui->comboBoxSerialStopBits->setDisabled(true);
    ui->comboBoxSerialParity->setDisabled(true);
    ui->pushButtonSerialSend->setDisabled(false);
}

void SerialDialog::EnableEditingUi() {
    ui->comboBoxSerialPort->setDisabled(false);
    ui->comboBoxSerialBaud->setDisabled(false);
    ui->comboBoxSerialDataBits->setDisabled(false);
    ui->comboBoxSerialStopBits->setDisabled(false);
    ui->comboBoxSerialParity->setDisabled(false);
    ui->pushButtonSerialSend->setDisabled(true);
}

void SerialDialog::SetSerialSettings() {

    my_serial_port_p->SetBaudRate(MySerialPort::GetBaudRateValueByIndex(ui->comboBoxSerialBaud->currentIndex()));
    my_serial_port_p->SetDataBits(MySerialPort::GetDatabitsValueByIndex(ui->comboBoxSerialDataBits->currentIndex()));
    my_serial_port_p->SetParity(MySerialPort::GetParityValueByIndex(ui->comboBoxSerialParity->currentIndex()));
    my_serial_port_p->SetStopBits(MySerialPort::GetStopbitsValueByIndex(ui->comboBoxSerialStopBits->currentIndex()));
}

void SerialDialog::on_pushButtonSerialOpen_clicked()
{
    if(my_serial_port_p->IsOpen()) {
        qDebug() << "do close";
        my_serial_port_p->Close();
        EnableEditingUi();
        ui->pushButtonSerialOpen->setText(QApplication::translate("SerialDialog", "打开串口"));
    } else {
        qDebug() << "do open";
        if(port_info_list_.count() > 0) {

            my_serial_port_p->SetPort(port_info_list_[ui->comboBoxSerialPort->currentIndex()]);
            SetSerialSettings();
            my_serial_port_p->Open();
            DisableEditingUi();

            ui->pushButtonSerialOpen->setText(QApplication::translate("SerialDialog", "关闭串口"));
        } else {
            QMessageBox::information(nullptr, "Error", "Please make sure you have a serial device plugged in!", QMessageBox::Yes, QMessageBox::Yes);
        }
    }
}

void SerialDialog::on_pushButtonSerialSend_clicked()
{
    if(!my_serial_port_p->IsOpen()) {
        QMessageBox::information(nullptr, "Warning", "Please open the serial port!", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QString text = ui->textEditSend->toPlainText().toLatin1();
    if(text.isEmpty()) {
        QMessageBox::information(nullptr, "Error", "Please input the sending content!", QMessageBox::Yes, QMessageBox::Yes);
    } else {

        QByteArray send_ba;


        if(ui->checkBox_Tx->isChecked()) {
            StringUtil::StringToHex(text, send_ba);
            //send_ba = send_ba.toHex();
        } else {
            send_ba = text.toUtf8();
        }

        //qDebug() << "send data = " << send_ba << "   len = " << send_ba.length();


        /*
        qDebug() << "send data = len = " << send_ba.length();
        for (int a = 0; a < send_ba.length(); a ++ ) {
                char* array = send_ba.data();
                printf("index=%d  %02x\n", a, array[a] & 0xff);
        }*/

        my_serial_port_p->SendData(send_ba);
      //  ui->textEditSend->clear();
    }
}

void SerialDialog::ReceivedData(const QByteArray &data) {
    QString str;
    if(ui->checkBox_Rx->isChecked()) {
        str +=  QString(data.toHex(' '));
    } else {
        str += data;
    }

    qDebug() << "ReceivedData:" << str;

    ui->textEditReceive->append(str);
    ui->textEditReceive->moveCursor(QTextCursor::End);
}
