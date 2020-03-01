

#ifndef COMMAND_H
#define COMMAND_H

#include "crc.h"

#include <QByteArray>
#include "../utils/byteutil.h"

namespace HYKT {

const static quint8 head[] = {0xee};
const static quint8 tail[] = {0xbb};


class Command
{
private:
    Command();
    ~Command();

public:

    static QByteArray* Pack(QByteArray &data);


    inline static QByteArray* SearchDevice() {
        QByteArray data;
        data.append(0x01);
        return Pack(data);
    }

    //put other command all at here at this class

};

} //namespace HYKT

#endif // COMMAND_H
