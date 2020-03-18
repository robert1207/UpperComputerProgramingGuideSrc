#include "demodialog.h"
#include "ui_demodialog.h"

#include <QDebug>
#include <QMessageBox>

#include "../device_connect_dialog/deviceconnectdialog.h"

DemoDialog::DemoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DemoDialog)
{
    ui->setupUi(this);

    protocol_manager_p = ProtocolManager::GetInstance();
    connect(protocol_manager_p, &ProtocolManager::onConnectionError,
            this , &DemoDialog::onConnectionError);
    connect(protocol_manager_p, &ProtocolManager::onDisconnect,
            this , &DemoDialog::onDisconnect);
    connect(protocol_manager_p, &ProtocolManager::onGetMachinetemperature,
            this , &DemoDialog::onGetMachinetemperature);
    connect(protocol_manager_p, &ProtocolManager::onReportValue,
            this , &DemoDialog::onReportValue);

    QRegExp regx("[0-9]+$");
    QValidator *validator_searching = new QRegExpValidator(regx, ui->lineEditSetValue );
    ui->lineEditSetValue->setValidator(validator_searching);

    ui->labelConnectStatus->setText("无连接设备");

}

DemoDialog::~DemoDialog()
{
    delete ui;
}

void DemoDialog::onConnectionError(QString msg) {
    qDebug() << "onConnectionError: " << msg;
}

void DemoDialog::onDisconnect() {
    qDebug() << "onDisconnect";
}

void DemoDialog::on_pushButtonConnectDevice_clicked()
{
    DeviceConnectDialog device_connect_dialog(this);
    if(device_connect_dialog.exec() == QDialog::Accepted) {
    }

    if(protocol_manager_p->IsConnected()) {
        ui->labelConnectStatus->setText("设备已连接");
    }
}

void DemoDialog::on_pushButtonSetValue_clicked()
{
    if(!protocol_manager_p->IsConnected()) {
        QMessageBox::information(nullptr, "Title", "Please connect device first!", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    int value = ui->lineEditSetValue->text().toInt();
    protocol_manager_p->AddWork(*Command::SendSetPositionValue(value));
}

void DemoDialog::on_pushButtonGettemperature_clicked()
{
    if(!protocol_manager_p->IsConnected()) {
        QMessageBox::information(nullptr, "Title", "Please connect device first!", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    protocol_manager_p->AddWork(*Command::SendGetMachinetemperature());
}

void DemoDialog::onGetMachinetemperature(int value) {
    QString tempeture_value_str = QString::number(value);
    ui->labelTemperatureValue->setText(tempeture_value_str);
}

void DemoDialog::onReportValue(int value) {
    ui->labelReportValue->setText(QString::number(value));
}
