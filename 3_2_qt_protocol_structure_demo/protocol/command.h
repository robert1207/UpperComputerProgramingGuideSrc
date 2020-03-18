

#ifndef COMMAND_H
#define COMMAND_H

#include "qglobal.h"
#include "crc.h"

#include <QByteArray>
#include <QDateTime>

#include "../utils/byteutil.h"


namespace HYKT {

const static quint8 head[] = {0xff};
const static quint8 tail[] = {0xee, 0xfc, 0xff, 0xea};

class Command
{
private:
    Command();
    ~Command();

public:

    static QByteArray* Pack(QByteArray &data);

    enum CommandType {
        SetValue = 0x01,        //上位机给下位设置数据的命令类型
        GetValue = 0x02,        //上位机从下位机获取数据的命令类型
        ReportValue = 0x03        //下位机主动给上位机上报数据的命令类型
    };

    inline static bool IsCommandIsReportingType(quint8 *pkg) {
        return (Command::CommandType::ReportValue == pkg[0]);
    }

    /*******************************************  *************************************/

    inline static QByteArray* SearchDevice() {
        QByteArray data;
        data.append(SetValue);
        data.append(0x01);
        return Pack(data);
    }


    //e.g. SetValue command type
    inline static QByteArray* SendSetPositionValue(int value) {
        QByteArray data;
        data.append(SetValue);
        data.append(0x01);

        int t1 = value / 100 + 48;
        int t2 = value % 100 / 10 + 48;
        int t3 = value % 10 + 48;

        data.append(ByteUtil::Int2Char(t1));
        data.append(ByteUtil::Int2Char(t2));
        data.append(ByteUtil::Int2Char(t3));

        return Pack(data);
    }

     //e.g. GetValue command type
    inline static QByteArray* SendGetMachinetemperature() {
        QByteArray data;
        data.append(GetValue);
        data.append(0x01);
        return Pack(data);
    }

    inline static bool IsCommandGetMachinetemperature(quint8 *pkg) {
        if(pkg[0] == GetValue && pkg[1] == 0x01) return true; return false;
    }

    inline static int GetValueOfGetMachinetemperature(quint8 *pkg, int len) {
        Q_UNUSED(pkg)
        Q_UNUSED(len)
        //把命令字符 转换 为int类型的温度值
        int value = (pkg[2] - 48) * 100 + (pkg[3] - 48) * 10 + (pkg[4] - 48);
        return value;
    }

     //e.g. ReportValue command type
    inline static QByteArray* ResponseForReportValue() {
        QByteArray data;
        data.append(ReportValue);
        data.append(0x01);
        return Pack(data);
    }

    inline static bool IsCommandReportValue(quint8 *pkg) {
        if(pkg[0] == Command::CommandType::ReportValue && pkg[1] == 0x01)  return true; return false;
    }

    inline static int GetReportValue(quint8 *pkg, int len) {
        Q_UNUSED(pkg)
        Q_UNUSED(len)
        int value = (pkg[2] - 48) * 100 + (pkg[3] - 48) * 10 + (pkg[4] - 48);
        return value;
    }

};

} //namespace HYKT

#endif // COMMAND_H
