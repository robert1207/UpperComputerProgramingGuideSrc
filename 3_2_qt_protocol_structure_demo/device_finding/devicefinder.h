

#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <QObject>
#include <QList>
#include <QTimer>

#include "deviceinfo.h"
#include "./net/netmanager.h"

namespace HYKT {

class DeviceFinder : public QObject
{
    Q_OBJECT
public:
    DeviceFinder();
    ~DeviceFinder();

    void StartFind(QString ip_of_adapter);
    void StopFind();
    QList<DeviceInfo> GetFountDeviceList();
    void Clear();

signals:
    void onFindingError(QString msg);
    void SafeCloseNetManager();

private slots:
    void Update();
    void onRecv(QByteArray *data, QString ip, quint16 port);
    void onError(int error_code, QString extra_error_info);
    void SafeCloseNetManagerSlot();

private:
    bool IsDeviceExist(DeviceInfo device);
    void Process(quint8 b);
    void ProcessMetaPkg(quint8 *pkg, int len);

private:
    bool is_finding_;
    NetManager* net_manager_p;
    QList<DeviceInfo> found_device_list_;

    //package param
    bool package_on_;
    const static int CACHE_LENGTH = 1024 * 5;
    quint8 cache[CACHE_LENGTH];
    int pos;
    QString net_adapter_ip_;
    QTimer timer_;

    const static quint16 UDP_DEVICE_PORT = 2009;
    QString temp_device_ip_;

};
} //namespace HYKT

#endif // DEVICEFINDER_H
