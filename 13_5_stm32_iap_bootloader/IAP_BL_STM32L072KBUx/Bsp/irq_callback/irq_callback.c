#include "irq_callback.h"

static bool isTimerCallbackHappend = false;

void BSP_EnableIrq() {
	__set_PRIMASK(0);//打开中断
}

void BSP_DisableIrq() {
	__set_PRIMASK(1);//关闭中断
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	APP_UartProcess(RxBuf[0]);
	BSP_UartRecvReset();//重新使能串口接收中断
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == (&htim7)) {
		//注意以中断方式启动定时器的时候，会直接触发一次本中断
		if (isTimerCallbackHappend == false) {
			isTimerCallbackHappend = true;
			return;
		} else {
			BSP_500msIRQ();
		}
	}
}
