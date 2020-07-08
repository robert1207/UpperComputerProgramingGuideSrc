#ifndef HEXFILEREADER_H
#define HEXFILEREADER_H

#include <QObject>

#include "../file/binaryfile.h"

class HexFileReader : public QObject
{
    Q_OBJECT
public:
    HexFileReader();
    ~HexFileReader();

    bool Open(QString file_path);
    void Close();

    quint16 GetTotalPieceCount();
    quint16 GetPieceDataSize();
    char* GetOnePieceDataAtIndex(quint32 page_index);
    char* GetNextPieceData();

private:
    const static quint16 piece_array_len = 128;
    char piece_array[piece_array_len];


    BinaryFile binary_file_;

};

#endif // HEXFILEREADER_H
