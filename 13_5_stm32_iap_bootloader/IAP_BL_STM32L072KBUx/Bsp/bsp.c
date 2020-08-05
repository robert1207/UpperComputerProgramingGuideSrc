#include "bsp.h"

TIM_HandleTypeDef htim7;

UART_HandleTypeDef huart1;

void BSP_Init() {
	SystemClock_Config();
	BSP_IoInit();

	BSP_TimeCounterInit();
	BSP_Uart1Init();
	BSP_UartRecvReset();
}

void Error_Handler(void)
{

}
