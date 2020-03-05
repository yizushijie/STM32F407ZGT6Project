#include "exti_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T EXTI_Init(void)
{
	//---使能端口始终
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOE, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---配置外部中断源
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTE, LL_SYSCFG_EXTI_LINE3);
	LL_EXTI_InitTypeDef EXTI_InitStruct = { 0 };
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---端口配置
	GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																			//---端口复用模式
	#endif
	LL_GPIO_Init(GPIOE, &GPIO_InitStruct);	
	//---中断配置
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_3;																			//---中断源编号
	EXTI_InitStruct.LineCommand = ENABLE;																				//---
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;																				//---使能中断
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;																	//---下降沿触发
	LL_EXTI_Init(&EXTI_InitStruct);
	NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	NVIC_EnableIRQ(EXTI3_IRQn);
	return OK_0;
}


UINT8_T EXTI_DisableIT(UINT32_T extiLine)
{
	LL_EXTI_EnableIT_0_31(extiLine);
	return OK_0;
}