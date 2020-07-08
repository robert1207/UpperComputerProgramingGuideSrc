#include "hexfilereader.h"

HexFileReader::HexFileReader()
{

}

HexFileReader::~HexFileReader()
{

}

bool HexFileReader::Open(QString file_path) {
    return binary_file_.Open(file_path);
}

void HexFileReader::Close() {
    binary_file_.Close();
}

quint16 HexFileReader::GetTotalPieceCount() {

    qint64 size = binary_file_.Size();
    quint16 page_count = static_cast<quint16>(size / piece_array_len);

    if((size % piece_array_len) > 0) {
        page_count += 1;
    }
    return page_count;
}

quint16 HexFileReader::GetPieceDataSize() {
    return piece_array_len;
}

char* HexFileReader::GetOnePieceDataAtIndex(quint32 page_index) {

    qint64 seek_pos = page_index * piece_array_len;
    binary_file_.Seek(seek_pos);

    memset(piece_array, 0, piece_array_len);
    binary_file_.Read(piece_array, piece_array_len);
    return piece_array;
}

char* HexFileReader::GetNextPieceData() {

    memset(piece_array, 0, piece_array_len);
    binary_file_.Read(piece_array, piece_array_len);
    return piece_array;
}


