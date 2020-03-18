

#include "devicefinder.h"
#include "../protocol/command.h"

#include "../utils/byteutil.h"


namespace HYKT {

DeviceFinder::DeviceFinder()
{
    connect(this, &DeviceFinder::SafeCloseNetManager,
            this, &DeviceFinder::SafeCloseNetManagerSlot, Qt::ConnectionType::QueuedConnection);
}

DeviceFinder::~DeviceFinder()
{
    disconnect(this, &DeviceFinder::SafeCloseNetManager, this, &DeviceFinder::SafeCloseNetManagerSlot);
}

void DeviceFinder::SafeCloseNetManagerSlot() {

    disconnect(&timer_, &QTimer::timeout, this , &DeviceFinder::Update);

    if(net_manager_p == nullptr) return;

    if(net_manager_p->IsOpen()) {
        StopFind();
    }

    disconnect(net_manager_p, &NetManager::onRecv, this, &DeviceFinder::onRecv);
    disconnect(net_manager_p, &NetManager::onError, this, &DeviceFinder::onError);

    if(net_manager_p != nullptr && net_manager_p->IsOpen()) {
        net_manager_p->Close();
    }

    delete  net_manager_p;
}

void DeviceFinder::Update() {

    if( is_finding_ == false ) return;
    if(net_manager_p == nullptr) {
        return;
    }

    if(net_manager_p->IsOpen()) {
        QByteArray *data = Command::SearchDevice();
        int res = net_manager_p->Send(*data );
        delete data;
        if(res < 0) is_finding_ = false;
    }
}

void DeviceFinder::StartFind(QString ip_of_adapter) {
    is_finding_ = false;
    package_on_ = false;

    net_manager_p = new NetManager();//NetManager::GetInstance();
    connect(net_manager_p, &NetManager::onRecv, this, &DeviceFinder::onRecv);
    connect(net_manager_p, &NetManager::onError, this, &DeviceFinder::onError);
    connect(&timer_, &QTimer::timeout, this , &DeviceFinder::Update);

    net_adapter_ip_ = ip_of_adapter;
    is_finding_ = true;
    net_manager_p->Open(Comm::NetType::UDP_broadcast, net_adapter_ip_, UDP_DEVICE_PORT);
    Update();
    Update();
    timer_.start(100);
}

void DeviceFinder::StopFind() {
    is_finding_ = false;//
    timer_.stop();

    emit SafeCloseNetManager();
}

void DeviceFinder::onRecv(QByteArray *data, QString ip, quint16 port) {
    Q_UNUSED(ip)
    Q_UNUSED(port)

    temp_device_ip_ = ip;
    for(int a = 0; a < data->length(); a ++) {
        Process(static_cast<quint8>(data->at(a)));
    }
}

void DeviceFinder::onError(int error_code, QString extra_error_info) {
    QString error_info =  "error code =" + QString::number(error_code) + " extra info =" + extra_error_info;

    StopFind();
    emit onFindingError(error_info);
}

QList<DeviceInfo> DeviceFinder::GetFountDeviceList() {
    return found_device_list_;
}

void DeviceFinder::Clear() {
    found_device_list_.clear();
}

bool DeviceFinder::IsDeviceExist(DeviceInfo device) {
    int count = found_device_list_.count();
    for(int a = 0; a < count; a ++) {
        DeviceInfo dev = found_device_list_.at(a);
        if(dev.ip == device.ip ) {
            return true;
        }
    }
    return false;
}

void DeviceFinder::Process(quint8 b) {
    if (package_on_ == true)
    {
        if (pos > CACHE_LENGTH) {
            package_on_ = false;
            pos = 0;
            return;
        }

        cache[pos++] = b;

        if (pos > 4 &&
            cache[pos - 4] == tail[0] &&    //a pkg is finished
            cache[pos - 3] == tail[1] &&
            cache[pos - 2] == tail[2] &&
            cache[pos - 1] == tail[3] &&
            cache[sizeof (head)] + sizeof (head) + sizeof (tail)  == pos //check pkg len
                ) {

            package_on_ = false;

            int skip_head_and_pkg_len = 2;
            int skip_tail = 4;
            quint8* pkg = &cache[skip_head_and_pkg_len];
            int pkg_len = pos - skip_head_and_pkg_len - skip_tail;//skip index of tail byte

            if (Crc::CheckCRC(pkg, pkg_len) == true) {
                ProcessMetaPkg(pkg, pkg_len-2);
            } else {
                StopFind();
                emit onFindingError("crc check error");
            }
        }
    } else if (package_on_ == false && b == head[0]) { //start a pkg
        package_on_ = true;
        pos = 0;
        cache[pos++] = b;
    }
}

void DeviceFinder::ProcessMetaPkg(quint8 *pkg, int len) {
    char* msg = new char[len];
    ByteUtil::ByteArray2CharArray(pkg, msg, len);
    QString message(msg);

    //std_str = "myname;0002231;V1.2.3"

    if (message.contains("myname")) {

        QStringList str_list =  message.split(';');
        DeviceInfo dev;
        dev.name = "myname";
        dev.ip = temp_device_ip_;

        for (int a = 0; a < str_list.length(); a++) {
            if (a == 1) { //get sn
                QString sn = str_list[a];
                dev.sn = sn;
            }
            if (a == 2)  {  //get version
                QString version = str_list[a];
                dev.version = version;
            }
        }

        if(!IsDeviceExist(dev)) {
            found_device_list_.append(dev);
        }
    }
    delete[] msg;
}


} //namespace HYKT

