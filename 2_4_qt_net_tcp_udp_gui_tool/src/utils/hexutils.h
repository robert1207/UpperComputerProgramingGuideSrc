#ifndef HEXUTILS_H
#define HEXUTILS_H

#include <QByteArray>
#include <QStringList>

class HexUtils
{
private:
    HexUtils();
    static char convertCharToHex(char ch);


public:
    static void HexStringToByteArray(const QString &str, QByteArray &byteData);
    static QString ByteArrayToHexString(QByteArray data);


};

#endif // HEXUTILS_H
