


#include "findingdevicemanager.h"
//#include "my_log.h"

namespace HYKT {

FindingDeviceManager::FindingDeviceManager()
{
    timer_p = new QTimer();
    connect(timer_p, &QTimer::timeout, this, &FindingDeviceManager::Update);
}

FindingDeviceManager::~FindingDeviceManager()
{
    if(timer_p->isActive()) timer_p->stop();
    disconnect(timer_p, &QTimer::timeout, this, &FindingDeviceManager::Update);
    delete timer_p;
}

void FindingDeviceManager::StartFindingDevice() {
    QList<QString> ip_list = NetManager::GetIpListOfComputer();
    StopFindingDevice();

   // D << "ip conunt=" <<  ip_list.count();

    for (int a = 0; a < ip_list.count(); a ++) {
        QString ip = ip_list[a];
        //D << "ip :" << ip;
        DeviceFinder *device_finder = new DeviceFinder();

        connect(device_finder, &DeviceFinder::onFindingError,
                                this, &FindingDeviceManager::onFoundDeviceError);

        device_finder->StartFind(ip);
        device_finder_list_.append(device_finder);
    }

    timer_p->start(2000);
}

void FindingDeviceManager::StopFindingDevice() {
    timer_p->stop();

    for(int a = 0; a < device_finder_list_.count(); a ++) {
        DeviceFinder *device_finder = device_finder_list_.at(a);
        if(device_finder != nullptr) {
            disconnect(device_finder, &DeviceFinder::onFindingError,
                                    this, &FindingDeviceManager::onFoundDeviceError);
            device_finder->StopFind();
        }
    }

    for(int a = 0; a < device_finder_list_.count(); a ++) {
        DeviceFinder *device_finder = device_finder_list_.at(a);
         if(device_finder != nullptr) {
               delete device_finder;
         }
    }

    device_finder_list_.clear();
}

void FindingDeviceManager::Update() {
    QList<DeviceInfo> device_list_all;

    for(int a = 0; a < device_finder_list_.count(); a ++) {
        DeviceFinder *device_finder = device_finder_list_.at(a);
        QList<DeviceInfo> device_list = device_finder->GetFountDeviceList();

        for(int b = 0; b < device_list.count(); b ++) {
            DeviceInfo di = device_list.at(b);

            bool is_exist = false;
            for(int c = 0; c <  device_list_all.count(); c++) {
               if(device_list_all.at(c).ip == di.ip) { is_exist = true; break; }
            }

            if(is_exist == false) {
                device_list_all.append(di);
            }
        }
    }

    emit onFoundDevice(device_list_all);
}




} //namespace HYKT
