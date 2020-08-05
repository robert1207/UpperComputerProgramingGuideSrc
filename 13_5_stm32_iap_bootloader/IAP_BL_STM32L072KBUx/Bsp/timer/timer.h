#ifndef BSP_TIMER_H_
#define BSP_TIMER_H_


#include "includes.h"

extern TIM_HandleTypeDef htim7;
typedef void (*TimeUpCallback)();

extern void BSP_TimeCounterInit();
extern void BSP_SetTimeUpCallback(TimeUpCallback cb);
extern void BSP_500msIRQ();
extern void BSP_TimeCounterStart(uint32_t period_ms);
extern void BSP_TimeCounterStop();



#endif //BSP_TIMER_H_
