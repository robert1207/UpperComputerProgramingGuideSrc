

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
        SetValue = 0x01,        //upper-computer setvalue to down-computer
        GetValue = 0x02,        //upper-computer getvalue from down-computer
        ReportValue = 0x03        //down-computer reportvalue to upper-computer
    };



    /*******************************************  *************************************/

    inline static QByteArray* ResponseForSearching() {
        QByteArray data;
        data.append(SetValue);
        data.append(0x6D);
        data.append(0x79);
        data.append(0x6e);
        data.append(0x61);
        data.append(0x6D);
        data.append(0x65);
        data.append(0x3b);
        data.append(0x30);
        data.append(0x30);
        data.append(0x30);
        data.append(0x32);
        data.append(0x32);
        data.append(0x33);
        data.append(0x31);
        data.append(0x3b);
        data.append(0x56);
        data.append(0x31);
        data.append(0x2e);
        data.append(0x32);
        data.append(0x2e);
        data.append(0x33);
        return Pack(data);
    }

    //e.g : SetValue
    inline static QByteArray* ResponseForSetPositionValue() {
        QByteArray data;
        data.append(SetValue);
        data.append(0x01);
        return Pack(data);
    }

    //e.g : GetValue
    inline static QByteArray* ResponseForGetTemperature(int temperature) {
        QByteArray data;
        data.append(GetValue);
        data.append(0x01);

        int t1 = temperature / 100 + 48;
        int t2 = temperature % 100 / 10 + 48;
        int t3 = temperature % 10 + 48;

        data.append(ByteUtil::Int2Char(t1));
        data.append(ByteUtil::Int2Char(t2));
        data.append(ByteUtil::Int2Char(t3));

        return Pack(data);
    }

    //e.g : ReportValue
    inline static QByteArray* ResponseForReportValue(int value) {
        QByteArray data;
        data.append(ReportValue);
        data.append(0x01);

        int t1 = value / 100 + 48;
        int t2 = value % 100 / 10 + 48;
        int t3 = value % 10 + 48;

        data.append(ByteUtil::Int2Char(t1));
        data.append(ByteUtil::Int2Char(t2));
        data.append(ByteUtil::Int2Char(t3));

        return Pack(data);
    }

};

} //namespace HYKT

#endif // COMMAND_H
