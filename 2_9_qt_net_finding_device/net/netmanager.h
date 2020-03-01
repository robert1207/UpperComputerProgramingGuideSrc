


#ifndef NETMANAGER_H
#define NETMANAGER_H


#include "comm.h"
#include "udpcomm.h"
#include "tcpcomm.h"

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QList>

#include "singleinstance.h"

namespace HYKT {
class NetManager : public QObject
{
    Q_OBJECT
public:
    NetManager();
    ~NetManager();

    /*
    static inline NetManager* GetInstance() {
         return &Singleton<HYKT::NetManager>::instance();
    }*/

    static QList<QString> GetNetTypeStrList();

    static QList<QString> GetIpListOfComputer();

    int Open(int net_type, QString des_ip, quint16 des_port);
    void Close();
    int Send(char *data, int len);
    int Send(const QByteArray &data);
    bool IsOpen();

signals:
    void onRecv(QByteArray *data, const QString ip, const quint16 port);
    void onError(int error_code, QString extra_error_info);

private:
    void ConnectSignals();
    void DisconnectSignals();

private:
    Comm *comm_p;

};
} //namespace HYKT

#endif // NETMANAGER_H
