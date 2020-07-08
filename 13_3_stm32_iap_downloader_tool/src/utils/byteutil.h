

#ifndef BYTEUTIL_H
#define BYTEUTIL_H

typedef unsigned char byte;


class ByteUtil
{
private:
    ByteUtil();

public:
    static char Byte2Char(const byte byte);
    static byte Char2Byte(const char ch);

    static char Int2Char(const int value);//only last 8bit of int is saved
    static int Char2Int(const char ch);

    static void ByteArray2CharArray(const byte * src, char *dst, int len);
    static void CharArray2ByteArray(const char * src, byte *dst, int len);
};

#endif // BYTEUTIL_H
