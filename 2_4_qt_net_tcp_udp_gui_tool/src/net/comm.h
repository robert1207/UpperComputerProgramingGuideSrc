/*
 * @Name       net
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-05
 */


#ifndef COMM_H
#define COMM_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QAbstractSocket>
#include <QList>

namespace HYKT {
class Comm : public QObject
{
    Q_OBJECT
public:
    Comm();
    virtual ~Comm();

    enum ErrorCode {
        NoError = 0,
        ErrorOpen,
        ErrorRecv,
        ErrorSend,
        ErrorConnection
    };

    enum NetType {
        UDP_broadcast,
        UDP_client,
        UDP_server,
        TCP_client,
        TCP_server
    };


    static QList<QString> GetNetTypeStrList();

    /*
     * Usage:
     * udp broadcast:   Open(Comm::NetType::UDP_client, "", des_port);
     * udp client:        Open(Comm::NetType::UDP_client, des_ip, des_port);
     * udp server:        Open(Comm::NetType::UDP_server, "", listen_port);
     * tcp client:        Open(Comm::NetType::TCP_client, des_ip, des_port);
     * tcp server:        Open(Comm::NetType::TCP_server, "", listen_port);
     */
    virtual int Open(int net_type, QString des_ip, quint16 des_port) = 0;
    virtual void Close() = 0;
    virtual int Send(const char *data, int len) = 0;
    virtual int Send(const QByteArray &data) = 0;
    virtual bool IsOpen() = 0;

private:
    virtual void DoRecv() = 0;
    virtual void DoError(QAbstractSocket::SocketError se) = 0;

signals:
    void onRecv(QByteArray *data, const QString ip, const quint16 port);
    void onError(int error_code, QString extra_error_info);

private:
    const static QList<QString> net_type_str_list_;

};

} //namespace HYKT


#endif // COMM_H
