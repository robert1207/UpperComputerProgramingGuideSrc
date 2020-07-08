/*
 * @Name       led_strip_editor
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-09-11
 */

#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDataStream>


class BinaryFile
{
public:
    BinaryFile();
    ~BinaryFile();

    bool Open(QString full_path);
    void Close();
    bool IsOpen();
    int Write(QByteArray &data);
    int Write(const char *data, int len);
    int Read(char *data, int len);
    qint64 Size();
    bool Seek(qint64 pos);
    void Flush();

private:
    QFile file_;
    QDataStream out_;

};


#endif // BINARYFILE_H
