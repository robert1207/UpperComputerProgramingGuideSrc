

#include "udpcomm.h"
#include "my_log.h"

namespace HYKT {

UdpComm::UdpComm()
{
}

UdpComm::~UdpComm()
{
    if(IsOpen()) {
        Close();
    }
}

/*
 * Usage:
 * udp server:Open(Comm::NetType::UDP_server, "", listen_port);
 * udp client:Open(Comm::NetType::UDP_client, des_ip, des_port);
 * udp broadcast:Open(Comm::NetType::UDP_client, "", des_port);
 */
int UdpComm::Open(int net_type, QString des_ip, quint16 des_port) {
    net_type_ = net_type;

    udp_p = new QUdpSocket(this);

    if(net_type_ == UDP_client) {
        des_ip_ = des_ip;
        des_port_ = des_port;
      //  udp_p->bind();
        udp_p->open(QIODevice::OpenModeFlag::ReadWrite);

    } else if (net_type_ == UDP_server) {
        udp_p->bind(des_port);
        udp_p->open(QIODevice::OpenModeFlag::ReadWrite);

    } else if (net_type_ == UDP_broadcast) {
        QHostAddress br(QHostAddress::Broadcast);
        QHostAddress ipv4_broadcast(br.toIPv4Address());
        des_ip_ = ipv4_broadcast.toString();
        des_port_ = des_port;
     //   udp_p->bind();
        udp_p->open(QIODevice::OpenModeFlag::ReadWrite);

    } else {
        return ErrorOpen;
    }

    connect(udp_p, &QUdpSocket::readyRead, this, &UdpComm::DoRecv);
    connect(udp_p, &QUdpSocket::disconnected, this, &UdpComm::DoOnDisconnected);
    //connect(udp_p, SIGNAL(error(QAbstractSocket::SocketError)), this,
    //                                                 SLOT(DoError(QAbstractSocket::SocketError)));
//https://stackoverflow.com/questions/48250574/how-to-connect-to-qtcpsocket-error-signal-in-qt
    connect(udp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                this, &UdpComm::DoError);
    return NoError;
}

void UdpComm::Close() {
    if(udp_p == nullptr)  return;

    disconnect(udp_p, &QUdpSocket::readyRead, this, &UdpComm::DoRecv);
    disconnect(udp_p, &QUdpSocket::disconnected, this, &UdpComm::DoOnDisconnected);
    disconnect(udp_p, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &UdpComm::DoError);

    if(udp_p->isOpen()) {
        udp_p->close();
    }

    delete udp_p;
    udp_p = nullptr;
}

bool UdpComm::IsOpen() {
    if (udp_p == nullptr) return false;
    return udp_p->isOpen();
}

int UdpComm::Send(const char *data, int len) {

    qint64 res;
    if(udp_p == nullptr || udp_p->isOpen() == false) return ErrorSend;

    if(net_type_ == UDP_client) {
        QHostAddress addr(des_ip_);
        res = udp_p->writeDatagram(data, len, addr, des_port_);

    } else if(net_type_ == UDP_server) {
        QHostAddress addr(received_client_ip_);
        res = udp_p->writeDatagram(data, len, addr, received_client_port_);

    } else if (net_type_ == UDP_broadcast) {
        QHostAddress addr(des_ip_);
        res = udp_p->writeDatagram(data, len, addr, des_port_);

    } else {
        return  ErrorSend;
    }

    if(res < 0) {
       // Close();
       // emit onError(ErrorSend,  QString::number(res));
        return  ErrorSend;
    }

    return NoError;
}

int UdpComm::Send(const QByteArray &data) {
    return Send(data.data(), data.length());
}

void UdpComm::DoRecv() {
    QByteArray *datagram;
    QHostAddress host;
    quint16 port = 0;

    if(udp_p == nullptr || udp_p->isOpen() == false) return;

    datagram = new QByteArray();
    datagram->resize(static_cast<int>(udp_p->pendingDatagramSize()));

    qint64 res;
    if(net_type_ == UDP_client) {
        res = udp_p->readDatagram(datagram->data(),datagram->size(), &host, &port);

    } else if (net_type_ == UDP_server) {
        res = udp_p->readDatagram(datagram->data(),datagram->size(), &host, &port);

    } else if (net_type_ == UDP_broadcast) {
        res = udp_p->readDatagram(datagram->data(),datagram->size(), &host, &port);

        D << "udp broadcast recv";

    } else {
        res = -1;
    }

    if (res < 0) {
        emit onError(ErrorRecv, QString::number(res));
    } else {
        QHostAddress ipv4(host.toIPv4Address());
        received_client_ip_ = ipv4.toString();
        received_client_port_ = port;
        emit onRecv(datagram, received_client_ip_, received_client_port_);
    }

    delete datagram;
}

void UdpComm::DoError(QAbstractSocket::SocketError se) {
    Q_UNUSED(se)
    QString error_str = "unknown error";
    if(udp_p != nullptr) {
        error_str = udp_p->errorString();
    }
    emit onError(ErrorConnection, error_str);
}

void UdpComm::DoOnDisconnected() {
    emit onError(ErrorConnection, "OnDisconnected");
}

} //namespace HYKT

