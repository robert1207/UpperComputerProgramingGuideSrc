#include "byteutil.h"

ByteUtil::ByteUtil()
{

}

char ByteUtil::Byte2Char(const byte byte) {
    char ret = 0x00;
    ret = ret | byte;
    return ret;
}

byte ByteUtil::Char2Byte(const char ch) {
    byte by = 0x00;
    by = static_cast<byte>(by | ch);
    return by;
}

//only last 8bit of int is saved
char ByteUtil::Int2Char(const int value) {
     return Byte2Char(static_cast<unsigned char>(value));
}

int ByteUtil::Char2Int(const char ch) {
    byte t = Char2Byte(ch);
    return static_cast<int>(t);
}


void ByteUtil::ByteArray2CharArray(const byte * src, char *dst, int len) {
    for (int a = 0; a < len; a++) {
        dst[a] = Byte2Char(src[a]);
    }
}

void ByteUtil::CharArray2ByteArray(const char * src, byte *dst, int len) {
    for (int a = 0; a < len; a++) {
        dst[a] = Char2Byte(src[a]);
    }
}

