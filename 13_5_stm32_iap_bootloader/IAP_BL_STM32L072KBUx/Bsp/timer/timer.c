#include "timer.h"

/*
 * 定时器的原始频率为:72000000
 * 预分频:720 得到频率为:100000
 * 100000 / 1000 = 100 周期为100的时候, 定时器1s触发1000次,即1ms一次
 * 100 * 500 = 50000 周期为50000的时候,定时器500ms触发一次
 */

//STM32 Cubemx 配置定时器定时1mS
//https://www.cnblogs.com/xingboy/p/9897500.html

static uint32_t period_ms_;

static TimeUpCallback timeup_cb = NULL;



void BSP_TimeCounterInit() {
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim7.Instance = TIM7;
	htim7.Init.Prescaler = 240-1;
	htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim7.Init.Period = 50000-1;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}


void BSP_SetTimeUpCallback(TimeUpCallback cb) {
	timeup_cb = cb;
}

void BSP_500msIRQ() {

	if(period_ms_ < 500) {
		period_ms_ = 0;
	} else {
		period_ms_ -= 500;
	}

	if(period_ms_ == 0) { //time up
		BSP_TimeCounterStop();

		if(timeup_cb != NULL) {
			timeup_cb();
		}
	}
}

/**
 * @brief	启动定时器(注意，只要保证，此函数内所写的频率与实际硬件频率匹配，则可以输出准确的 周期)
 * @param	定时器中断周期,单位ms
 * @retval	无
 */
void BSP_TimeCounterStart(uint32_t period_ms) {

	period_ms_ = period_ms;
	HAL_TIM_Base_Stop_IT(&htim7);

	//注意设置定时器周期的寄存器位16bit，因此，定时器最大周期位，65535，
	//通常，来说比如设定为50000，所得到的定时器，周期为500ms。这是接近周期的最大值了。
	//因此，如果要定时超过500ms，应该通过多次，累积，最终达到目标计时。而不是一次性设置所需周期，在定时器周期中。

	HAL_TIM_Base_Start_IT(&htim7);
}

void BSP_TimeCounterStop() {
	HAL_TIM_Base_Stop_IT(&htim7);
}
