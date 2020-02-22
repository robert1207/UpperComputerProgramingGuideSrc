/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */


#ifndef DIALOG_H
#define DIALOG_H

#include "../net/netmanager.h"
#include "../views/toast/toast.h"
#include "../utils/stringutil.h"

#include <QString>
#include <QDialog>
#include <QScrollBar>

using namespace HYKT;

namespace Ui {
class Dialog;
}

class KcpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KcpDialog(QWidget *parent = nullptr);
    ~KcpDialog();

private slots:

    void on_pushButtonOpen_clicked();
    void on_pushButtonSend_clicked();

    void on_pushButtonRecvClear_clicked();

    void on_pushButtonSendClear_clicked();

    void on_comboBoxNetType_currentIndexChanged(int index);


private:

    void InitUI();
    void SetOpenBtnStatus(bool is_open);
    void SetNetTypeStatus(bool is_enable);
    void AddRecvMsg(QString line);
    void ClearRecvMsg();
    void ClearSendMsg();

    void ShowEditDesIp(bool is_show);
    void SetEditPortTextInListen(bool is_listen);

private slots:
    void OnRecv(QByteArray *data, const QString ip, const quint16 port);

    void OnError(int error_code, QString extra_error_info);



private:
    Ui::Dialog *ui;

    NetManager *netmanager_p;
    QString des_ip_;
    quint16 des_port_;
    QString recv_str_cache_;


};

#endif // DIALOG_H
