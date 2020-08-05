#include "command.h"

#include "crc.h"

/**
 * @brief	获取命令反馈封包,返回数据包长度
 * @param	resPkg 参数详情
 * @retval	反馈封包最终长度, -1 缓存数组长度不够
 */
int APP_GetProtocolResponsePKG(ResponsePkg *resPkg) {

	//CRC校验码 = [命令类型码 + 命令码 + 命令参数]
	//计算方括号内的数据
	uint16_t res_data_len = resPkg->param_len + 2;
	uint8_t res_data[res_data_len];
	res_data[0] = resPkg->command_type;
	res_data[1] = resPkg->command;
	for (int a = 0; a < resPkg->param_len; a++) {
		res_data[2 + a]  = resPkg->param_buf[a];
	}

	//计算缓存数据是否够用
	uint16_t buffer_need_len = res_data_len + 8;
	if(buffer_need_len > resPkg->res_buffer_len) return -1;

	//CRC校验码
	uint16_t crc;
	GetCRC(res_data, res_data_len, &crc);
	uint8_t crc_high_byte = (crc >> 8) & 0xff;
	uint8_t crc_low_byte = crc & 0xff;

	//组装封包
	uint8_t* res_buf = resPkg->res_buffer;
	int res_buf_index = 0;

	res_buf[res_buf_index++] = HEAD[0];
	res_buf[res_buf_index++] = 0;//temp pkg len

	for (int a = 0; a < res_data_len; a++) {
		res_buf[res_buf_index++]  = res_data[a];
	}
	res_buf[res_buf_index++] = crc_high_byte;
	res_buf[res_buf_index++] = crc_low_byte;

	uint8_t tail_buf_len = sizeof(TAIL);
	for (int a = 0; a < tail_buf_len; a++) {
		res_buf[res_buf_index++]  = TAIL[a];
	}

	//计算包长
	uint8_t head_len = sizeof(HEAD);
	uint8_t tail_len = sizeof(TAIL);
	uint8_t temp_pkg_len = res_buf_index;

	uint8_t pkg_len = temp_pkg_len - head_len - tail_len;
	res_buf[1] = pkg_len;

	return temp_pkg_len;
}


