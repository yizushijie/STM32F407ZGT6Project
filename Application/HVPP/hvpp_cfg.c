#include "hvpp_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_DataBus_Write(HVPP_HandlerType* HVPPx,UINT8_T val )
{
	//---У�����������ǲ���д��״̬
	if (HVPPx->msgDataBusState!=HVPP_DATA_BUS_STATE_WRITE)
	{
		//---����Ϊ����̬
		HVPP_DATA_BUS_TO_HZ;
		//---���ö˿�Ϊ���ģʽ
		HVPP_DATA_BUS_WRITE;
		HVPPx->msgDataBusState = HVPP_DATA_BUS_STATE_WRITE;
		//---�л�������Ϊ�������豸
		HVPP_DATA_BUS_TO_DEVICE;
	}
	//---��������
	((val & 0x80) == 0) ? HVPP_DATA0_OUT_0 : HVPP_DATA0_OUT_1;
	((val & 0x40) == 0) ? HVPP_DATA1_OUT_0 : HVPP_DATA1_OUT_1;
	((val & 0x20) == 0) ? HVPP_DATA2_OUT_0 : HVPP_DATA2_OUT_1;
	((val & 0x10) == 0) ? HVPP_DATA3_OUT_0 : HVPP_DATA3_OUT_1;
	((val & 0x08) == 0) ? HVPP_DATA4_OUT_0 : HVPP_DATA4_OUT_1;
	((val & 0x04) == 0) ? HVPP_DATA5_OUT_0 : HVPP_DATA5_OUT_1;
	((val & 0x02) == 0) ? HVPP_DATA6_OUT_0 : HVPP_DATA6_OUT_1;
	((val & 0x01) == 0) ? HVPP_DATA7_OUT_0 : HVPP_DATA7_OUT_1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_DataBus_Read(HVPP_HandlerType* HVPPx)
{
	UINT8_T _return=0;
	//---У�����������ǲ��Ƕ�ȡ״̬
	if (HVPPx->msgDataBusState != HVPP_DATA_BUS_STATE_READ)
	{
		//---����Ϊ����̬
		HVPP_DATA_BUS_TO_HZ;
		//---���ö˿�Ϊ����ģʽ
		HVPP_DATA_BUS_READ;
		HVPPx->msgDataBusState = HVPP_DATA_BUS_STATE_READ;
		//---�л�������Ϊ�豸������
		HVPP_DATA_BUS_TO_HOST;
	}
	//---��ȡ����
	_return |= (HVPP_DATA0_STATE != 0 ? 0x80 : 0x00);
	_return |= (HVPP_DATA1_STATE != 0 ? 0x40 : 0x00);
	_return |= (HVPP_DATA2_STATE != 0 ? 0x20 : 0x00);
	_return |= (HVPP_DATA3_STATE != 0 ? 0x10 : 0x00);
	_return |= (HVPP_DATA4_STATE != 0 ? 0x08 : 0x00);
	_return |= (HVPP_DATA5_STATE != 0 ? 0x04 : 0x00);
	_return |= (HVPP_DATA6_STATE != 0 ? 0x02 : 0x00);
	_return |= (HVPP_DATA7_STATE != 0 ? 0x01 : 0x00);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_Device_Init(HVPP_HandlerType* HVPPx)
{
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---DATA_OE---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = HVPP_DATA_OE_BIT;
	LL_GPIO_Init(HVPP_DATA_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_OE_PORT, HVPP_DATA_OE_BIT);

	//---DATA_DIR---���Ϊ�ߣ����ݴ��������豸
	GPIO_InitStruct.Pin = HVPP_DATA_DIR_BIT;
	LL_GPIO_Init(HVPP_DATA_DIR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_DIR_PORT, HVPP_DATA_DIR_BIT);

	//---CTRL_OE---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = HVPP_CTRL_OE_BIT;
	LL_GPIO_Init(HVPP_CTRL_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_CTRL_OE_PORT, HVPP_CTRL_OE_BIT);

	//---HVPP_RDY_BSY---����Ϊ��
	GPIO_InitStruct.Pin  = HVPP_RDY_BSY_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(HVPP_RDY_BSY_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_RDY_BSY_PORT, HVPP_RDY_BSY_BIT);

	//---HVPP_OE---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_OE_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_OE_PORT, HVPP_OE_BIT);

	//---HVPP_WR---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_WR_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_WR_BIT);

	//---HVPP_BS1---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS1_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS1_BIT);

	//---HVPP_XA0---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA0_BIT;
	LL_GPIO_Init(HVPP_XA0_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA0_PORT, HVPP_XA0_BIT);

	//---HVPP_XA1---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA1_BIT;
	LL_GPIO_Init(HVPP_XA1_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA1_PORT, HVPP_XA1_BIT);

	//---HVPP_PAGEL---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_PAGEL_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_PAGEL_BIT);

	//---HVPP_BS2---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS2_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS2_BIT);

	//---HVPP_DATA---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_DATA_BUS_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(HVPP_DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_BUS_PORT, HVPP_DATA_BUS_BIT);
	//---������������״̬Ϊ��ȡ״̬
	HVPPx->msgDataBusState=HVPP_DATA_BUS_STATE_READ;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ö˿�Ϊ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_Device_DeInit(HVPP_HandlerType* HVPPx)
{
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---HVPP_RDY_BSY---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_RDY_BSY_BIT;
	LL_GPIO_Init(HVPP_RDY_BSY_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_RDY_BSY_PORT, HVPP_RDY_BSY_BIT);

	//---HVPP_OE---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_OE_BIT;
	LL_GPIO_Init(HVPP_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_OE_PORT, HVPP_OE_BIT);

	//---HVPP_WR---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_WR_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_WR_BIT);

	//---HVPP_BS1---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS1_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS1_BIT);

	//---HVPP_XA0---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA0_BIT;
	LL_GPIO_Init(HVPP_XA0_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA0_PORT, HVPP_XA0_BIT);

	//---HVPP_XA1---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA1_BIT;
	LL_GPIO_Init(HVPP_XA1_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA1_PORT, HVPP_XA1_BIT);

	//---HVPP_PAGEL---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_PAGEL_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_PAGEL_BIT);

	//---HVPP_BS2---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS2_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS2_BIT);

	//---HVPP_DATA---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_DATA_BUS_BIT;
	LL_GPIO_Init(HVPP_DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_BUS_PORT, HVPP_DATA_BUS_BIT);

	//---�л�����Ϊ�豸������
	HVPP_DATA_BUS_TO_HOST;
	//---�����ź�Ϊ����ģʽ
	HVPP_CTRL_TO_HZ;
	//---����Ϊ��ȡģʽ
	HVPPx->msgDataBusState=HVPP_DATA_BUS_STATE_READ;
	//---�ر���������
	HVPP_DATA_BUS_TO_HZ;

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_GPIO_Init(HVPP_HandlerType* HVPPx)
{
	//---ʹ�ܿ������ߵĶ˿�ʱ��
	GPIOTask_Clock(HVPP_RDY_BSY_PORT, 1);
	GPIOTask_Clock(HVPP_OE_PORT, 1);
	GPIOTask_Clock(HVPP_WR_PORT, 1);
	GPIOTask_Clock(HVPP_BS1_PORT, 1);
	GPIOTask_Clock(HVPP_XA0_PORT, 1);
	GPIOTask_Clock(HVPP_XA1_PORT, 1);
	GPIOTask_Clock(HVPP_PAGEL_PORT, 1);
	GPIOTask_Clock(HVPP_BS2_PORT, 1);
	GPIOTask_Clock(HVPP_XTAL_PORT, 1);
	GPIOTask_Clock(HVPP_CTRL_OE_PORT, 1);

	//---ʹ���������ߵĶ˿�ʱ��
	GPIOTask_Clock(HVPP_DATA0_PORT, 1);
	GPIOTask_Clock(HVPP_DATA1_PORT, 1);
	GPIOTask_Clock(HVPP_DATA2_PORT, 1);
	GPIOTask_Clock(HVPP_DATA3_PORT, 1);
	GPIOTask_Clock(HVPP_DATA4_PORT, 1);
	GPIOTask_Clock(HVPP_DATA5_PORT, 1);
	GPIOTask_Clock(HVPP_DATA6_PORT, 1);
	GPIOTask_Clock(HVPP_DATA7_PORT, 1);
	GPIOTask_Clock(HVPP_DATA_OE_PORT, 1);
	GPIOTask_Clock(HVPP_DATA_DIR_PORT, 1);
	//---���ö˿ڵĳ�ʼ��״̬
	HVPP_Device_Init(HVPPx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_Init(HVPP_HandlerType* HVPPx,void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return OK_0;
}