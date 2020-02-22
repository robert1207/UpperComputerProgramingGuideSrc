/*
 * @Name       kcp_tool
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-02
 */

#include "comm.h"




namespace HYKT {

const QList<QString> Comm::net_type_str_list_ = {
    "UDP broadcase", "UDP client", "UDP server", "TCP client", "TCP server"};

Comm::Comm()
{

}

Comm::~Comm()
{

}

QList<QString> Comm::GetNetTypeStrList() {
    return net_type_str_list_;
}

} //namespace HYKT

