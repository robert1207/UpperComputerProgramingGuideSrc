/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */


#include "netmanager.h"

namespace HYKT {


NetManager::NetManager()
{
    comm_p = nullptr;
}

NetManager::~NetManager()
{
    if (comm_p != nullptr) Close();
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

} //namespace HYKT
