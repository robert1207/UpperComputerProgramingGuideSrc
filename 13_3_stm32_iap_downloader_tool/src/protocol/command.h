

#ifndef COMMAND_H
#define COMMAND_H

#include "qglobal.h"
#include "crc.h"

#include <QByteArray>
#include <QDateTime>

#include "../utils/byteutil.h"

const static quint8 head[] = {0xff}; //放置自己特有的 包头
const static quint8 tail[] = {0xe3, 0xd1, 0xac, 0xb5}; //放置自己特有的 包尾巴

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

    inline static QByteArray* HexDownloadStart() {
        QByteArray data;
        data.append(SetValue);
        data.append(0x02);
        return Pack(data);
    }

    inline static QByteArray* HexDownloadEnd() {
        QByteArray data;
        data.append(SetValue);
        data.append(0x03);
        return Pack(data);
    }

    inline static QByteArray* HexDownloadData(quint16 piece_index, bool is_last_piece, char *buf, int len) {
        QByteArray data;
        data.append(SetValue);
        data.append(0x04);

        //pieces index
        char piece_h =  ByteUtil::Byte2Char((piece_index >> 8) & 0xff);
        char piece_l = ByteUtil::Byte2Char((piece_index >> 0) & 0xff);
        data.append(piece_h);
        data.append(piece_l);
        if(is_last_piece) {
            data.append(0x01);
        } else {
            data.append(static_cast<char>(0));
        }

        //hex data
        for (int a = 0; a < len; a ++) {
            data.append(buf[a]);
        }

        return Pack(data);
    }

    inline static QByteArray* HexDownloadDataCheck(quint32 check_sum, quint32 piece_count) {
        QByteArray data;
        data.append(SetValue);
        data.append(0x05);

        char sum_1 =  ByteUtil::Byte2Char((check_sum >> 24) & 0xff);
        char sum_2 = ByteUtil::Byte2Char((check_sum >> 16) & 0xff);
        char sum_3 =  ByteUtil::Byte2Char((check_sum >> 8) & 0xff);
        char sum_4 = ByteUtil::Byte2Char((check_sum >> 0) & 0xff);

        data.append(sum_1);
        data.append(sum_2);
        data.append(sum_3);
        data.append(sum_4);

        char sum_5 =  ByteUtil::Byte2Char((piece_count >> 24) & 0xff);
        char sum_6 = ByteUtil::Byte2Char((piece_count >> 16) & 0xff);
        char sum_7 =  ByteUtil::Byte2Char((piece_count >> 8) & 0xff);
        char sum_8 = ByteUtil::Byte2Char((piece_count >> 0) & 0xff);

        data.append(sum_5);
        data.append(sum_6);
        data.append(sum_7);
        data.append(sum_8);

        return Pack(data);
    }






};

#endif // COMMAND_H
