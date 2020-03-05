#include "dma_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DMA_Clock(DMA_TypeDef* DMAx, UINT8_T isEnable)
{
	#ifdef DMA1
	if (DMAx == DMA1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
			#else
				LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA1);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
			#else
				LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA1);
			#else
				LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA1);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA1);
			#else
				LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA1);
			#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef DMA2
	if (DMAx == DMA2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
			#else
				LL_APB2_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
			#else
				LL_APB2_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA2);
			#else
				LL_APB2_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_DMA2);
			#endif
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			#ifndef USE_MCU_STM32F1
				LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA2);
			#else
				LL_APB2_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_DMA2);
			#endif
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	return ERROR_2;
}