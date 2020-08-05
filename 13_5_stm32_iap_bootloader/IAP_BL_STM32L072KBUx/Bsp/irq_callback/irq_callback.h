#ifndef BSP_IRQ_CALLBACK_H_
#define BSP_IRQ_CALLBACK_H_

#include "includes.h"

extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart1;

extern void BSP_EnableIrq();
extern void BSP_DisableIrq();


#endif //BSP_IRQ_CALLBACK_H_
