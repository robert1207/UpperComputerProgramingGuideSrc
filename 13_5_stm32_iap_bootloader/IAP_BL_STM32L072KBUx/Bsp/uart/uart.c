#include "uart.h"

//TrueSTUDIO使用printf通过串口打印
//https://blog.csdn.net/u012308586/article/details/89514986

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE  int __io_putchar(int ch)
PUTCHAR_PROTOTYPE
{
	BSP_Uart1SendData((uint8_t*)&ch, 1);
  return ch;
}
#endif


uint8_t RxBuf[1];
bool is_set_uart_irq_recv_failed = false;
bool is_first_time_set_up_uart_it = false;


void BSP_Uart1Init() {
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 57600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		Error_Handler();
	}
}


/**
 * @brief	将485芯片设置为接收模式
 * @param	无
 * @retval	无
 */
static void SetIntoRevcMode() {
	HAL_GPIO_WritePin(GPIO_PORT_485_CTRL, GPIO_PIN_485_CTRL, GPIO_PIN_RESET);
}

/**
 * @brief	将485芯片设置为发送模式
 * @param	无
 * @retval	无
 */
static void SetIntoSendMode() {
	HAL_GPIO_WritePin(GPIO_PORT_485_CTRL, GPIO_PIN_485_CTRL, GPIO_PIN_SET);
}

/**
 * @brief	uart1初始化接收中断函数
 * @param	无
 * @retval	无
 */
void BSP_UartRecvReset() {
	uint16_t i = 0;

	SetIntoRevcMode();

	//在接收到快速的大量的数据,会导致设置 串口接收中断失败(这里的高速大量数据,是指超出 编程所指定的9600波特率的速度)
	//处理方法是,检测是否发生设置串口中断失败,并且重新设置

	while(HAL_UART_Receive_IT(&huart1, RxBuf, RX_BUF_LEN) != HAL_OK ) {
		i++;
		if( i > 10000 ) {
			huart1.RxState = HAL_UART_STATE_READY;
			__HAL_UNLOCK(&huart1);
			i = 0;
		}
	}
}

/**
 * @brief	uart1 发送数据
 * @param	data 数组指针
 * @param	len 数据长度
 * @retval	无
 */
void BSP_Uart1SendData(uint8_t *data, uint16_t len) {
	SetIntoSendMode();
	HAL_UART_Transmit(&huart1, data, len, HAL_MAX_DELAY);
	SetIntoRevcMode();
}

/**
 * @brief	处理接收中断错误
 * @retval	无
 */
void BSP_ProcessUartRecvError(void) {
	//在接收到快速的大量的数据,会导致设置 串口接收中断失败(这里的高速大量数据,是指超出 编程所指定的9600波特率的速度)
	//处理方法是,检测是否发生设置串口中断失败,并且重新设置
	if(is_set_uart_irq_recv_failed == true) {
		BSP_Uart1Init();
		is_set_uart_irq_recv_failed = false;
	}
}
