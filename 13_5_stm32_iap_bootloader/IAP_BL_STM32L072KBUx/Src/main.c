/* USER CODE BEGIN Header */
//上面这行代码，会保护此文件内的现有代码不被 cubemx重新生成的时候覆盖掉。#include "includes.h"

#include "includes.h"

static bool startup_wait_flag = true;
static bool is_startup_wait_timeout = false;

static void TimeUp() {
	Main_ClearStartupFlag(true);
}

//定时器超时中断后，会调用此函数， 传true
//收到下载固件命令也会调用此函数，传false
void Main_ClearStartupFlag(bool isTimeout) {
	startup_wait_flag = false;
	is_startup_wait_timeout = isTimeout;
}

static void Main_ProcessWhileLoop() {
	//在9600波特率的速度下,传输1byte需要花费1ms.一个最小的数据协议封包是8byte.因此最快8ms接收一个协议封包
	//需要保证处理解析数据的速度大于接收速度,从而保证接受数据的双缓存够用,不会累积数据.因此这里的delay 推荐5ms
	HAL_Delay(5);//5ms处理一个完整数据包
	APP_ProcessProtocolReceivedPkgAtMain();
}

int main(void)
{
	HAL_Init();
	BSP_Init();

	//定时器：开始等待，下载固件的指令
	BSP_SetTimeUpCallback(TimeUp);
	BSP_TimeCounterStart(5000); //wait 5s
	while(startup_wait_flag) {
		Main_ProcessWhileLoop();//在等待超时的过程中，检测是否收到串口指令
	}

	//如果是因为等待超时，且有可用app则跳转到app执行
	if(is_startup_wait_timeout == true && APP_IsHadAppFlag()) {
		//printf("start app\n");
		APP_RunApp();
	}
	// APP_EraseAppUsingPages();//测试时候使用

	while (1)
	{
		Main_ProcessWhileLoop();
	}
}

//使用CubeMx生成代码后，把下面的代码都删除掉即可。
/* USER CODE END Header */
