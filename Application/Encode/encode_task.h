#ifndef ENCODE_TASK_H_
#define ENCODE_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"encode_lib.h"
	#include "uart_task.h"
	#include "at24cxx_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===���ò����ı���
	#define ENCODE_GEN_CHANNEL_MASK1_ADDR_X1						0x70
	#define ENCODE_GEN_CHANNEL_MASK2_ADDR_X1						( ENCODE_GEN_CHANNEL_MASK1_ADDR_X1+0x01 )

	#define ENCODE_GEN_CHANNEL_MASK1_ADDR_X2						( ENCODE_GEN_CHANNEL_MASK1_ADDR_X1+0x02 )
	#define ENCODE_GEN_CHANNEL_MASK2_ADDR_X2						( ENCODE_GEN_CHANNEL_MASK1_ADDR_X1+0x03 )

	#define ENCODE_GEN_CHANNEL_MASK1_ADDR_X3						( ENCODE_GEN_CHANNEL_MASK1_ADDR_X1+0x04 )
	#define ENCODE_GEN_CHANNEL_MASK2_ADDR_X3						( ENCODE_GEN_CHANNEL_MASK1_ADDR_X1+0x05 )
	
	//===��������
	void EncodeTask_Init( void );
	void EnCodeTask_IRQTask( void );
	void EnCodeTask_SetChannel(UINT8_T chIndex, UINT8_T isEnCode, UINT8_T isHigh);
	UINT8_T EnCodeTask_UART_MenuTask(UART_HandleType* UARTx);
	UINT8_T EnCodeTask_EepromInit(void);
	UINT8_T EnCodeTask_EepromWrite(void);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ENCODE_TASK_H_ */