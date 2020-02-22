/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */

#include "netdialog.h"
#include "ui_dialog.h"

KcpDialog::KcpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);


    InitUI();

    netmanager_p = NetManager::GetInstance();
    connect(netmanager_p, &NetManager::onRecv, this, &KcpDialog::OnRecv);
    connect(netmanager_p, &NetManager::onError, this, &KcpDialog::OnError);

}

KcpDialog::~KcpDialog()
{
    delete ui;
}

void KcpDialog::InitUI() {

    //net type
    QList<QString> net_type_list = NetManager::GetNetTypeStrList();
    for(int a = 0; a < net_type_list.size(); ++a) {
         ui->comboBoxNetType->addItem(net_type_list[a]);
    }
    ui->comboBoxNetType->setCurrentIndex(0);

    //addr
    ui->lineEditDesIp->setText("127.0.0.1");

    //port
    ui->lineEditDesPort->setText("2009");

    recv_str_cache_ = "";
}

void KcpDialog::SetNetTypeStatus(bool is_enable) {
     ui->comboBoxNetType->setEnabled(is_enable);
     ui->lineEditDesIp->setEnabled(is_enable);
     ui->lineEditDesPort->setEnabled(is_enable);
}

void KcpDialog::SetOpenBtnStatus(bool is_open) {
    if(is_open) {
         ui->pushButtonOpen->setText(QApplication::translate("Dialog", "Open"));
    } else {
         ui->pushButtonOpen->setText(QApplication::translate("Dialog", "Close"));
    }
}

void KcpDialog::on_pushButtonOpen_clicked()
{
    if(netmanager_p->IsOpen()) { //do close
        netmanager_p->Close();
        SetOpenBtnStatus(true);
        SetNetTypeStatus(true);
    } else { //do open

        QString des_ip = ui->lineEditDesIp->text();
        QString des_port = ui->lineEditDesPort->text();

        if(des_ip.isEmpty()) {
            Toast::showTip(QApplication::translate("Dialog", "Please set destination IP !"));
            return;
        }

        if(des_port.isEmpty()) {
            Toast::showTip(QApplication::translate("Dialog", "Please set destination port !"));
            return;
        }

        //net type
        int net_type_index = ui->comboBoxNetType->currentIndex();

        //ip, port
        des_ip_ = des_ip;
        des_port_ = static_cast<quint16>(des_port.toInt());

        netmanager_p->Open(net_type_index, des_ip_, des_port_);

        SetOpenBtnStatus(false);
        SetNetTypeStatus(false);
    }
}

void KcpDialog::on_pushButtonSend_clicked()
{
    if(!netmanager_p->IsOpen()) {
        Toast::showTip(QApplication::translate("Dialog", "Please click 'open' button first !"));
        return;
    }

    QString send_str = ui->textEditSend->toPlainText();

    if(send_str.isEmpty()) {
        Toast::showTip(QApplication::translate("Dialog", "Please input sending string !"));
        return;
    }

    QByteArray send_ba;
    send_ba = send_str.toUtf8();

    if(ui->checkBoxSendHex->isChecked()) {
        send_ba = send_ba.toHex();
    }

    netmanager_p->Send(send_ba.data(), send_ba.size());
}

void KcpDialog::OnRecv(QByteArray *data, const QString ip, const quint16 port) {

        QString str;
        if(ui->checkBoxRecvHex->isChecked()) {
             QByteArray ba;
             QString temp(*data);
             StringUtil::StringToHex(temp, ba);
             str += ba;
        } else {
             str += *data;
        }
        str += "\n";

        AddRecvMsg(str);
}

void KcpDialog::AddRecvMsg(QString line) {
    recv_str_cache_ += line;
    ui->textEditRecv->setText(recv_str_cache_);

    QScrollBar *scrollbar = ui->textEditRecv->verticalScrollBar();
    if (scrollbar) {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

void KcpDialog::ClearRecvMsg() {
    recv_str_cache_ = "";
    ui->textEditRecv->setText(recv_str_cache_);
}

void KcpDialog::ClearSendMsg() {
    ui->textEditSend->setText("");
}

void KcpDialog::on_pushButtonRecvClear_clicked()
{
    ClearRecvMsg();
}

void KcpDialog::on_pushButtonSendClear_clicked()
{
    ClearSendMsg();
}

void KcpDialog::OnError(int error_code, QString extra_error_info) {
     QString error_str;
     error_str += "e:"+ QString::number(error_code);
     error_str += "ex:"+ extra_error_info;

     Toast::showTip(error_str);
}

void KcpDialog::on_comboBoxNetType_currentIndexChanged(int index)
{
    switch (index) {
        case Comm::NetType::UDP_broadcast:
            ShowEditDesIp(false);
            SetEditPortTextInListen(false);
            break;
        case Comm::NetType::UDP_client:
            ShowEditDesIp(true);
            SetEditPortTextInListen(false);
            break;
        case Comm::NetType::UDP_server:
            ShowEditDesIp(false);
            SetEditPortTextInListen(true);
            break;
        case Comm::NetType::TCP_client:
            ShowEditDesIp(true);
            SetEditPortTextInListen(false);
            break;
        case Comm::NetType::TCP_server:
            ShowEditDesIp(false);
            SetEditPortTextInListen(true);
            break;
    }
}

void KcpDialog::ShowEditDesIp(bool is_show) {
    if(is_show) {
        ui->lineEditDesIp->show();
        ui->destinationLabel->show();
    } else {
        ui->lineEditDesIp->hide();
        ui->destinationLabel->hide();
    }
}

void KcpDialog::SetEditPortTextInListen(bool is_listen) {
    if(is_listen) {
        ui->portLabel->setText("Listen Port:");
    } else {
        ui->portLabel->setText("Destination Port:");
    }
}

