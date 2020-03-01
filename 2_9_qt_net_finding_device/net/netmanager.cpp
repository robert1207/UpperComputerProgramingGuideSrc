


#include "netmanager.h"

#include <QNetworkInterface>

namespace HYKT {


NetManager::NetManager()
{
    comm_p = nullptr;
}

NetManager::~NetManager()
{
    if (comm_p != nullptr) {

        if(IsOpen()) {

            Close();
        }
    }
}

QList<QString> NetManager::GetNetTypeStrList() {
    return Comm::GetNetTypeStrList();
}

int NetManager::Open(int net_type, QString des_ip, quint16 des_port) {
    if(net_type == Comm::NetType::UDP_broadcast ||
            net_type == Comm::NetType::UDP_client ||
            net_type == Comm::NetType::UDP_server ) {
        comm_p = new UdpComm();
        ConnectSignals();
        return comm_p->Open(net_type, des_ip, des_port);
    } else {
        comm_p = new TcpComm();
        ConnectSignals();
        return comm_p->Open(net_type, des_ip, des_port);
    }
}

void NetManager::Close() {
    DisconnectSignals();
    comm_p->Close();
    delete comm_p;
    comm_p = nullptr;
}

int NetManager::Send(char *data, int len) {
    return comm_p->Send(data, len);
}

int NetManager::Send(const QByteArray &data) {
    return comm_p->Send(data);
}

bool NetManager::IsOpen() {
    if(comm_p == nullptr) {
        return false;
    }
    return comm_p->IsOpen();
}

void NetManager::ConnectSignals() {
    connect(comm_p, &Comm::onRecv, this, &NetManager::onRecv);
    connect(comm_p, &Comm::onError, this, &NetManager::onError);
}

void NetManager::DisconnectSignals() {
    disconnect(comm_p, &Comm::onRecv, this, &NetManager::onRecv);
    disconnect(comm_p, &Comm::onError, this, &NetManager::onError);
}



QList<QString> NetManager::GetIpListOfComputer() {
    QList<QString> ret_list;

    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();

    foreach(QNetworkInterface interfaceItem, interfaceList)
    {
        if(interfaceItem.flags().testFlag(QNetworkInterface::IsUp)
                &&interfaceItem.flags().testFlag(QNetworkInterface::IsRunning)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanBroadcast)
                &&interfaceItem.flags().testFlag(QNetworkInterface::CanMulticast)
                &&!interfaceItem.flags().testFlag(QNetworkInterface::IsLoopBack)

         //       &&!interfaceItem.humanReadableName().contains("VMware")
             //   &&!interfaceItem.humanReadableName().contains("vnic") //mac parallels
              //  &&!interfaceItem.humanReadableName().contains("Npcap") //windows wareshark，enable this line will
                                                                                                                                   //make upd send blocked,or confused
                )
        {
            QList<QNetworkAddressEntry> addressEntryList=interfaceItem.addressEntries();
            foreach(QNetworkAddressEntry addressEntryItem, addressEntryList)
            {
                if(addressEntryItem.ip().protocol()==QAbstractSocket::IPv4Protocol)
                {
                    qDebug()<<"------------------------------------------------------------";
                    qDebug()<<"Adapter Name:"<<interfaceItem.name();
                    qDebug()<<"Adapter Address:"<<interfaceItem.hardwareAddress();
                    qDebug()<<"IP Address:"<<addressEntryItem.ip().toString();
                    qDebug()<<"IP Mask:"<<addressEntryItem.netmask().toString();

                    qDebug() << "can filter name" << interfaceItem.humanReadableName();

                    ret_list.append(addressEntryItem.ip().toString());
                }
            }
        }
    }

    return ret_list;
}

} //namespace HYKT
