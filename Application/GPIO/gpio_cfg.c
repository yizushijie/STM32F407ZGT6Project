#include "gpio_cfg.h"

#ifdef USE_MCU_STM32
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void GPIO_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable)
{
	//---ʹ�ܶ˿ڵ�ʱ��
#ifdef GPIOA
	if (GPIOx == GPIOA)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		#endif
		}
		return;
	}
#endif // GPIOA

#ifdef GPIOB
	if (GPIOx == GPIOB)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		#endif
		}
		return;
	}
#endif // GPIOB

#ifdef GPIOC
	if (GPIOx == GPIOC)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOC);
		#endif
		}
		return;
	}
#endif // GPIOC

#ifdef GPIOD
	if (GPIOx == GPIOD)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOD);
		#endif
		}
		return;
	}
#endif // GPIOD

#ifdef GPIOE
	if (GPIOx == GPIOE)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOE);
		#endif
		}
		return;
	}
#endif // GPIOE

#ifdef GPIOF
	if (GPIOx == GPIOF)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOF);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOF);
		#endif
		}
		return;
	}
#endif // GPIOF

#ifdef GPIOG
	if (GPIOx == GPIOG)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOG);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOG);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOG);
		#endif
		}
		return;
	}
#endif // GPIOG

#ifdef GPIOH
	if (GPIOx == GPIOH)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOH);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOH);
		#endif
		}
		return;
	}
#endif // GPIOH

#ifdef GPIOI
	if (GPIOx == GPIOI)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOI);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOI);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOI);
		#endif
		}
		return;
	}
#endif // GPIOI

#ifdef GPIOJ
	if (GPIOx == GPIOJ)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOJ);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOJ);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOJ);
		#endif
		}
		return;
	}
#endif // GPIOJ

#ifdef GPIOK
	if (GPIOx == GPIOK)
	{
		if (isEnable)
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOK);
		#endif
		}
		else
		{
		#ifndef USE_MCU_STM32F1
			LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOK);
		#else
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_GPIOK);
		#endif
		}
		return;
	}
#endif // GPIOK
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� void GPIO_Init(void)
//////��	   �ܣ� �������еĶ˿�Ϊģ������
//////�������: ��
//////�������: ��
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void GPIO_Init(void)
{
	//---ʹ�����ж˿ڵ�ʱ��
	#ifdef GPIOA
		GPIO_Clock(GPIOA, 1);
	#endif
	
	#ifdef GPIOB
		GPIO_Clock(GPIOB, 1);
	#endif
	
	#ifdef GPIOC
		GPIO_Clock(GPIOC, 1);
	#endif
	
	#ifdef GPIOD
		GPIO_Clock(GPIOD, 1);
	#endif
	
	#ifdef GPIOE
		GPIO_Clock(GPIOE, 1);
	#endif
	
	#ifdef GPIOF
		GPIO_Clock(GPIOF, 1);
	#endif
	
	#ifdef GPIOG
		GPIO_Clock(GPIOG, 1);
	#endif
	
	#ifdef GPIOH
		GPIO_Clock(GPIOH, 1);
	#endif
	
	#ifdef GPIOI
		GPIO_Clock(GPIOI, 1);
	#endif
	
	//---����ʱ��
	#ifndef USE_MCU_STM32F1
		//---ʹ�ܸ���ʱ��
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	#else
		//---ʹ�ܶ˿ڸ���ʱ��
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
	#endif
	
	//---�Ƿ�ʹ��SWD���Զ˿�
	#ifdef USE_DEBUG_SWD
		#ifdef  USE_MCU_STM32F1
			//---����JTAG�˿ڣ�ʹ��SWD�˿�
			LL_GPIO_AF_Remap_SWJ_NOJTAG();
			//---�ͷ�PB4�˿�
			LL_GPIO_AF_Remap_SWJ_NONJTRST();
		#endif
	#endif
}

#endif 