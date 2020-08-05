#ifndef BSP_UART_H_
#define BSP_UART_H_

#include "includes.h"

extern UART_HandleTypeDef huart1;

#define RX_BUF_LEN 1
extern uint8_t RxBuf[1];
extern bool is_set_uart_irq_recv_failed;
extern bool is_first_time_set_up_uart_it;


#define GPIO_PORT_485_CTRL USART1_CTRL_GPIO_Port
#define GPIO_PIN_485_CTRL  USART1_CTRL_Pin

extern int __io_putchar(int ch);

extern void BSP_Uart1Init();
extern void BSP_UartRecvReset();
extern void BSP_Uart1SendData(uint8_t *data, uint16_t len);
extern void BSP_ProcessUartRecvError(void);


#endif //BSP_UART_H_
