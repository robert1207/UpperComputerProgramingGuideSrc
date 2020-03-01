

#ifndef DEVICEINFO_H
#define DEVICEINFO_H


#include <QString>

namespace HYKT {

class DeviceInfo
{
public:

    DeviceInfo();


    QString ip;
    QString name;//using this value to tell which kind of device it is
    QString sn;
    QString version;


    inline void operator=(DeviceInfo d) {
        this->ip = d.ip;
        this->sn = d.sn;
        this->name = d.name;
        this->version = d.version;
    }

};

} //namespace HYKT

#endif // DEVICEINFO_H
