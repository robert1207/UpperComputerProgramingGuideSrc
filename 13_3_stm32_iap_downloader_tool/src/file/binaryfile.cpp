/*
 * @Name       led_strip_editor
 * @Author    Robert Zhang
 * @E-mail    zhangzhiguo1207@163.com
 * @Date       2019-09-11
 */

#include "binaryfile.h"



BinaryFile::BinaryFile()
{

}

BinaryFile::~BinaryFile()
{

}

bool BinaryFile::Open(QString full_path) {
    file_.setFileName(full_path);
    bool res = file_.open(QIODevice::ReadWrite);

    out_.setDevice(&file_);
    return res;
}

void BinaryFile::Close() {
    file_.flush();
    file_.close();
}

bool BinaryFile::IsOpen() {
    return file_.isOpen();
}

int BinaryFile::Write(QByteArray &data) {
    return out_.writeRawData(data.data(), data.length());
}

int BinaryFile::Write(const char *data, int len) {
    return out_.writeRawData(data, len);
}

int BinaryFile::Read(char *data, int len) {
    return out_.readRawData(data, len);
}

qint64 BinaryFile::Size() {
    return file_.size();
}

bool BinaryFile::Seek(qint64 pos) {
     return file_.seek(pos);
}

void BinaryFile::Flush() {
    file_.flush();
}


