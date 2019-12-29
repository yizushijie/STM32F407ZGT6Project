#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===ʹ�ð�����ͷ�ļ�
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////
	//////////////λ������,ʵ��51���Ƶ�GPIO���ƹ���////////////////////////////////////////
	//////////////����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).///////////////////////
	//////////////IO�ڲ����궨��/////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	#define BIT_BAND(addr, bitIndex)	((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitIndex<<2)) 
	#define MEM_ADDR(addr)				*((volatile unsigned long  *)(addr)) 
	#define BIT_ADDR(addr, bitIndex)	MEM_ADDR(BIT_BAND(addr, bitIndex)) 
	
	#ifdef USE_MCU_STM32F1
		//====IO�����ƫ��
		#define	GPIO_ODR_OFFSET				0x0C
		//====IO�����ƫ��
		#define	GPIO_IDR_OFFSET				0x08
	#elif defined (USE_MCU_STM32F4)
		//====IO�����ƫ��
		#define	GPIO_ODR_OFFSET				0x14
		//====IO�����ƫ��
		#define	GPIO_IDR_OFFSET				0x10
	#else
		#error "IO�˿ڵ������������ַƫ�����ô���"
	#endif

	//===IO�������ַӳ��
	#define GPIOA_ODR_ADDR				(GPIOA_BASE+GPIO_ODR_OFFSET) //0x4001080C 
	#define GPIOB_ODR_ADDR				(GPIOB_BASE+GPIO_ODR_OFFSET) //0x40010C0C 
	#define GPIOC_ODR_ADDR				(GPIOC_BASE+GPIO_ODR_OFFSET) //0x4001100C 
	#define GPIOD_ODR_ADDR			    (GPIOD_BASE+GPIO_ODR_OFFSET) //0x4001140C 
	#define GPIOE_ODR_ADDR			    (GPIOE_BASE+GPIO_ODR_OFFSET) //0x4001180C 
	#define GPIOF_ODR_ADDR			    (GPIOF_BASE+GPIO_ODR_OFFSET) //0x40011A0C    
	#define GPIOG_ODR_ADDR			    (GPIOG_BASE+GPIO_ODR_OFFSET) //0x40011E0C    
	
	//===IO�������ַӳ��
	#define GPIOA_IDR_ADDR			    (GPIOA_BASE+GPIO_IDR_OFFSET) //0x40010808 
	#define GPIOB_IDR_ADDR			    (GPIOB_BASE+GPIO_IDR_OFFSET) //0x40010C08 
	#define GPIOC_IDR_ADDR			    (GPIOC_BASE+GPIO_IDR_OFFSET) //0x40011008 
	#define GPIOD_IDR_ADDR			    (GPIOD_BASE+GPIO_IDR_OFFSET) //0x40011408 
	#define GPIOE_IDR_ADDR			    (GPIOE_BASE+GPIO_IDR_OFFSET) //0x40011808 
	#define GPIOF_IDR_ADDR			    (GPIOF_BASE+GPIO_IDR_OFFSET) //0x40011A08 
	#define GPIOG_IDR_ADDR			    (GPIOG_BASE+GPIO_IDR_OFFSET) //0x40011E08 
	
	//===IO�ڲ���,ֻ�Ե�һ��IO��!
	#ifdef GPIOA
		//===���
		#define PA_OUT(n)				BIT_ADDR(GPIOA_ODR_ADDR,n)
		//===����
		#define PA_PIN(n)				BIT_ADDR(GPIOA_IDR_ADDR,n)  
	#endif
	
	#ifdef GPIOB
		//===���
		#define PB_OUT(n)				BIT_ADDR(GPIOB_ODR_ADDR,n)
		//===����
		#define PB_PIN(n)				BIT_ADDR(GPIOB_IDR_ADDR,n)  
	#endif
	
	#ifdef GPIOC
		//===���
		#define PC_OUT(n)				BIT_ADDR(GPIOC_ODR_ADDR,n)
		//===����
		#define PC_PIN(n)				BIT_ADDR(GPIOC_IDR_ADDR,n)  
	#endif

	#ifdef GPIOD
		//===���
		#define PD_OUT(n)				BIT_ADDR(GPIOD_ODR_ADDR,n)
		//===����
		#define PD_PIN(n)				BIT_ADDR(GPIOD_IDR_ADDR,n)  
	#endif

	#ifdef GPIOE
		//===���
		#define PE_OUT(n)				BIT_ADDR(GPIOE_ODR_ADDR,n)
		//===����
		#define PE_PIN(n)				BIT_ADDR(GPIOE_IDR_ADDR,n)  
	#endif

	#ifdef GPIOF
		//===���
		#define PF_OUT(n)				BIT_ADDR(GPIOF_ODR_ADDR,n)
		//===����
		#define PF_PIN(n)				BIT_ADDR(GPIOF_IDR_ADDR,n)  
	#endif

	#ifdef GPIOG
		//===���
		#define PG_OUT(n)				BIT_ADDR(GPIOG_ODR_ADDR,n)
		//===����
		#define PG_PIN(n)				BIT_ADDR(GPIOG_IDR_ADDR,n)  
	#endif

	#ifdef GPIOH
		//===���
		#define PH_OUT(n)				BIT_ADDR(GPIOH_ODR_Addr,n)
		//===����
		#define PH_PIN(n)				BIT_ADDR(GPIOH_IDR_Addr,n)  
	#endif
	
	/////////////////////////////////////////////////////////////////////////////////////
	//===���ö˿�Ϊ���ģʽ
	#define GPIO_SET_WRITE(	name, index )			LL_GPIO_SetPinMode(	name, index,LL_GPIO_MODE_OUTPUT)	
	//===���ö˿�Ϊ����ģʽ
	#define GPIO_SET_READ(	name, index )			LL_GPIO_SetPinMode(	name, index,LL_GPIO_MODE_INPUT)	
	//===���ö˿������
	#define GPIO_OUT_1(	name, index )				LL_GPIO_SetOutputPin(  name, index )	
	//===���ö˿������
	#define GPIO_OUT_0(	name, index )				LL_GPIO_ResetOutputPin( name, index )	
	//===���ö˿����ȡ��
	#define GPIO_OUT_C(	name, index )				LL_GPIO_TogglePin(	name, index )	
	//===��ȡ�˿ڵ�����״̬
	#define GPIO_GET_STATE(	name, index )			LL_GPIO_IsInputPinSet(	name, index )	
	//===GPIO�Ͱ�λ������
	#define GPIO_L8BITS_OUT( name, val	)			( name->ODR=(name->ODR&0xFF00)| (val&0x00FF) )	
	//===GPIO�߰�λ������
	#define GPIO_H8BITS_OUT( name, val	)			( name->ODR=(name->ODR&0x00FF)| ((val<<8)&0xFF00) )	
	//===GPIO16λ������
	#define GPIO_16BITS_OUT( name, val	)			( name->ODR=(val&0xFFFF) )
	
	//===����ṹ��
	typedef struct _GPIO_HandlerType				GPIO_HandlerType;
	//===����ָ��ṹ��
	typedef	struct _GPIO_HandlerType				*pGPIO_HandlerType;
	//===�ṹ����
	struct _GPIO_HandlerType
	{
		GPIO_TypeDef	*msgGPIOPort;																//---�˿�
		UINT32_T		msgGPIOBit;																	//---���
	};

	//===��������
	void GPIO_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable);
	void GPIO_Init(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* GPIO_CFG_H_ */