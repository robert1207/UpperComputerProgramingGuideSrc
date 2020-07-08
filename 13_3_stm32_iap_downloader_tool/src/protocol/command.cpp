
#include "command.h"

#include "../utils/byteutil.h"


Command::Command()
{

}

Command::~Command()
{

}

QByteArray* Command::Pack(QByteArray &data) {
    QByteArray *ret = new QByteArray();

    quint16 crc;
    Crc::GetCRC(reinterpret_cast<quint8*>(data.data()), data.length(), crc);
    quint8 high_byte = (crc >> 8) & 0xff;
    quint8 low_byte = crc & 0xff;

    char head_char_array[sizeof(head)];
    ByteUtil::ByteArray2CharArray(head, head_char_array, sizeof(head));

    char tail_char_array[sizeof(tail)];
    ByteUtil::ByteArray2CharArray(tail, tail_char_array, sizeof(tail));

    ret->append(head_char_array, sizeof(head_char_array));
    ret->append(data);
    ret->append(ByteUtil::Byte2Char(high_byte));
    ret->append(ByteUtil::Byte2Char(low_byte));
    ret->append(tail_char_array, sizeof(tail_char_array));

    int head_len = sizeof(head);
    int tail_len = sizeof(tail);

    int pkg_len = ret->length() - head_len - tail_len + 1; //+1 for include self
    ret->insert(head_len, ByteUtil::Int2Char(pkg_len));

/*
    quint8 *dst =  new quint8[ret->length()];
    ByteUtil::CharArray2ByteArray(ret->data(), dst, ret->length());
    for(int a = 0; a < ret->length(); a ++) {
        printf("%d dst hex=%02x \n", a,dst[a]);
    }
    delete[] dst;
    */


    return ret;
}

