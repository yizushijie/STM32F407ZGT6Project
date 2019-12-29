#include "ds1302_cfg.h"

//===ȫ�ֱ�������
DS1302_HandlerType		g_Ds1302Device0 = { 0 };
pDS1302_HandlerType		pDs1302Device0 = &g_Ds1302Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device0_Init(DS1302_HandlerType *DS1302x)
{
	DS1302x->msgCS.msgGPIOPort = GPIOB;
	DS1302x->msgCS.msgGPIOBit = LL_GPIO_PIN_5;

	DS1302x->msgCLK.msgGPIOPort = GPIOB;
	DS1302x->msgCLK.msgGPIOBit = LL_GPIO_PIN_6;

	DS1302x->msgDAT.msgGPIOPort = GPIOB;
	DS1302x->msgDAT.msgGPIOBit = LL_GPIO_PIN_8;

	DS1302x->msgPluseWidth = 1000;
	DS1302x->msgDelayus = NULL;

	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(DS1302x->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(DS1302x->msgCLK.msgGPIOPort, 1);
	GPIOTask_Clock(DS1302x->msgDAT.msgGPIOPort, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---CS�˿ڵĳ�ʼ��
	GPIO_InitStruct.Pin = DS1302x->msgCS.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCS.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);

	//---CLK�˿ڵĳ�ʼ��
	GPIO_InitStruct.Pin = DS1302x->msgCLK.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCLK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);

	//---DAT�˿ڵĳ�ʼ��
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pin = DS1302x->msgDAT.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgDAT.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device1_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Device2_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Init(DS1302_HandlerType *DS1302x, void(*pFuncDelayus)(UINT32_T delay))
{
	//---ָ���豸�ĳ�ʼ��
	if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_ONE))
	{
		DS1302_Device0_Init(DS1302x);
	}
	else if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_TWO))
	{
		DS1302_Device1_Init(DS1302x);
	}
	else if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_THREE))
	{
		DS1302_Device2_Init(DS1302x);
	}
	else
	{
		return ERROR_1;
	}

   //---us��ʱ
	if (pFuncDelayus!=NULL)
	{
		DS1302x->msgDelayus = pFuncDelayus;
	}
	else
	{
		DS1302x->msgDelayus = DelayTask_us;
	}
	//---�˳�����ģʽ
	DS1302_DisableSleepMode(DS1302x);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteByteLSB(DS1302_HandlerType* DS1302x, UINT8_T wVal)
{
	UINT8_T i = 0;
	for (i=0;i<8;i++)
	{
		if ((wVal&0x01)!=0)
		{
			GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
		}
		else
		{
			GPIO_OUT_0(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
		}
		GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
		GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
		wVal >>= 1;
	}
	//---??????
	GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_ReadByteLSB(DS1302_HandlerType* DS1302x)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;
	for (i = 0; i < 8; i++)
	{
		GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}	
		_return >>= 1;
		//---��ȡ1bit������
		if (GPIO_GET_STATE(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit) != 0)
		{
			_return |= 0x80;
		}
		else
		{
			_return &= 0x7F;
		}
		GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�DS1302�˳�����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_DisableSleepMode(DS1302_HandlerType* DS1302x)
{
	UINT8_T _return = 0x00;
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &_return);
	if ((_return&0x80)!=0)
	{
		//---�˳�����ģʽ
		DS1302_WriteTime(DS1302x,DS1302_REG_SECOND,_return&0x7F);
		DS1302x->msgRTC.second = BcdToDec(_return & 0x7F);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�DS1302��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  DS1302_EnableSleepMode(DS1302_HandlerType* DS1302x)
{
	//---ʹ������ģʽ
	DS1302_WriteTime(DS1302x, DS1302_REG_SECOND, 0x80);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����DS1302�Ƿ���ڣ����ȱ�֤�豸�Ѿ����빤��ģʽ����������ģʽ������������
//////�������:
//////�������: 0---�豸���ڣ�1---�豸�쳣
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_CheckDevice(DS1302_HandlerType* DS1302x)
{
	UINT8_T _return = 0x00;
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &_return);
	if ((_return & 0x80) != 0)
	{
		_return = ERROR_1;
	}
	else
	{
		_return = OK_0;
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
void DS1302_WriteReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, addr&0xFE);
	DS1302_WriteByteLSB(DS1302x, dat);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, addr|0x01);
	*pVal=DS1302_ReadByteLSB(DS1302x);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);	
	
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������ʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	//---ȡ��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---��ָ����λ��д��ָ��������
	DS1302_WriteReg(DS1302x, addr, dat);
	//---��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	DS1302_ReadReg(DS1302x, addr, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������ʵʱʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteRTC(DS1302_HandlerType *DS1302x, RTC_HandlerType rtcTime)
{
	DS1302x->msgRTC = rtcTime;
	//---ȡ��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---д������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_SECOND, DecToBcd((rtcTime.second)&0x7F));
	//---д������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_MINUTE, DecToBcd(rtcTime.minute));
	//---дʱ����,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_HOUR, DecToBcd(rtcTime.hour));
	//---д������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_DAY, DecToBcd(rtcTime.day));
	//---д��������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_WEEK, DecToBcd(rtcTime.week));
	//---д������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_MONTH, DecToBcd(rtcTime.month));
	//---д������,����תBCD��ʽ
	DS1302_WriteReg(DS1302x, DS1302_REG_YEAR, DecToBcd(rtcTime.year));
	//---��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡʵʱʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadRTC(DS1302_HandlerType *DS1302x)
{
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &(DS1302x->msgRTC.second));
	//---BCDת����
	DS1302x->msgRTC.second = BcdToDec(DS1302x->msgRTC.second);
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_MINUTE, &(DS1302x->msgRTC.minute));
	//---BCDת����
	DS1302x->msgRTC.minute = BcdToDec(DS1302x->msgRTC.minute);
	//---��ʱ����
	DS1302_ReadReg(DS1302x, DS1302_REG_HOUR, &(DS1302x->msgRTC.hour));

	if ((DS1302x->msgRTC.hour&0x80)!=0)
	{
		//---��ʾ12Сʱ��
		DS1302x->msgRTC.time24H = 0;
	}
	else
	{
		//---��ʾ24Сʱ��
		DS1302x->msgRTC.time24H = 1;
	}
	
	if ((DS1302x->msgRTC.hour & 0x20) == 0)
	{
		//---��ʾ����
		DS1302x->msgAMOrPM = 0;
	}
	else
	{
		//---��ʾ����
		DS1302x->msgAMOrPM = 0;
	}

	//---BCDת����
	DS1302x->msgRTC.hour = BcdToDec(DS1302x->msgRTC.hour&=(DS1302x->msgRTC.time24H==1?0x3F:0x1F));
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_DAY, &(DS1302x->msgRTC.day));
	//---BCDת����
	DS1302x->msgRTC.day = BcdToDec(DS1302x->msgRTC.day);
	//---����������
	DS1302_ReadReg(DS1302x, DS1302_REG_WEEK, &(DS1302x->msgRTC.week));
	//---BCDת����
	DS1302x->msgRTC.week = BcdToDec(DS1302x->msgRTC.week);
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_MONTH, &(DS1302x->msgRTC.month));
	//---BCDת����
	DS1302x->msgRTC.month = BcdToDec(DS1302x->msgRTC.month);
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_YEAR, &(DS1302x->msgRTC.year));
	//---BCDת����
	DS1302x->msgRTC.year = BcdToDec(DS1302x->msgRTC.year);
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ȡ���е�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadBurstRTC(DS1302_HandlerType* DS1302x)
{
	UINT8_T i = 0;
	UINT8_T rtc[7] = {0};
	DS1302_WriteByteLSB(DS1302x, DS1302_BURST_READ_RAM | 0x01);
	for (i=0;i<7;i++)
	{
		rtc[i]= DS1302_ReadByteLSB(DS1302x);
	}
	//---��������---BCDת����
	DS1302x->msgRTC.second = BcdToDec(rtc[0]);
	//-----BCDת����
	DS1302x->msgRTC.minute = BcdToDec(rtc[1]);
	//---��ʱ����
	DS1302x->msgRTC.hour = BcdToDec(rtc[2]);
	if ((DS1302x->msgRTC.hour & 0x80) != 0)
	{
		//---��ʾ12Сʱ��
		DS1302x->msgRTC.time24H = 0;
	}
	else
	{
		//---��ʾ24Сʱ��
		DS1302x->msgRTC.time24H = 1;
	}

	if ((DS1302x->msgRTC.hour & 0x20) == 0)
	{
		//---��ʾ����
		DS1302x->msgAMOrPM = 0;
	}
	else
	{
		//---��ʾ����
		DS1302x->msgAMOrPM = 0;
	}

	//---BCDת����
	DS1302x->msgRTC.hour = BcdToDec(DS1302x->msgRTC.hour &= (DS1302x->msgRTC.time24H == 1 ? 0x3F : 0x1F));
	//---��������---BCDת����
	DS1302x->msgRTC.day = BcdToDec(rtc[3]);
	//---����������---BCDת����
	DS1302x->msgRTC.week = BcdToDec(rtc[5]);
	//---��������---BCDת����
	DS1302x->msgRTC.month = BcdToDec(rtc[4]);
	//---��������---BCDת����
	DS1302x->msgRTC.year = BcdToDec(rtc[6]);
}