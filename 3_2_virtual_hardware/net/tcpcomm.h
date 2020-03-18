

#ifndef TCPCOMM_H
#define TCPCOMM_H

#include "comm.h"

#include <QTcpSocket>
#include <QHostAddress>

#include <QString>
#include <QByteArray>
#include <QAbstractSocket>
#include <QTcpServer>

namespace HYKT {

class TcpComm : public Comm
{
    Q_OBJECT
public:
    TcpComm();
    ~TcpComm() override;

    virtual int Open(int net_type, QString des_ip, quint16 des_port) override;
    virtual void Close() override;
    virtual int Send(const char *data, int len) override;
    virtual int Send(const QByteArray &data) override;
    virtual bool IsOpen() override;

private:
    virtual void DoRecv() override;
    virtual void DoError(QAbstractSocket::SocketError se) override;
    void DoOnDisconnected();
    void DonewConnection();

private:
    QTcpSocket *tcp_p;
    QTcpServer *server_p;
    int net_type_;

    QString des_ip_;
    quint16 des_port_;

    QString received_client_ip_;
    quint16 received_client_port_;
    bool is_connected_;

};

} //namespace HYKT

#endif // TCPCOMM_H
