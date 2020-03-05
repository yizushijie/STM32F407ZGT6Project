#include "lcd1602_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_GPIOInit(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(LCD1602_RS_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(LCD1602_RW_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(LCD1602_EN_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(LCD1602_DATA_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---LCD1602_RS_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LCD1602_RS_BIT;
	LL_GPIO_Init(LCD1602_RS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(LCD1602_RS_PORT, LCD1602_RS_BIT);

	//---LCD1602_RW_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LCD1602_RW_BIT;
	LL_GPIO_Init(LCD1602_RW_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(LCD1602_RW_PORT, LCD1602_RW_BIT);

	//---LCD1602_EN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LCD1602_EN_BIT;
	LL_GPIO_Init(LCD1602_EN_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(LCD1602_EN_PORT, LCD1602_EN_BIT);

	//---LCD1602_DATA_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LCD1602_DATA_BITS;
	LL_GPIO_Init(LCD1602_DATA_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(LCD1602_DATA_PORT, LCD1602_DATA_BITS);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ���� �ж�1602Һ��æ�����ȴ�
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_WaitReady(void)
{
	UINT32_T _return = 0;

	//---��λ��������
	LCD1602_DATA_VAL(0xFF);

	//---RS����
	LCD1602_RS_OUT_0;

	//--RW����
	LCD1602_RW_OUT_1;
	while (1)
	{
		//---ʹ��EN
		LCD1602_EN_OUT_1;
		DelayTask_ms(5);

		//---��ȡ����
		_return = LCD1602_DATA_STATE;

		//---����ʹ���Ա�����һ�β���������
		LCD1602_EN_OUT_0;

		//---�ж�״̬��BIT7λ�Ƿ�Ϊ1��Ϊ1���ʾæ������ȴ�
		if ((_return&LCD1602_BIT7_MASK) == 0)
		{
			//---�˳�ѭ��
			break;
		}
	}

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�дLCD1602����
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_WriteCmd(UINT8_T cmd)
{
	//---�ж�æ��æ��ȴ�
	LCD1602_WaitReady();
	LCD1602_RS_OUT_0;
	LCD1602_RW_OUT_0;

	//---д������
	LCD1602_DATA_VAL(cmd);

	//---����ʹ�ܶ� ���ݱ����䵽LCD1602��
	LCD1602_EN_OUT_1;

	//---����ʹ���Ա�����һ�β���������
	LCD1602_EN_OUT_0;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�дLCD1602����
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_WriteData(UINT8_T val)
{
	//---�ж�æ��æ��ȴ�
	LCD1602_WaitReady();
	LCD1602_RS_OUT_1;
	LCD1602_RW_OUT_0;

	//---д������
	LCD1602_DATA_VAL(val);

	//---����ʹ�ܶ� ���ݱ����䵽LCD1602��
	LCD1602_EN_OUT_1;

	//---����ʹ���Ա�����һ�β���������
	LCD1602_EN_OUT_0;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���������
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_ClearScreen(void)
{
	return LCD1602_WriteCmd(0x01);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ����ù��λ��
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_SetCursor(UINT8_T xPos, UINT8_T yPos)
{
	if (yPos != 0)
	{
		xPos += 0x40;
	}
	return LCD1602_WriteCmd(xPos | 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�LCD1602��ʾ�ַ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_ShowChar(UINT8_T xPos, UINT8_T yPos, UINT8_T dat)
{
	//---���ù��
	LCD1602_SetCursor(xPos, yPos);

	//---��ʾ�ַ�
	return LCD1602_WriteData(dat);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�LCD1602��ʾ�ַ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_ShowStr(UINT8_T xPos, UINT8_T yPos, UINT8_T *str)
{
	//---���ù��
	LCD1602_SetCursor(xPos, yPos);

	//---��ʾ�ַ���
	while (*str != '\0')
	{
		LCD1602_WriteData(*str);
		str++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�LCD1602��ʼ��
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LCD1602_Init(void)
{
	//---GPIO�ĳ�ʼ��
	LCD1602_GPIOInit();

	//16*2��ʾ��5*7����8λ���ݿ�
	LCD1602_WriteCmd(0x38);

	//����ʾ�����ر�
	LCD1602_WriteCmd(0x0C);

	//���ֲ�������ַ�Զ�+1
	LCD1602_WriteCmd(0x06);

	//����
	LCD1602_WriteCmd(0x01);
	return OK_0;
}