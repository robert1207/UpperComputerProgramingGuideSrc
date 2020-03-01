/*
 * @Name       protocol
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-08-06
 */

#ifndef CRC_H
#define CRC_H


#include "qglobal.h"

namespace HYKT {

class Crc
{
private:
        Crc();
        ~Crc();
public:
    static void GetCRC(quint8 *data, int len, quint16 &crc);
    static bool CheckCRC(quint8 *data, int len);
};

} //namespace HYKT

#endif // CRC_H
