#include "virtualhardwaredialog.h"
#include "ui_virtualhardwaredialog.h"

#include <QRegExpValidator>
#include "protocol/command.h"
#include <QDebug>

VirtualHardwareDialog::VirtualHardwareDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VirtualHardwareDialog)
{
    ui->setupUi(this);

    net_udp_searching_device_service_p = new NetManager();
    connect(net_udp_searching_device_service_p, &NetManager::onRecv, this, &VirtualHardwareDialog::SearchingDeviceRecv);
    connect(net_udp_searching_device_service_p, &NetManager::onError, this, &VirtualHardwareDialog::SearchingDeviceError);


    net_udp_communication_service_p = new NetManager();
    connect(net_udp_communication_service_p, &NetManager::onRecv, this, &VirtualHardwareDialog::CommunicationRecv);
    connect(net_udp_communication_service_p, &NetManager::onError, this, &VirtualHardwareDialog::CommunicationError);

    QRegExp regx("[0-9]+$");
    QValidator *validator_searching = new QRegExpValidator(regx, ui->lineEditSearchPort );
    ui->lineEditSearchPort->setValidator(validator_searching);

    QValidator *validator_communication = new QRegExpValidator(regx, ui->lineEditCommPort );
    ui->lineEditCommPort->setValidator(validator_communication);

}

VirtualHardwareDialog::~VirtualHardwareDialog()
{
    delete ui;
}

void VirtualHardwareDialog::SearchingDeviceRecv(QByteArray *data, const QString ip, const quint16 port) {
    //recv:EE 01 A34E EE FC FF EA
    //response:EE 01 6d 79 6e 61 6d 65 3b 30 30 30 32 32 33 31 3b 56 31 2e 32 2e 33 7e d6 EE FC FF EA

   // qDebug() << "searching device recv:" << data;

    int head = ByteUtil::Char2Int(data->at(0));
    //position 1 is pkg-len
    int command_tyep_code = ByteUtil::Char2Int(data->at(2) );
    int command_code = ByteUtil::Char2Int(data->at(3) );
    if(head == HYKT::head[0] && command_tyep_code == Command::CommandType::SetValue  && command_code == 0x01) {
        net_udp_searching_device_service_p->Send(*Command::ResponseForSearching());
    }
}
void VirtualHardwareDialog::SearchingDeviceError(int error_code, QString extra_error_info) {

}

void VirtualHardwareDialog::CommunicationRecv(QByteArray *data, const QString ip, const quint16 port) {
    int head = ByteUtil::Char2Int(data->at(0));
    int command_tyep_code = ByteUtil::Char2Int(data->at(2) );
    int command_code = ByteUtil::Char2Int(data->at(3) );

    //res for : SetValue Command Type
    if(head == HYKT::head[0] && command_tyep_code == Command::CommandType::SetValue  && command_code == 0x01) {

        int value =  (data->at(4) - 48) * 100 +
                            (data->at(5) - 48) * 10 +
                            (data->at(6) - 48) * 1;
        qDebug() << "Set value = " << value;
        net_udp_communication_service_p->Send(*Command:: ResponseForSetPositionValue());
        ui->lineEditSetValue->setText(QString::number(value));
    }

    //res for : GetValue Command Type
    else if(head == HYKT::head[0] && command_tyep_code == Command::CommandType::GetValue  && command_code == 0x01) {
        int temp_value = ui->lineEditGetValue->text().toInt();
        net_udp_communication_service_p->Send(*Command::ResponseForGetTemperature(temp_value));
    }
}

void VirtualHardwareDialog::CommunicationError(int error_code, QString extra_error_info) {

}


void VirtualHardwareDialog::on_pushButtonStartService_clicked()
{

    if(net_udp_communication_service_p->IsOpen()) { //do close

        net_udp_searching_device_service_p->Close();
        net_udp_communication_service_p->Close();
        ui->pushButtonStartService->setText("启动服务");
    } else { //do open

        int searching_port = ui->lineEditSearchPort->text().toInt();
        int communication_port = ui->lineEditCommPort->text().toInt();

        net_udp_searching_device_service_p->Open(Comm::NetType::UDP_server, "", static_cast<quint16>(searching_port));
        net_udp_communication_service_p->Open(Comm::NetType::UDP_server, "", static_cast<quint16>(communication_port));

        ui->pushButtonStartService->setText("关闭服务");
    }
}

void VirtualHardwareDialog::on_pushButtonReport_clicked()
{
     //ReportValue command type
    if(!net_udp_communication_service_p->IsOpen()) return;

    int temp_value = ui->lineEditReportValue->text().toInt();
    net_udp_communication_service_p->Send(*Command:: ResponseForReportValue(temp_value));
    ui->lineEditReportValue->setText(QString::number(temp_value + 1));
}
