#include "crc.h"

/**
 * @brief	把包长、数据正文、数据参数，放到一个数组中。
 * 			把数组作为GetCRC的参数并调用GetCRC即可获取一个16bit的CRC校验码。
 * @param	data	原始数据数组
 * @param	len		数组长度
 * @retval	crc值 16bit
 */
void GetCRC(uint8_t *data, int16_t len, uint16_t *crc) {
    uint16_t i,j,carry_flag, temp;
    *crc = 0xffff;
    for (i = 0; i < len; i++) {
        *crc = *crc ^ data[i];
        for (j = 0; j < 8; j ++) {
            temp = *crc;
            carry_flag = temp & 0x0001;
            *crc = *crc >> 1;
            if (carry_flag == 1) {
                 *crc = *crc ^ 0xa001;
            }
         }
    }
}

/**
 * @brief	收到数据封包后，把封包的包头和包尾去掉，把剩下的部分放到一个数组中，
 * 			把此数组作为CheckCRC的参数，并调用CheckCRC，
 * 			即可通过此函数的返回值来判断CRC码是否匹配。
 * @param	data	原始数据数组
 * @param	len		数组长度
 * @retval	校验是否正确
 */
bool CheckCRC(uint8_t *data, int16_t len) {
    if (len < 2) return false;
    uint16_t crcLow = data[len - 1];
    uint16_t crcHigh = data[len - 2];
    uint16_t crc_received = (uint16_t)(crcHigh << 8 | crcLow);
    uint16_t crc_new;
    GetCRC(data, len - 2, &crc_new);
    if (crc_new == crc_received) {
        return true;
    }
    return false;
}
