#ifndef APP_CRC_H_
#define APP_CRC_H_

#include "includes.h"

extern void GetCRC(uint8_t *data, int16_t len, uint16_t *crc);
extern bool CheckCRC(uint8_t *data, int16_t len);

#endif //APP_CRC_H_
