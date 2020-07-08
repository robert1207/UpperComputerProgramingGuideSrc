

#include "work.h"

#include "../utils/byteutil.h"


Work::Work()
{
    failed_times = 0;
}

bool Work::CheckResponse(quint8 *return_pkg) {

    quint8 src_pkg_bit_1 = ByteUtil::Char2Byte(data.at(2));//command type
    quint8 src_pkg_bit_2 = ByteUtil::Char2Byte(data.at(3));//command code

   if (return_pkg[0] == src_pkg_bit_1 && return_pkg[1] == src_pkg_bit_2) {
       return true;
   } else {
       return false;
   }
}



