#include "usb_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�USBʱ������
//////�������:
//////�������: 
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USB_Clock(void)
{
	//---����USBʱ��
	#if (HSE_VALUE==4000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_2, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==6000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_3, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==8000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_4, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==12000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_6, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==16000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==20000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_10, 168, LL_RCC_PLLQ_DIV_7);
	#elif (HSE_VALUE==24000000UL)
		LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 168, LL_RCC_PLLQ_DIV_7);
	#else
		#error "�ⲿ�������óɴ���ֻ֧��4M,6M,8M,12M,16M,20M,24M������!"
	#endif
}