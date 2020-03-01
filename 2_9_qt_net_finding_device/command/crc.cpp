

#include "crc.h"

#include <QDebug>

namespace HYKT {

Crc::Crc()
{

}

Crc::~Crc()
{

}

void Crc::GetCRC(quint8 *data, int len, quint16 &crc) {
    quint16 i,j,carry_flag, temp;

    crc = 0xffff;

    for (i = 0; i < len; i++) {
        crc = crc ^ data[i];
        for (j = 0; j < 8; j ++) {
            temp = crc;
            carry_flag = temp & 0x0001;
            crc = crc >> 1;

            if (carry_flag == 1) {
                 crc = crc ^ 0xa001;
            }
         }
    }
}


bool Crc::CheckCRC(quint8 *data, int len) {
    if (len < 2) return false;

    quint16 crcLow = data[len - 1];
    quint16 crcHigh = data[len - 2];
    quint16 crc_received = static_cast<quint16>(crcHigh << 8 | crcLow);
    quint16 crc_new;

    GetCRC(data, len - 2, crc_new);

    /*
    qDebug() << "crc new low = " << QString::number(crc_new & 0xff, 16);
    qDebug() << "crc new  high = " << QString::number((crc_new >> 8) & 0xff, 16);

    qDebug() << "crc_received low = " << QString::number(crc_received & 0xff, 16);
    qDebug() << "crc_received high = " << QString::number((crc_received >> 8) & 0xff, 16);
    */

    if (crc_new == crc_received) {
        return true;
    }

    return false;
}

} //namespace HYKT
