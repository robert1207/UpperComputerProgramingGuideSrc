

#ifndef FINDINGDEVICEMANAGER_H
#define FINDINGDEVICEMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>

#include "deviceinfo.h"
#include "devicefinder.h"


namespace HYKT {

class FindingDeviceManager : public QObject
{
    Q_OBJECT
public:
    FindingDeviceManager();
    ~FindingDeviceManager();

    void StartFindingDevice();
    void StopFindingDevice();

signals:
    void onFoundDevice(QList<DeviceInfo> device_list);//refresh and emit this signal every 10s
    void onFoundDeviceError(QString msg);

private:
    void Update();

private:
    QTimer *timer_p;
    QList<DeviceFinder*> device_finder_list_;
};
} //namespace HYKT

#endif // FINDINGDEVICEMANAGER_H
