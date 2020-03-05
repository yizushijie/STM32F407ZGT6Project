#ifndef DATA_BUS_H_
#define DATA_BUS_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===使用的数据总线
	#define DATA_BUS_PORT					GPIOD
	#define DATA_BUS_BIT					( LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7 )
	#define DATA_BUS_STATE					GPIO_GET_STATE(DATA_BUS_PORT,DATA_BUS_BIT)
	#define DATA_BUS_WRITE					GPIO_SET_WRITE(DATA_BUS_PORT,DATA_BUS_BIT)
	#define DATA_BUS_READ					GPIO_SET_READ( DATA_BUS_PORT,DATA_BUS_BIT)
	#define DATA_BUS_VAL(val)				GPIO_L8BITS_OUT(DATA_BUS_PORT,val)	

	//===数据总线方向控制端
	#define DATA_BUS_DIR_PORT				GPIOE
	#define DATA_BUS_DIR_BIT				LL_GPIO_PIN_1
	#define DATA_BUS_DIR_STATE				GPIO_GET_STATE(DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)
	#define DATA_BUS_DIR_WRITE				GPIO_SET_WRITE(DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)
	#define DATA_BUS_DIR_READ				GPIO_SET_READ( DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)
	#define DATA_BUS_DIR_OUT_0				GPIO_OUT_0(    DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)
	#define DATA_BUS_DIR_OUT_1				GPIO_OUT_1(    DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)
	#define DATA_BUS_DIR_OUT_C				GPIO_OUT_C(    DATA_BUS_DIR_PORT,DATA_BUS_DIR_BIT)

	//===数据总线使能控制端
	#define DATA_BUS_OE_PORT				GPIOE
	#define DATA_BUS_OE_BIT					LL_GPIO_PIN_2
	#define DATA_BUS_OE_STATE				GPIO_GET_STATE(DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)
	#define DATA_BUS_OE_WRITE				GPIO_SET_WRITE(DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)
	#define DATA_BUS_OE_READ				GPIO_SET_READ( DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)
	#define DATA_BUS_OE_OUT_0				GPIO_OUT_0(    DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)
	#define DATA_BUS_OE_OUT_1				GPIO_OUT_1(    DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)
	#define DATA_BUS_OE_OUT_C				GPIO_OUT_C(    DATA_BUS_OE_PORT,DATA_BUS_OE_BIT)

	//===数据流向
	#define DATA_BUS_TO_DEVICE				( DATA_BUS_DIR_OUT_1,DATA_BUS_OE_OUT_0 )
	#define DATA_BUS_TO_HOST				( DATA_BUS_DIR_OUT_0,DATA_BUS_OE_OUT_0 )
	#define DATA_BUS_TO_HZ					DATA_BUS_OE_OUT_1

	//===TRG的脉冲触发
	#define TRIG_PULSE_PORT					GPIOD
	#define TRIG_PULSE_BIT					LL_GPIO_PIN_11
	#define TRIG_PULSE_STATE				GPIO_GET_STATE(TRIG_PULSE_PORT,TRIG_PULSE_BIT)
	#define TRIG_PULSE_WRITE				GPIO_SET_WRITE(TRIG_PULSE_PORT,TRIG_PULSE_BIT)
	#define TRIG_PULSE_READ					GPIO_SET_READ( TRIG_PULSE_PORT,TRIG_PULSE_BIT)
	#define TRIG_PULSE_OUT_0				GPIO_OUT_0(    TRIG_PULSE_PORT,TRIG_PULSE_BIT)
	#define TRIG_PULSE_OUT_1				GPIO_OUT_1(    TRIG_PULSE_PORT,TRIG_PULSE_BIT)
	#define TRIG_PULSE_OUT_C				GPIO_OUT_C(    TRIG_PULSE_PORT,TRIG_PULSE_BIT)

	//===TRG的脉冲使能
	#define TRIG_OE_PORT					GPIOD
	#define TRIG_OE_BIT						LL_GPIO_PIN_15
	#define TRIG_OE_STATE					GPIO_GET_STATE(TRIG_OE_PORT,TRIG_OE_BIT)
	#define TRIG_OE_WRITE					GPIO_SET_WRITE(TRIG_OE_PORT,TRIG_OE_BIT)
	#define TRIG_OE_READ					GPIO_SET_READ( TRIG_OE_PORT,TRIG_OE_BIT)
	#define TRIG_OE_OUT_0					GPIO_OUT_0(    TRIG_OE_PORT,TRIG_OE_BIT)
	#define TRIG_OE_OUT_1					GPIO_OUT_1(    TRIG_OE_PORT,TRIG_OE_BIT)
	#define TRIG_OE_OUT_C					GPIO_OUT_C(    TRIG_OE_PORT,TRIG_OE_BIT)

	//===函数定义
	void DataBus_Init(void);
	UINT8_T DataBus_Read(void);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DATA_BUS_H_ */