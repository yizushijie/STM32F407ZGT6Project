#include "w25qxx_cfg.h"

//===ȫ�ֱ����Ķ���
W25QXX_HandleType  g_W25qxxDevice0 = { 0 };
pW25QXX_HandleType pW25qxxDevice0 = &g_W25qxxDevice0;

//===ͳһ���ͺ���
UINT8_T(*W25QXX_SEND_CMD)(W25QXX_HandleType *, UINT8_T, UINT8_T *);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device0_Init(W25QXX_HandleType *W25Qx)
{
	//---д�����˿ڵ�����
#ifdef WM25QXX_SPI_USE_HWWP
	W25Qx->msgWP.msgPort = GPIOC;
	W25Qx->msgWP.msgBit = LL_GPIO_PIN_4;
#endif

	//---SPI1�ӿ�
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI

	//---SPI1�ӿ�
	//---PB14------ > SPI1_NSS
	//---PB3------ > SPI1_SCK
	//---PB4------ > SPI1_MISO
	//---PB5------ > SPI1_MOSI

	//---SPI2�ӿ�
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	W25Qx->msgSPI.msgCS.msgPort = GPIOB;//GPIOA;
	W25Qx->msgSPI.msgCS.msgBit  = LL_GPIO_PIN_14;//LL_GPIO_PIN_4;
	//---SCK
	W25Qx->msgSPI.msgSCK.msgPort = GPIOB;// GPIOA;
	W25Qx->msgSPI.msgSCK.msgBit = LL_GPIO_PIN_3; //LL_GPIO_PIN_5;
	//---MISO  
	W25Qx->msgSPI.msgMISO.msgPort = GPIOB;//GPIOA;
	W25Qx->msgSPI.msgMISO.msgBit = LL_GPIO_PIN_4;//LL_GPIO_PIN_6;
	//---MOSI
	W25Qx->msgSPI.msgMOSI.msgPort = GPIOB; //GPIOA;
	W25Qx->msgSPI.msgMOSI.msgBit = LL_GPIO_PIN_5; //LL_GPIO_PIN_7;
	//---����ģʽ
#ifndef USE_MCU_STM32F1
	W25Qx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
#endif
	//---SPI���
	W25Qx->msgSPI.pMsgSPIx = SPI1;
#ifndef USE_MCU_STM32F1
	//---SPI��Э��
	W25Qx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
#endif
	//---����������
	W25Qx->msgSPI.msgPluseWidth = 0;
	//---ʱ�ӿ���Ϊ�͵�ƽ
	W25Qx->msgSPI.msgCPOL = 0;
	//---���ݲ����ڵ�һ��ʱ�ӱ���
	W25Qx->msgSPI.msgCPOH = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device1_Init(W25QXX_HandleType *W25Qx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device2_Init(W25QXX_HandleType *W25Qx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_HW_Init(W25QXX_HandleType *W25Qx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(W25Qx->msgSPI),1);
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(W25Qx->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct = { 0 };
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;														//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;												//---8λ����
	//---ʱ�ӿ���ʱ�ļ���
	if (W25Qx->msgSPI.msgCPOL == 0)
	{
		//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;				
		GPIO_OUT_0(W25Qx->msgSPI.msgSCK.msgPort, W25Qx->msgSPI.msgSCK.msgBit);
	}
	else
	{
		//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;				
	}
	//---���ݲ�����ʱ�ӱ���λ��
	if (W25Qx->msgSPI.msgCPOL == 0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}	
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;															//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV4;										//---ϵͳʱ��256��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;														//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;									//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(W25Qx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_Init(W25QXX_HandleType *W25Qx)
{
	SPITask_DeInit(&(W25Qx->msgSPI),1);
	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(W25Qx->msgSPI));
	//---ʱ�ӿ���ʱ�ļ���
	(W25Qx->msgSPI.msgCPOL == 0)?(GPIO_OUT_0(W25Qx->msgSPI.msgSCK.msgPort, W25Qx->msgSPI.msgSCK.msgBit)):(GPIO_OUT_1(W25Qx->msgSPI.msgSCK.msgPort, W25Qx->msgSPI.msgSCK.msgBit));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_HW_SendCmd(W25QXX_HandleType *W25Qx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadByte(&(W25Qx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_SendCmd(W25QXX_HandleType *W25Qx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadByteMSB(&(W25Qx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Init(W25QXX_HandleType *W25Qx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_ONE))
	{
		W25QXX_SPI_Device0_Init(W25Qx);
	}
	else if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_TWO))
	{
		W25QXX_SPI_Device1_Init(W25Qx);
	}
	else if ((W25Qx != NULL) && (W25Qx == W25QXX_TASK_THREE))
	{
		W25QXX_SPI_Device2_Init(W25Qx);
	}
	else
	{
		return ERROR_1;
	}
	//---�жϳ�ʼ���ķ�ʽ
	if (isHW != 0)
	{
		W25Qx->msgSPI.msgHwMode = 1;
		W25QXX_SPI_HW_Init(W25Qx);
		//---�����д
		W25QXX_SEND_CMD = W25QXX_SPI_HW_SendCmd;
	}
	else
	{
		W25Qx->msgSPI.msgHwMode = 0;
		W25QXX_SPI_SW_Init(W25Qx);
		//---�����д
		W25QXX_SEND_CMD = W25QXX_SPI_SW_SendCmd;
	}
	//---ע��ms��ʱʱ��
	(pFuncDelayms != NULL)?(W25Qx->pMsgDelayms = pFuncDelayms):(W25Qx->pMsgDelayms = DelayTask_ms);
	//---ע��us��ʱ����
	(pFuncDelayus != NULL)?(W25Qx->msgSPI.pMsgDelayus = pFuncDelayus):(W25Qx->msgSPI.pMsgDelayus = DelayTask_us);
	//---ע��δ���
	(pFuncTimerTick != NULL)?(W25Qx->msgSPI.pMsgTimeTick = pFuncTimerTick):(W25Qx->msgSPI.pMsgTimeTick = SysTickTask_GetTick);
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		//---ʹ��GPIO��ʱ��
		#ifndef  USE_FULL_GPIO
		GPIOTask_Clock(W25Qx->msgWP.msgPort, PERIPHERAL_CLOCK_ENABLE);
		#endif
		//---GPIO�Ľṹ��
		LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;													//---����״̬Ϊ���ģʽ
		GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;											//---GPIO���ٶ�---�����豸
		GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;										//---���ģʽ---�������
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;														//---����
#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;													//---�˿ڸ���ģʽ
#endif
		//---WPs_BIT�ĳ�ʼ��
		GPIO_InitStruct.Pin = W25Qx->msgWP.msgBit;
		LL_GPIO_Init(W25Qx->msgWP.msgPort, &GPIO_InitStruct);
		GPIO_OUT_0(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ���ʼ��������ͬһ��SPI�˿ڹ��ض���豸���ٶȲ�һ�µ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_AutoInit(W25QXX_HandleType* W25Qx)
{
	if (W25Qx->msgSPI.msgHwMode != 0)
	{
		//---�����ʼ��
		W25QXX_SPI_HW_Init(W25Qx);
	}
	else
	{
		//---Ӳ����ʼ��
		W25QXX_SPI_SW_Init(W25Qx);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ�ע��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_AutoDeInit(W25QXX_HandleType* W25Qx)
{
	//---ע����ǰ����������
	return	SPITask_DeInit(&(W25Qx->msgSPI),0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ״̬�Ĵ���1
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR1(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_REG_SR1, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &_return);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ״̬�Ĵ���2
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR2(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_REG_SR2, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &_return);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д��״̬�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR1(W25QXX_HandleType *W25Qx, UINT8_T cmd, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_WRITE_REG_SR, NULL);
	W25QXX_SEND_CMD(W25Qx, cmd, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д��״̬�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR2(W25QXX_HandleType *W25Qx, UINT8_T cmd, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---��ȡSR1��ֵ
	_return =  W25QXX_SPI_ReadRegSR1(W25Qx,0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_WRITE_REG_SR, NULL);
	//---дSR1
	W25QXX_SEND_CMD(W25Qx, _return, NULL);
	//---дSR2
	W25QXX_SEND_CMD(W25Qx, cmd, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дʹ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableWrite(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ENABLE_WRITE, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дʹ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_DisableWrite(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_DISABLE_WRITE, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�  ��ȡоƬID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T W25QXX_SPI_ReadID(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	UINT8_T temp = 0;
	UINT16_T  _return = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_MANUFACT_DEVICE_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	//---��ȡ�豸��ID��Ϣ��λֵ
	W25QXX_SEND_CMD(W25Qx, 0xFF, &temp);
	_return = temp;
	//---��ȡ�豸��ID��Ϣ��λֵ
	W25QXX_SEND_CMD(W25Qx, 0xFF, &temp);	
	_return = (_return << 8) + temp;
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);	
	W25Qx->msgChipID = _return;
	switch (W25Qx->msgChipID)
	{
		case 0xEF13:
			//---W25Q80---1MByte
			W25Qx->msgEraseDelayMS = 25000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF14:
			//---W25Q16---2Mbyte
			W25Qx->msgEraseDelayMS = 40000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF15:
			//---W25Q32---4Mbyte
			W25Qx->msgEraseDelayMS = 80000;
			W25Qx->msgEraseSectorDelayMS = 200;
			W25Qx->msgErase32KbBlockDelayMS = 1000;
			W25Qx->msgErase64KbBlockDelayMS = 1500;
			break;
		case 0xEF16:
			//---W25Q64---8Mbyte
			W25Qx->msgEraseDelayMS = 30000;
			W25Qx->msgEraseSectorDelayMS = 400;
			W25Qx->msgErase32KbBlockDelayMS = 800;
			W25Qx->msgErase64KbBlockDelayMS = 1000;
			break;
		default:
			break;
	}
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_WaitBusy(W25QXX_HandleType *W25Qx,UINT32_T timeOut, UINT8_T isAutoInit)
{
	//---��ȡ״̬�Ĵ���
	UINT8_T _return = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	_return=W25QXX_SPI_ReadRegSR1(W25Qx,0);
	//---��ȡʱ���ǩ
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime =((W25Qx->msgSPI.pMsgTimeTick != NULL)? W25Qx->msgSPI.pMsgTimeTick():0);
	//---�ȴ�BUSYλ���
	while ((_return & 0x01) == 0x01)
	{
		_return = W25QXX_SPI_ReadRegSR1(W25Qx,0);
		if (W25Qx->msgSPI.pMsgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = W25Qx->msgSPI.pMsgTimeTick();
			//---�жϵδ�ʱ�Ƿ����������
			if (nowTime < oldTime)
			{
				cnt = (0xFFFFFFFF - oldTime + nowTime);
			}
			else
			{
				cnt = nowTime - oldTime;
			}
			//---�ж��Ƿ�ʱ
			if (cnt > timeOut)
			{
				//---���ͷ�����ʱ����
				return ERROR_1;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > timeOut*100000)
			{
				//---���ͷ�����ʱ����
				return ERROR_2;
			}
		}
	}
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadData(W25QXX_HandleType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT16_T i = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_DATA, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr), NULL);
	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}
	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadFast(W25QXX_HandleType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT16_T i = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_FAST, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(addr), NULL);
	//---����α�ֽ�
	W25QXX_SEND_CMD(W25Qx, 0xFF, NULL);
	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}
	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дҳ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WritePage(W25QXX_HandleType *W25Qx, UINT32_T addr, UINT8_T *pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT8_T pageIndex = 0;
	UINT16_T i = 0;
	UINT32_T pageAdddr = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---�ж�Ҳ���ݵĸ����������256���ֽ�
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}
	//---У��ҳ��ַ
	pageAdddr = (addr & W25QXX_PAGE_NUM_MASK);
	//---У��ҳ���
	pageIndex = (UINT8_T)(addr & W25QXX_PAGE_BYTE_MASK);
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
	//----����дҳ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_PAGE_PROGRAM, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(pageAdddr), NULL);
	//---ѭ��д������
	for (i = pageIndex; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, pVal[i - pageIndex], NULL);
	}
	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ�д�����
	W25QXX_SPI_WaitBusy(W25Qx,100, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	//---ʹ��д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��������оƬ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseChip(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx,100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ƭ��������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_CHIP, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);	
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx,W25Qx->msgEraseDelayMS, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSuspend(W25QXX_HandleType* W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx,0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx, 100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ƭ��������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SUSPEND, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx, 100, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �����ָ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseResume(W25QXX_HandleType* W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx, 100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ƭ��������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_RESUME, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx, 100, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����ָ������
//////�������: sectorNum---��������ţ�����0��511����ͬ���������ĸ�����ͬ
//////�������:
//////˵		���������ĵ�ַ��0��511����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSector(W25QXX_HandleType *W25Qx, UINT32_T sectorNum, UINT8_T isAutoInit)
{
	//---����������ַ
	sectorNum *= W25QXX_SECTOR_BYTE_SIZE;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx,100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SECTOR, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(sectorNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgEraseSectorDelayMS, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����ָ������
//////�������: sectorNum---��������ţ�����0��511����ͬ���������ĸ�����ͬ
//////�������:
//////˵		���������ĵ�ַ��0��511����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrSector(W25QXX_HandleType* W25Qx, UINT32_T sectorAddr, UINT8_T isAutoInit)
{
	//---�����������
	sectorAddr /= W25QXX_SECTOR_BYTE_SIZE;
	W25QXX_SPI_EraseSector(W25Qx, sectorAddr,isAutoInit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������飬32KB
//////�������: block32KbNum---���������ţ�����0��63
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock32KB(W25QXX_HandleType *W25Qx, UINT32_T block32KbNum, UINT8_T isAutoInit)
{
	//---����32Kb��С��ĵ�ַ
	block32KbNum *= W25QXX_BLOCK_32KB_BYTE_SIZE;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx,100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_BLOCK_32KB, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(block32KbNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgErase32KbBlockDelayMS, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������飬32KB
//////�������: block32KbNum---���������ţ�����0��63
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrBlock32KB(W25QXX_HandleType* W25Qx, UINT32_T block32KbAddr, UINT8_T isAutoInit)
{
	//---����32Kb��С������
	block32KbAddr /= W25QXX_BLOCK_32KB_BYTE_SIZE;
	W25QXX_SPI_EraseBlock32KB(W25Qx, block32KbAddr,isAutoInit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������飬64KB
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock64KB(W25QXX_HandleType *W25Qx, UINT32_T blockNum, UINT8_T isAutoInit)
{
	//---����64Kb��С��ĵ�ַ
	blockNum *= W25QXX_BLOCK_64KB_BYTE_SIZE;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx, 0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx,100, 0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_BLOCK_64KB, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(blockNum), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx, W25Qx->msgErase64KbBlockDelayMS, 0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������飬64KB
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseAddrBlock64KB(W25QXX_HandleType* W25Qx, UINT32_T blockAddr, UINT8_T isAutoInit)
{
	//---����64Kb��С������
	blockAddr /= W25QXX_BLOCK_64KB_BYTE_SIZE;
	W25QXX_SPI_EraseBlock64KB( W25Qx, blockAddr,isAutoInit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_PowerDown(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);	
	//---���͵�������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_POWER_DOWN, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---TDP
	W25Qx->msgSPI.pMsgDelayus(3);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WakeUp(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---���ͻ�������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_RELEASE_POWER_DOWN, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---TRES1
	W25Qx->msgSPI.pMsgDelayus(3);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���к�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadUniqueIDNumber(W25QXX_HandleType *W25Qx, UINT8_T *pVal, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---׼����ȡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_UNIQUE_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	W25QXX_SEND_CMD(W25Qx, 0x00, NULL);
	//---��ȡ64Bit��UniqueSerialNumber
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[2]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[3]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[4]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[5]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[6]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[7]);
	//---������ȡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadJEDECID(W25QXX_HandleType *W25Qx, UINT8_T *pVal, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_JEDEC_ID, NULL);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[2]);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ܼĴ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSecurityReg(W25QXX_HandleType *W25Qx, UINT32_T regAddr, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx,0);
	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25Qx,100,0);
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ERASE_SECURITY_REG, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25Qx,100,0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼��ܼĴ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ProgramSecurityReg(W25QXX_HandleType *W25Qx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT16_T i = 0;

	//---�ж�Ҳ���ݵĸ����������256���ֽ�
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---����WEL
	W25QXX_SPI_EnableWrite(W25Qx,0);
	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
	//----����дҳ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_PROGRAM_SECURITY_REG, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);
	//---ѭ��д������
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, pVal[i], NULL);
	}
	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---�ȴ�д�����
	W25QXX_SPI_WaitBusy(W25Qx,100,0);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
	//---ʹ��д����
#ifdef WM25QXX_SPI_USE_HWWP
	if (W25Qx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(W25Qx->msgWP.msgPort, W25Qx->msgWP.msgBit);
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���ܼĴ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadSecurityReg(W25QXX_HandleType *W25Qx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT16_T i = 0;
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_READ_SECURITY_REG, NULL);
	//----����24bit��ַ
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25Qx, (UINT8_T)(regAddr), NULL);
	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25Qx, 0xFF, &pVal[i]);
	}
	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableReset(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����ʹ�ܸ�λ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_ENABLE_RESET, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_Reset(W25QXX_HandleType *W25Qx, UINT8_T isAutoInit)
{
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	GPIO_OUT_0(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����ʦ���ܹ���λ����
	W25QXX_SEND_CMD(W25Qx, W25QXX_CMD_RESET, NULL);
	GPIO_OUT_1(W25Qx->msgSPI.msgCS.msgPort, W25Qx->msgSPI.msgCS.msgBit);
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ֻд�벻У�������Ƿ����д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteNoCheck(W25QXX_HandleType *W25Qx, UINT32_T addr, UINT8_T* pVal, UINT16_T length, UINT8_T isAutoInit)
{
	//---����ҳ���ֽ���
	UINT16_T byteNum = W25QXX_PAGE_BYTE_SIZE - (UINT8_T)(addr&W25QXX_PAGE_BYTE_MASK);
	if (length <= byteNum)
	{
		//---������256���ֽ�
		byteNum = length;
	}
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---ѭ��д������
	while (1)
	{
		W25QXX_SPI_WritePage(W25Qx, addr, pVal, byteNum,0);
		if (length == byteNum)
		{
			//---д�������
			break;
		}
		else
		{
			pVal += byteNum;
			addr += byteNum;

			//---��ȥ�Ѿ�д���˵��ֽ���
			length -= byteNum;
			if (length > W25QXX_PAGE_BYTE_SIZE)
			{
				//---һ�ο���д��256���ֽ�
				byteNum = W25QXX_PAGE_BYTE_SIZE;
			}
			else
			{
				//---����256���ֽ���
				byteNum = length;
			}
		}
	};
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteAndCheck(W25QXX_HandleType *W25Qx, UINT32_T addr, UINT8_T* pVal, UINT16_T length, UINT8_T isAutoInit)
{
	UINT32_T sectorAddr = 0;
	UINT16_T sectorOffset = 0;
	UINT16_T sectorRemainSize = 0;
	UINT16_T i = 0;
	//---������ַ
	sectorAddr = addr & W25QXX_SECTOR_NUM_MASK;
	//---�������ڵ�ƫ��
	sectorOffset = addr & W25QXX_SECTOR_BYTE_MASK;
	//---����ʣ��ռ��С
	sectorRemainSize = W25QXX_SECTOR_BYTE_SIZE - sectorOffset;
	if (length <= sectorRemainSize)
	{
		//---������4096���ֽ�
		sectorRemainSize = length;
	}
	//---����Ӧ�����Ӳ��ʱ��ʼ
	if (isAutoInit)
	{
		W25QXX_SPI_AutoInit(W25Qx);
	}
	//---ѭ��д������
	while (1)
	{
		//---������������������
		W25QXX_SPI_ReadData(W25Qx, sectorAddr , W25Qx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE,0);
		//---У������
		for (i = 0; i < sectorRemainSize; i++)
		{
			if (W25Qx->msgBuffer[sectorOffset + i] != 0XFF)
			{
				//---��Ҫ����
				break;
			}
		}
		//---�ж��Ƿ���Ҫ����
		if (i < sectorRemainSize)
		{
			//---�����������
			W25QXX_SPI_EraseAddrSector(W25Qx, sectorAddr,0);
			//---����
			for (i = 0; i < sectorRemainSize; i++)
			{
				W25Qx->msgBuffer[i + sectorOffset] = pVal[i];
			}
			//---д����������
			W25QXX_SPI_WriteNoCheck(W25Qx, sectorAddr, W25Qx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE,0);
		}
		else
		{
			//---д�Ѿ������˵�,ֱ��д������ʣ������.
			W25QXX_SPI_WriteNoCheck(W25Qx, addr, pVal, sectorRemainSize,0);
		}
		//---�ж��Ƿ�д�����
		if (length == sectorRemainSize)
		{
			//---д�������
			break;
		}
		else
		{
			//---д��δ����
			//---������ַƫ��
			sectorAddr+= W25QXX_SECTOR_BYTE_SIZE;
			//---ƫ��λ��Ϊ0
			sectorOffset = 0;
			//---ָ��ƫ��
			pVal += sectorRemainSize;
			//---д��ַƫ��
			addr += sectorRemainSize;
			//---�ֽ����ݼ�
			length -= sectorRemainSize;
			//---�ж���һ�������Ƿ��ܹ�д��
			if (length >= W25QXX_SECTOR_BYTE_SIZE)
			{
				//---��һ����������д����
				sectorRemainSize = W25QXX_SECTOR_BYTE_SIZE;
			}
			else
			{
				//---��һ����������д����
				sectorRemainSize = length;
			}
		}
	};
	//---����Ӧ�����Ӳ��ʱ�����
	if (isAutoInit)
	{
		W25QXX_SPI_AutoDeInit(W25Qx);
	}
}
