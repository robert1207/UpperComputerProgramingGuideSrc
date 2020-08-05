#ifndef APP_COMMAND_H_
#define APP_COMMAND_H_

#include "includes.h"

const static uint8_t HEAD[1] = {0xFF};
const static uint8_t TAIL[4] = {0xE3, 0xD1, 0xAC, 0xB5};

typedef enum CommandType_ {
	SetValue	 	= 0x01,        //上位机给下位设置数据的命令类型
	GetValue 		= 0x02,        //上位机从下位机获取数据的命令类型
	ReportValue 	= 0x03         //下位机主动给上位机上报数据的命令类型

} CommandType;

typedef struct ResponsePkg_ {
	uint8_t* 	res_buffer;			//生成的返回数据包缓存数组
	uint16_t 	res_buffer_len;		//生成的返回数据包缓存数组长度
	uint8_t 	command_type;		//命令类型
	uint8_t 	command;			//返回命令
	uint8_t* 	param_buf;			//命令参数储存数组
	uint16_t 	param_len;			//命令参数储存数组长度
} ResponsePkg;


#define COMMAND_SHAKE_HANDS			0X01
#define COMMAND_DOWNLOAD_START		0X02
#define COMMAND_DOWNLOAD_STOP		0X03
#define COMMAND_DOWNLOAD_DATA		0X04
#define COMMAND_DOWNLOAD_CHECKSUM	0X05

extern int APP_GetProtocolResponsePKG(ResponsePkg *resPkg);

#endif //APP_COMMAND_H_
