#ifndef HW_CFG_H_
#define HW_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===RESET�ĸ�ѹ���ƶ�H�˿�
	#define RST_HEN_PORT						GPIOB
	#define RST_HEN_BIT							LL_GPIO_PIN_2
	#define RST_HEN_STATE						GPIO_GET_STATE(RST_HEN_PORT,RST_HEN_BIT)
	#define RST_HEN_WRITE						GPIO_SET_WRITE(RST_HEN_PORT,RST_HEN_BIT)
	#define RST_HEN_READ						GPIO_SET_READ( RST_HEN_PORT,RST_HEN_BIT)
	#define RST_HEN_OUT_0						GPIO_OUT_0(    RST_HEN_PORT,RST_HEN_BIT)
	#define RST_HEN_OUT_1						GPIO_OUT_1(    RST_HEN_PORT,RST_HEN_BIT)
	#define RST_HEN_OUT_C						GPIO_OUT_C(    RST_HEN_PORT,RST_HEN_BIT)
	//===RESET�ĸ�ѹ���ƶ�L�˿�
	#define RST_LEN_PORT						GPIOB
	#define RST_LEN_BIT							LL_GPIO_PIN_1
	#define RST_LEN_STATE						GPIO_GET_STATE(RST_LEN_PORT,RST_LEN_BIT)
	#define RST_LEN_WRITE						GPIO_SET_WRITE(RST_LEN_PORT,RST_LEN_BIT)
	#define RST_LEN_READ						GPIO_SET_READ( RST_LEN_PORT,RST_LEN_BIT)
	#define RST_LEN_OUT_0						GPIO_OUT_0(    RST_LEN_PORT,RST_LEN_BIT)
	#define RST_LEN_OUT_1						GPIO_OUT_1(    RST_LEN_PORT,RST_LEN_BIT)
	#define RST_LEN_OUT_C						GPIO_OUT_C(    RST_LEN_PORT,RST_LEN_BIT)
	//===RESET�ĸ�ѹ���ƶ�V�˿�
	#define RST_NEN_PORT						GPIOB
	#define RST_NEN_BIT							LL_GPIO_PIN_1
	#define RST_NEN_STATE						GPIO_GET_STATE(RST_NEN_PORT,RST_NEN_BIT)
	#define RST_NEN_WRITE						GPIO_SET_WRITE(RST_NEN_PORT,RST_NEN_BIT)
	#define RST_NEN_READ						GPIO_SET_READ( RST_NEN_PORT,RST_NEN_BIT)
	#define RST_NEN_OUT_0						GPIO_OUT_0(    RST_NEN_PORT,RST_NEN_BIT)
	#define RST_NEN_OUT_1						GPIO_OUT_1(    RST_NEN_PORT,RST_NEN_BIT)
	#define RST_NEN_OUT_C						GPIO_OUT_C(    RST_NEN_PORT,RST_NEN_BIT)
	//===RST�ӵ�VCC
	#define RST_TO_VCC							( RST_LEN_OUT_0,RST_HEN_OUT_0,RST_NEN_OUT_1 )
	//===RST�ӵ�GND
	#define RST_TO_GND							( RST_LEN_OUT_0,RST_HEN_OUT_0,RST_NEN_OUT_0,RST_LEN_OUT_1 )
	//===RST�ӵ�12V
	#define RST_TO_12V							( RST_LEN_OUT_0,RST_HEN_OUT_0,RST_NEN_OUT_0,RST_HEN_OUT_1 )
	//===RST���ڸ���̬	
	#define RST_TO_HZ							( RST_LEN_OUT_0,RST_HEN_OUT_0,RST_NEN_OUT_0 )

	//===��������
	void HardWare_Init();

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HW_CFG_H_ */