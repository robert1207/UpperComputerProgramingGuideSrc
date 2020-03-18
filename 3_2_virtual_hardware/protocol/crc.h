

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
