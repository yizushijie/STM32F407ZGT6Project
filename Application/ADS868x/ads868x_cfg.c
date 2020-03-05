#include "ADS868X_cfg.h"

//===ȫ�ֱ�������
ADS868X_HandleType   g_ADS868XDevice0 = { 0 };
pADS868X_HandleType  pADS868XDevice0 = &g_ADS868XDevice0;

//===ͳһ�����ֽ�����
UINT8_T(*ADS868X_SPI_SEND_CMD)(ADS868X_HandleType *, UINT8_T, UINT8_T *);
//===ͳһ������������
UINT8_T(*ADS868X_SPI_SEND_ARRAY)(ADS868X_HandleType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device0_Init(ADS868X_HandleType *ADS868x)
{
	//---��λ�ź�
	ADS868x->msgHWRST.msgPort = NULL;
	ADS868x->msgHWRST.msgBit = LL_GPIO_PIN_0;
	#ifndef  USE_FULL_GPIO
	//---GPIOʱ��ʹ��
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		GPIOTask_Clock(ADS868x->msgHWRST.msgPort, PERIPHERAL_CLOCK_ENABLE);
	}
	#endif
	//---SPI1�ӿ�
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI
	
	//---SPI2�ӿ�
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	ADS868x->msgSPI.msgCS.msgPort = GPIOA;
	ADS868x->msgSPI.msgCS.msgBit = LL_GPIO_PIN_4;
	//---SCK
	ADS868x->msgSPI.msgSCK.msgPort = GPIOA;
	ADS868x->msgSPI.msgSCK.msgBit = LL_GPIO_PIN_5;
	//---MISO  SD0
	ADS868x->msgSPI.msgMISO.msgPort = GPIOA;
	ADS868x->msgSPI.msgMISO.msgBit = LL_GPIO_PIN_6;
	//---MOSI SDI
	ADS868x->msgSPI.msgMOSI.msgPort = GPIOA;
	ADS868x->msgSPI.msgMOSI.msgBit = LL_GPIO_PIN_7;
	//---GPIO������
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;															//---����ʹ��
	//---��ʼ��RST
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS868x->msgHWRST.msgBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS868x->msgHWRST.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
	}
	//---����ģʽ
	#ifndef USE_MCU_STM32F1
		//---�˿ڸ���ģʽ
		ADS868x->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI���
	ADS868x->msgSPI.pMsgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI��Э��
		ADS868x->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif
	UINT8_T i = 0;
	//---�ο���ѹ����
	ADS868x->msgREFPowerUV = ADS868X_REF_POWER_UV;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		ADS868x->msgChannelRange[i] = 0;
		ADS868x->msgPositive[i] = 0;
		ADS868x->msgChannelNowADCResult[i] = 0;
		ADS868x->msgChannelOldADCResult[i] = 0;
		ADS868x->msgChannelPowerResult[i] = 0;
		ADS868X_SPI_ChannelRange(ADS868x, i);
	}
	ADS868x->msgReadyOK = 0;
	ADS868x->msgInitRetryCount = 3;
	ADS868x->msgChipID = 0;
	//---Ĭ����������
	ADS868x->msgFeature = 0x28;
	//---Ĭ����0xFF
	ADS868x->msgAutoSeqEn = 0xFF;
	//---����������
	ADS868x->msgSPI.msgPluseWidth = 2;
	//---ʱ�ӿ���Ϊ�͵�ƽ
	ADS868x->msgSPI.msgCPOL = 0;
	//---���ݲ����ڵڶ���ʱ�ӱ���
	ADS868x->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device1_Init(ADS868X_HandleType *ADS868x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device2_Init(ADS868X_HandleType *ADS868x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendCmd(ADS868X_HandleType *ADS868x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS868x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendArray(ADS868X_HandleType* ADS868x, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---���ݷ���
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS868x->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendCmd(ADS868X_HandleType *ADS868x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS868x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendArray(ADS868X_HandleType* ADS868x, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS868x->msgSPI), pWVal, pRVal,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_Init(ADS868X_HandleType *ADS868x)
{
	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ADS868x->msgSPI));
	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	//---ʱ�Ӽ��Ե�����
	if (ADS868x->msgSPI.msgCPOL == 0)
	{
		//---CLK����ʱΪ�͵�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---���ݲ�����ʱ�ӱ���λ��
	if (ADS868x->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---ϵͳʱ��4��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(ADS868x->msgSPI), SPI_InitStruct);
	//---����ͺ���
	ADS868X_SPI_SEND_CMD = ADS868X_SPI_HW_SendCmd;
	ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_HW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_Init(ADS868X_HandleType *ADS868x)
{
	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ADS868x->msgSPI));
	//---ʱ���ߵļ���
	if (ADS868x->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	//---����ͺ���
	ADS868X_SPI_SEND_CMD = ADS868X_SPI_SW_SendCmd;
	ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_SW_SendArray;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Init(ADS868X_HandleType *ADS868x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_ONE))
	{
		ADS868X_SPI_Device0_Init(ADS868x);
	}
	else if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_TWO))
	{
		ADS868X_SPI_Device1_Init(ADS868x);
	}
	else if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_THREE))
	{
		ADS868X_SPI_Device2_Init(ADS868x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж�Ӳ�����������ʽ
	(isHW != 0) ? (ADS868X_SPI_HW_Init(ADS868x)) : (ADS868X_SPI_SW_Init(ADS868x));
	//---ע��ms��ʱʱ��
	(pFuncDelayms != NULL) ? (ADS868x->pMsgDelayms = pFuncDelayms) : (ADS868x->pMsgDelayms = DelayTask_ms);
	//---ע��us��ʱ����
	(pFuncDelayus != NULL) ? (ADS868x->msgSPI.pMsgDelayus = pFuncDelayus) : (ADS868x->msgSPI.pMsgDelayus = DelayTask_us);
	//---ע��δ���
	(pFuncTimerTick != NULL) ? (ADS868x->msgSPI.pMsgTimeTick = pFuncTimerTick) : (ADS868x->msgSPI.pMsgTimeTick = SysTickTask_GetTick);
	//---����ADS868X
	return ADS868X_SPI_ConfigInit(ADS868x,0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ���ʼ��������ͬһ��SPI�˿ڹ��ض���豸���ٶȲ�һ�µ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AutoInit(ADS868X_HandleType* ADS868x)
{
	if (ADS868x->msgSPI.msgHwMode != 0)
	{
		//---�����ʼ��
		ADS868X_SPI_HW_Init(ADS868x);
	}
	else
	{
		//---Ӳ����ʼ��
		ADS868X_SPI_SW_Init(ADS868x);
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
UINT8_T ADS868X_SPI_AutoDeInit(ADS868X_HandleType* ADS868x)
{
	//---ע����ǰ����������
	return SPITask_DeInit(&(ADS868x->msgSPI),0);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�дADS868X����Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteCommandReg(ADS868X_HandleType *ADS868x, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, NULL, 2);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Registerд����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteProgramReg(ADS868X_HandleType *ADS868x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, NULL, 2);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Program Register������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadProgramReg(ADS868X_HandleType *ADS868x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, rTemp, 3);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}

	//---���ݿ���
	pVal[0] = rTemp[1];
	pVal[1] = rTemp[2];

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadCommandBack(ADS868X_HandleType* ADS868x, UINT8_T* pVal,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_CMD_READ_BACK, pVal);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�����������ѡ�е�״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_NO_OP(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_NO_OP);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_STDBY(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_STDBY);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_PWRDN(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_PWR_DN);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ����λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_HardReset(ADS868X_HandleType *ADS868x)
{
	if (ADS868x->msgHWRST.msgPort!=NULL)
	{
		GPIO_OUT_0(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
		ADS868x->pMsgDelayms(1);
		GPIO_OUT_1(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
		ADS868x->pMsgDelayms(1);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_SoftReset(ADS868X_HandleType *ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_RST);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��豸��λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Reset(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		_return = ADS868X_SPI_HardReset(ADS868x);
	}
	else
	{
		_return = ADS868X_SPI_SoftReset(ADS868x,isAutoInit);
	}
	ADS868x->msgReadyOK = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AUTORST(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_AUTO_RST);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������ֶ�ɨ��ͨ��
//////�������:
//////�������:
//////˵		�����˳���ģʽ��ִ��AUTO_RST����MAN_CH_n�������Ҫ�ȴ�����20us�Ա�֤�������ݵ�ADת��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ManualChannel(ADS868X_HandleType* ADS868x,UINT16_T manualCHCmd,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, manualCHCmd);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ������豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChipID(ADS868X_HandleType* ADS868x, UINT8_T devid,UINT8_T isAutoInit)
{
	devid <<= 6;
	ADS868x->msgChipID = (devid & 0xC0) | ADS868x->msgFeature;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, ADS868x->msgChipID);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChipID(ADS868X_HandleType* ADS868x, UINT8_T *pDevID,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У���豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CheckChipID(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadChipID(ADS868x, &tempChipID,0);
	//---У���ȡ��ID��Ϣ
	if (tempChipID!=ADS868x->msgChipID)
	{
		_return += ERROR_1;
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�̽���豸�Ƿ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_DetectionDevice(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return=ADS868X_SPI_ReadProgramReg(pADS868XDevice0, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---У�����Ƿ���ȷ
	if (tempAutoSeqEn[1]!=ADS868x->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---У���豸��ID��Ϣ
		_return = ADS868X_SPI_CheckChipID(ADS868x,0);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T seq,UINT8_T isAutoInit)
{
	ADS868x->msgAutoSeqEn = seq;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return =ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, seq);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ������ͨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T *pAutoSeqEn,UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 }; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS868x->msgAutoSeqEn)
		{
			*pAutoSeqEn = tempAutoSeqEn[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T ch,UINT8_T isAutoInit)
{
	ADS868x->msgChannelPWRDN = ch;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_CH_PWR_DN, ch);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T *pPWRDN,UINT8_T isAutoInit)
{
	UINT8_T tempPWRDN[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS868x->msgChannelPWRDN)
		{
			*pPWRDN = tempPWRDN[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteFeature(ADS868X_HandleType* ADS868x, UINT8_T feature,UINT8_T isAutoInit)
{
	ADS868x->msgFeature = (feature&0x3F)|ADS868x->msgChipID;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, feature);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������ģʽ��ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadFeature(ADS868X_HandleType* ADS868x, UINT8_T *pFeature,UINT8_T isAutoInit)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS868x->msgFeature)
		{
			*pFeature = tempFeature[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T range,UINT8_T isAutoInit)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ADS868x->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ADS868x->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ADS868x->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ADS868x->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ADS868x->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ADS868x->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ADS868x->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ADS868x->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---ÿ��ͨ�������̵�����
	ADS868X_SPI_ChannelRange(ADS868x, ch);
	//---����ͨ��������
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, chReg, range);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;

}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ͨ�������̷�Χ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ReadChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T *pRange,UINT8_T isAutoInit)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---��ȡͨ��������
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, chReg, tempChannelRange);
	//---�ж϶�ȡ���
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS868x->msgChannelRange[ch])
		{
			*pRange = tempChannelRange[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹuv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerUV(ADS868X_HandleType* ADS868x, UINT32_T refUV)
{
	ADS868x->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ο���ѹ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS868X_SPI_ReadREFPowerUV(ADS868X_HandleType* ADS868x, UINT32_T refUV)
{
	return ADS868x->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����òο���ѹmv
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerMV(ADS868X_HandleType* ADS868x, UINT32_T refMV)
{
	ADS868x->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ÿͨ�������̺��������ֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS868X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS868x->msgChannelRange[chIndex])
		{
			//---����1.25����VREF
			case ADS868X_RANGE_5120MV_5120MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 1250);//5120000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //156250;
				break;
			//---����0.625����VREF
			case ADS868X_RANGE_2560MV_2560MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 625); //2560000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //78125;
				break;
			//---��2.5����VREF
			case ADS868X_RANGE_0MV_10240MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 2500);//10240000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = ADS868x->msgChannelRangeFullUVX1000[chIndex] / (1<< ADS868X_ADC_SAMPLE_BITS); //156250;
				break;
			//---��1.25����VREF
			case ADS868X_RANGE_0MV_5120MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV* 1250);//5120000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = ADS868x->msgChannelRangeFullUVX1000[chIndex] / (1<< ADS868X_ADC_SAMPLE_BITS); //78125;
				break;
			//---����2.5����VREF
			case ADS868X_RANGE_10240MV_10240MV:
			default:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 2500);//10240000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //312500;
				break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ��ADC�Ĳɼ��������ADCͨ���ĵ�ѹֵ
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalcChannelPower(ADS868X_HandleType* ADS868x, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---����������
	ADS868x->msgPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---�ж��Ƿ���Ҫ�����ֵ
	if (isCalcDelta != 0)
	{
		//---��ȡ�ϴκͱ��εĲ�������ľ��Բ�ֵ
		adcDelta = ABS_SUB(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex]);
		//---������ݲ�����Ͽ�ʼ
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS868x->msgChannelOldADCResult[chIndex] = MAX(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS868x->msgChannelNowADCResult[chIndex] > ADS868x->msgChannelOldADCResult[chIndex])
			{
				ADS868x->msgChannelOldADCResult[chIndex] = ADS868x->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS868x->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else if (ADS868x->msgChannelNowADCResult[chIndex] < ADS868x->msgChannelOldADCResult[chIndex])
			{
				ADS868x->msgChannelOldADCResult[chIndex] -= 1;
			}
			else
			{
				ADS868x->msgChannelOldADCResult[chIndex] = MAX(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS868x->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS868x->msgChannelNowADCResult[chIndex];
			ADS868x->msgChannelOldADCResult[chIndex] = ADS868x->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS868x->msgChannelNowADCResult[chIndex];
	}
	calcPower &= ((1<< ADS868X_ADC_SAMPLE_BITS)-1);
	//---������ݲ�����Ͻ���
	//---��������ת��Ϊģ����
	calcPower *= ADS868x->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---�ж�ADC������������˫���Ի��ǵ�����
	if (ADS868x->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if (((ADS868x->msgChannelNowADCResult[chIndex] & (1<< (ADS868X_ADC_SAMPLE_BITS-1)))) != 0)
		{
			ADS868x->msgPositive[chIndex] = 2;
			ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS868x->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS868x->msgPositive[chIndex] = 1;
			ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS868x->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS868x->msgPositive[chIndex] = 2;
		ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---�����������
	if (ADS868x->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS868x->msgChannelPowerResult[chIndex];
		adcPower *= ADS868x->msgADCKP[chIndex];
		if (adcPower< ADS868x->msgADCDelta[chIndex])
		{
			ADS868x->msgPositive[chIndex] = 1;
			adcPower = (ADS868x->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS868x->msgADCDelta[chIndex];
		}
		ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�Զ�ɨ��ͨ�����е�ADת������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTResult(ADS868X_HandleType *ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[4] = {0};
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS868x->msgReadyOK == 1)
	{
		_return = ADS868X_SPI_ConfigInit(ADS868x,0);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}
	//---�����Զ�ɨ��ģʽ
	_return =ADS868X_SPI_AUTORST(ADS868x,0);
	//---ɨ��ͨ���Ľ��
	for (i = 0; i < chNum; i++)
	{
		//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---׼����ȡ����
			if (ADS868x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
			}
			_return=ADS868X_SPI_SEND_ARRAY(ADS868x, adcWTemp, adcRTemp, 4);
			//---�������ݵĶ�ȡ
			if (ADS868x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
			}
			//---�����ȡ������
			ADS868x->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS868x->msgChannelNowADCResult[i] = (ADS868x->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			ADS868x->msgChannelNowADCResult[i] >>= ADS868X_DATA_SAMPLE_BITS;
			//---����������
			ADS868X_SPI_CalcChannelPower(ADS868x, i,0);
		}
		rstMode >>= 1;
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetAutoRSTNSampleResult(ADS868X_HandleType* ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	//---����������
	UINT16_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---��ȡ�������
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868x, chNum,0);
		//---�������ݰ���
		for (j=0;j< ADS868X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS868x->msgChannelNowADCResult[j];
		}
		//---У������
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---�������ݰ���
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				//---������������
				AscSortWord(adcSampleTemp[j], ADS868X_N_SAMPLE_COUNT);
				//---�����ֵ
				ADS868x->msgChannelNowADCResult[j] = CalcAvgWordFromIndex(adcSampleTemp[j], (ADS868X_N_SAMPLE_COUNT - 2), 2);
				//---��������ĵ�ѹֵ
				ADS868X_SPI_CalcChannelPower(ADS868x, j,1);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_KalmanFilterGetAutoRSTNSampleResult(ADS868X_HandleType* ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	//---����������
	UINT32_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---�������ṹ
	KalmanOneFilter_HandleType kalmanFilterX;
	//---��ȡ�������
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---��ȡ�������
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868x, chNum,0);
		//---�������ݰ���
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			adcSampleTemp[j][i] = ADS868x->msgChannelNowADCResult[j];
		}
		//---У������
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---�������ݰ���
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---�ж��Ƿ�ʹ���Զ�RSTɨ�蹦��
			if (rstMode & 0x01)
			{
				KalmanOneFilter_Init(&kalmanFilterX, (float)adcSampleTemp[j][0], 5e2);
				for (i = 1; i < ADS868X_N_SAMPLE_COUNT; i++)
				{
					//---�������˲�֮��Ľ��
					ADS868x->msgChannelNowADCResult[j] = (UINT32_T)KalmanOneFilter_Filter(&kalmanFilterX, (float)adcSampleTemp[j][i]);
				}
				//---��������ĵ�ѹֵ
				ADS868X_SPI_CalcChannelPower(ADS868x, j, 0);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ȡ�յ�ɨ��ͨ����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS868X_SPI_GetManualChannelResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[4] = { 0 };
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T adcChannel = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---�ж��豸�Ƿ��ʼ���ɹ�
	if (ADS868x->msgReadyOK==1)
	{
		_return=ADS868X_SPI_ConfigInit(ADS868x,0);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---�����ֶ�ɨ��ͨ��
	_return = ADS868X_SPI_ManualChannel(ADS868x, manualChannel,0);
	//---׼����ȡ���õ�ɨ��ͨ����ֵ
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	//---��ȡADC�����Ľ��
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, adcWTemp, adcRTemp, 4);
	//---������ȡ���õ�ɨ��ͨ����ֵ
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	//---ͨ����ת��
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�ж��Ƿ���AUXͨ������
	if (adcChannel<8)
	{
		ADS868x->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS868x->msgChannelNowADCResult[adcChannel] = (ADS868x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		ADS868x->msgChannelNowADCResult[adcChannel] >>= ADS868X_DATA_SAMPLE_BITS;
		//---����������
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannel,0);
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��ֶ�ͨ������N�εĲ��Խ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_GetManualChannelNSampleResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT16_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---��ȡ�������
	for ( i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868x, manualChannel,0);
		adcSampleTemp[i] = ADS868x->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---������������
		AscSortWord(adcSampleTemp, ADS868X_N_SAMPLE_COUNT);
		//---�����ֵ
		ADS868x->msgChannelNowADCResult[adcChannelIndex] = CalcAvgWordFromIndex(adcSampleTemp, (ADS868X_N_SAMPLE_COUNT - 2), 2);
		//---��������ĵ�ѹֵ
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannelIndex,1);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ��������˲���ʽ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_KalmanFilterGetManualChannelNSampleResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������
	UINT32_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---��ȡADC����ͨ�������
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---�������ṹ
	KalmanOneFilter_HandleType kalmanFilterX;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---��ȡ�������
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868x, manualChannel,0);
		adcSampleTemp[i] = ADS868x->msgChannelNowADCResult[adcChannelIndex];
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		KalmanOneFilter_Init(&kalmanFilterX, (float)adcSampleTemp[0], 5e2);
		for (i=1;i< ADS868X_N_SAMPLE_COUNT; i++)
		{
			//---�������˲�֮��Ľ��
			ADS868x->msgChannelNowADCResult[adcChannelIndex] =(UINT32_T) KalmanOneFilter_Filter(&kalmanFilterX,(float) adcSampleTemp[i]);
		}
		//---��������ĵ�ѹֵ
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannelIndex, 1);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ�У׼ͨ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_CalibrationChannelErr(ADS868X_HandleType* ADS868x)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1�Ű����
				//ADS868x->msgADCKP[i] = 1.013216;
				//ADS868x->msgADCDelta[i] = 27130;
				//---2�Ű����
				ADS868x->msgADCKP[i] = 1.013216;
				ADS868x->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1�Ű����
				//ADS868x->msgADCKP[i] = 1.0129;
				//ADS868x->msgADCDelta[i] = 25870;
				//---2�Ű����
				ADS868x->msgADCKP[i] = 1.0129;
				ADS868x->msgADCDelta[i] = 27070;
			}
			
		}
		rstMode >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��	    �ܣ���ʼ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ConfigInit(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;
	if (isAutoInit!=0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	if (ADS868x->msgInitRetryCount==0)
	{
		ADS868x->msgInitRetryCount = 1;
	}
	//---ѭ����γ�ʼ���豸
	for (i=0;i< ADS868x->msgInitRetryCount;i++)
	{
		//---��λоƬ
		_return = ADS868X_SPI_Reset(ADS868x,0);
		//---У��
		if (_return == OK_0)
		{
			//---�豸��������
			_return = ADS868X_SPI_WriteFeature(ADS868x, 0x28,0);
			//---У��
			if (_return == OK_0)
			{
				//---��ȡ�豸������
				_return = ADS868X_SPI_ReadFeature(ADS868x, tempBuffer,0);
				//---У��
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}
	//---����ɨ�跽ʽ
	_return = ADS868X_SPI_WriteAUTOSEQEN(ADS868x, 0xF0,0);
	//---��ȡ���õ�ֵ
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, tempBuffer);
	//---�ж�У��
	if (ADS868x->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS868x->msgReadyOK = 1;
	}
	else
	{
		//---����ͨ��������
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH0_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH1_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH2_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		//---���ù���ģʽ
		ADS868X_SPI_AUTORST(ADS868x,0);
	}
	ADS868X_SPI_CalibrationChannelErr(ADS868x);
    if (isAutoInit!=0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}