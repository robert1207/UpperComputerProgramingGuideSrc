#ifndef BSP_H_
#define BSP_H_


#include "io_and_clock/io_and_clock.h"
#include "./irq_callback/irq_callback.h"
#include "./uart/uart.h"
#include "./flash/flash.h"
#include "./timer/timer.h"

extern void BSP_Init();
extern void Error_Handler(void);

#endif //BSP_H_
