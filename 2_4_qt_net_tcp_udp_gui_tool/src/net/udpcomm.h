/*
 * @Name       net
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-05
 */


#ifndef UDPCOMM_H
#define UDPCOMM_H

#include "comm.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QString>
#include <QByteArray>
#include <QAbstractSocket>

namespace HYKT {

class UdpComm :  public Comm
{
    Q_OBJECT
public:
    UdpComm();
    ~UdpComm() override;

    virtual int Open(int net_type, QString des_ip, quint16 des_port) override;
    virtual void Close() override;
    virtual int Send(const char *data, int len) override;
    virtual int Send(const QByteArray &data) override;
    virtual bool IsOpen() override;

private:
    virtual void DoRecv() override;
    virtual void DoError(QAbstractSocket::SocketError se) override;
    void DoOnDisconnected();

private:
    QUdpSocket *udp_p;
    int net_type_;

    QString des_ip_;
    quint16 des_port_;

    QString received_client_ip_;
    quint16 received_client_port_;

};

} //namespace HYKT



#endif // UDPCOMM_H
