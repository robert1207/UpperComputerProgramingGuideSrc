/*
 * @Name       net
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-05
 */

#include "tcpcomm.h"

namespace HYKT {

TcpComm::TcpComm()
{
    is_connected_ = false;
    tcp_p = nullptr;
}

TcpComm::~TcpComm()
{
    if(IsOpen()) {
        Close();
    }
    is_connected_ = false;

}

/*
 * Usage:
 * tcp server:        Open(Comm::NetType::TCP_server, "", listen_port);
 * tcp client:        Open(Comm::NetType::TCP_client, des_ip, des_port);
 */
int TcpComm::Open(int net_type, QString des_ip, quint16 des_port) {
    net_type_ = net_type;

    if(net_type_ == NetType::TCP_client) {
        tcp_p = new QTcpSocket(this);
        QHostAddress addr(des_ip);
        tcp_p->connectToHost(addr, des_port);
        if (!tcp_p->waitForConnected(10000)) //10s
        {
           return ErrorOpen;
        }

        received_client_ip_ = des_ip;
        received_client_port_ = des_port;

        connect(tcp_p, &QTcpSocket::readyRead, this, &TcpComm::DoRecv);
        connect(tcp_p, &QTcpSocket::disconnected, this, &TcpComm::DoOnDisconnected);
        connect(tcp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpComm::DoError);

    } else if (net_type_ == NetType::TCP_server) {
        server_p  = new QTcpServer(this);
        connect(server_p, &QTcpServer::newConnection, this, &TcpComm::DonewConnection);
        if(!server_p->listen(QHostAddress::Any, des_port)) {
            return ErrorOpen;
        }

    } else {
        return ErrorOpen;
    }

    is_connected_ = true;
    return NoError;
}

void TcpComm::Close() {

    disconnect(tcp_p, &QTcpSocket::readyRead, this, &TcpComm::DoRecv);
    disconnect(tcp_p, &QTcpSocket::disconnected, this, &TcpComm::DoOnDisconnected);
    disconnect(tcp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpComm::DoError);

    if(net_type_ == NetType::TCP_client) {
        tcp_p->disconnectFromHost();
        if (tcp_p->state() == QAbstractSocket::UnconnectedState \
                                || tcp_p->waitForDisconnected(1000))  {}

    } else if (net_type_ == NetType::TCP_server) {
        disconnect(server_p, &QTcpServer::newConnection, this, &TcpComm::DonewConnection);
    }

    if(tcp_p->isOpen()) {
        tcp_p->close();
    }

    delete tcp_p;
    tcp_p = nullptr;
    is_connected_ = false;
}

bool TcpComm::IsOpen() {
    if(is_connected_ == false) return false;
    if(tcp_p == nullptr) return false;
    return tcp_p->isOpen();
}

int TcpComm::Send(const char *data, int len) {

   // if(net_type_ == NetType::TCP_client) {
        qint64 res;
        res = tcp_p->write(data, len);
       // tcp_p->flush();

        if(res < 0) {
            qDebug() << "error TcpComm::Send , code =" << res;
            emit onError(ErrorSend, QString::number(res));
            return  ErrorSend;
        }

 //   } else if (net_type_ == NetType::TCP_server) {

 //   }

    return NoError;
}

int TcpComm::Send(const QByteArray &data) {
    return Send(data.data(), data.length());
}

void TcpComm::DoRecv() {
   // if(net_type_ == NetType::TCP_client) {
        QByteArray buffer = tcp_p->readAll();
        if(buffer.length() > 0) {
            emit onRecv(&buffer, received_client_ip_, received_client_port_);
        }

  //  } else if (net_type_ == NetType::TCP_server) {

  //  }
}

void TcpComm::DoError(QAbstractSocket::SocketError se) {
    is_connected_ = false;
    Q_UNUSED(se)
    emit onError(ErrorConnection, tcp_p->errorString());
}

void TcpComm::DoOnDisconnected() {
    is_connected_ = false;
    emit onError(ErrorConnection, "OnDisconnected");
}

void TcpComm::DonewConnection() {

    if(tcp_p != nullptr) {
        disconnect(tcp_p, &QTcpSocket::readyRead, this, &TcpComm::DoRecv);
        disconnect(tcp_p, &QTcpSocket::disconnected, this, &TcpComm::DoOnDisconnected);
        disconnect(tcp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpComm::DoError);
    }

    tcp_p = server_p->nextPendingConnection();
    received_client_ip_ = tcp_p->peerAddress().toString();
    received_client_port_ = tcp_p->peerPort();

    connect(tcp_p, &QTcpSocket::readyRead, this, &TcpComm::DoRecv);
    connect(tcp_p, &QTcpSocket::disconnected, this, &TcpComm::DoOnDisconnected);
    connect(tcp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpComm::DoError);

}


} //namespace HYKT

