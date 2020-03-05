#include "hvpp_cfg.h"

//===ȫ�ֱ����Ķ���
HVPP_HandleType  g_HvppDevice0 = { 0 };
pHVPP_HandleType pHvppDevice0 = &g_HvppDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������Ϊд��ģʽ,��д��ָ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_DATABUS_WRITE(HVPP_HandleType* HVPPx,UINT8_T val )
{
	//---У�����������ǲ���д��״̬
	if (HVPPx->msgDataBusState!=HVPP_DATA_BUS_MODE_WRITE)
	{
		//---����Ϊ����̬
		HVPP_DATA_BUS_DIR_TO_HZ;
		//---���ö˿�Ϊ���ģʽ
		HVPP_DATA_BUS_WRITE;
		HVPPx->msgDataBusState = HVPP_DATA_BUS_MODE_WRITE;
		//---�л�������Ϊ�������豸
		HVPP_DATA_BUS_DIR_TO_DEVICE;
		//---�ȴ�״̬�ȶ�
		HVPP_WAIT_STATE_STABLE;
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
//////��		�ܣ���������Ϊ��ȡģʽ
//////�������: isReadDir---0�л�����Ϊ��ȡģʽ��1---��ȡ��������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_DATABUS_READ(HVPP_HandleType* HVPPx,UINT8_T isReadDir)
{
	UINT8_T _return=0;
	//---У�����������ǲ��Ƕ�ȡ״̬
	if (HVPPx->msgDataBusState != HVPP_DATA_BUS_MODE_READ)
	{
		//---����Ϊ����̬
		HVPP_DATA_BUS_DIR_TO_HZ;
		//---���ö˿�Ϊ����ģʽ
		HVPP_DATA_BUS_READ;
		HVPPx->msgDataBusState = HVPP_DATA_BUS_MODE_READ;
		//---�л�������Ϊ�豸������
		HVPP_DATA_BUS_DIR_TO_HOST;
		//---�ȴ�״̬�ȶ�
		HVPP_WAIT_STATE_STABLE;
	}
	if (isReadDir!= HVPP_DATA_BUS_READ_DIR)
	{
		//---��ȡ����
		_return |= (HVPP_DATA0_STATE != 0 ? 0x80 : 0x00);
		_return |= (HVPP_DATA1_STATE != 0 ? 0x40 : 0x00);
		_return |= (HVPP_DATA2_STATE != 0 ? 0x20 : 0x00);
		_return |= (HVPP_DATA3_STATE != 0 ? 0x10 : 0x00);
		_return |= (HVPP_DATA4_STATE != 0 ? 0x08 : 0x00);
		_return |= (HVPP_DATA5_STATE != 0 ? 0x04 : 0x00);
		_return |= (HVPP_DATA6_STATE != 0 ? 0x02 : 0x00);
		_return |= (HVPP_DATA7_STATE != 0 ? 0x01 : 0x00);
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
UINT8_T HVPP_GPIO_Init(HVPP_HandleType* HVPPx)
{
	//---RST����
	HVPP_DUT_RST_TO_GND;
	//---ʹ�ܿ������ߵĶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(HVPP_RDY_BSY_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_OE_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_WR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_BS1_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_XA0_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_XA1_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_PAGEL_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_BS2_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_XTAL_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_CTRL_OE_PORT, PERIPHERAL_CLOCK_ENABLE);

	//---ʹ���������ߵĶ˿�ʱ��
	GPIOTask_Clock(HVPP_DATA0_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA1_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA2_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA3_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA4_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA5_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA6_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA7_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA_OE_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(HVPP_DATA_DIR_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;																															//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---�˿ڸ���ģʽ
#endif
	//---DATA_OE---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = HVPP_DATA_OE_BIT;
	LL_GPIO_Init(HVPP_DATA_OE_PORT, &GPIO_InitStruct);
	//---DATA_DIR---���Ϊ�ߣ����ݴ��豸������
	GPIO_InitStruct.Pin = HVPP_DATA_DIR_BIT;
	LL_GPIO_Init(HVPP_DATA_DIR_PORT, &GPIO_InitStruct);
	//---��������Ϊ�������豸
	HVPP_DATA_BUS_DIR_TO_DEVICE;

	//---CTRL_OE---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = HVPP_CTRL_OE_BIT;
	LL_GPIO_Init(HVPP_CTRL_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(HVPP_CTRL_OE_PORT, HVPP_CTRL_OE_BIT);

	//---HVPP_RDY_BSY---����Ϊ�ߣ��ö˿�һֱ��������ģʽ
	GPIO_InitStruct.Pin = HVPP_RDY_BSY_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(HVPP_RDY_BSY_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_RDY_BSY_PORT, HVPP_RDY_BSY_BIT);

	//---HVPP_OE---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_OE_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_OE_PORT, HVPP_OE_BIT);

	//---HVPP_WR---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_WR_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_WR_BIT);

	//---HVPP_BS1---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS1_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_BS1_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(HVPP_BS1_PORT, HVPP_BS1_BIT);
	
	//---HVPP_XA0---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA0_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_XA0_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA0_PORT, HVPP_XA0_BIT);

	//---HVPP_XA1---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA1_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_XA1_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA1_PORT, HVPP_XA1_BIT);

	//---HVPP_PAGEL---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_PAGEL_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_PAGEL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(HVPP_PAGEL_PORT, HVPP_PAGEL_BIT);

	//---HVPP_BS2---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS2_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_BS2_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(HVPP_BS2_PORT, HVPP_BS2_BIT);

	//---HVPP_XTAL---���Ϊ��
	GPIO_InitStruct.Pin = HVPP_XTAL_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_XTAL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(HVPP_XTAL_PORT, HVPP_XTAL_BIT);

	//---HVPP_DATA---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_DATA_BUS_BIT;
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Init(HVPP_DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_BUS_PORT, HVPP_DATA_BUS_BIT);
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(HVPP_DATA_BUS_PORT, &GPIO_InitStruct);
	//---������������״̬Ϊ��ȡ״̬
	HVPPx->msgDataBusState = HVPP_DATA_BUS_MODE_READ;
	//---�����ź�Ϊ����ģʽ
	HVPP_CTRL_DIR_TO_HZ;
	//---�ͷ�RST�˿�
	HVPP_DUT_RST_TO_HZ;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ö˿�Ϊ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_GPIO_DeInit(HVPP_HandleType* HVPPx)
{
	//---�л���������Ϊ�豸������
	HVPP_DATA_BUS_DIR_TO_HOST;
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;																																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;																															//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---�˿ڸ���ģʽ
#endif
	//---HVPP_RDY_BSY---����Ϊ�ߣ��ö˿�һֱ��������ģʽ
	GPIO_OUT_1(HVPP_RDY_BSY_PORT, HVPP_RDY_BSY_BIT);
	//---HVPP_OE---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_OE_BIT;
	LL_GPIO_Init(HVPP_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_OE_PORT, HVPP_OE_BIT);
	//---HVPP_WR---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_WR_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_WR_BIT);
	//---HVPP_BS1---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS1_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS1_BIT);
	//---HVPP_XA0---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA0_BIT;
	LL_GPIO_Init(HVPP_XA0_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA0_PORT, HVPP_XA0_BIT);
	//---HVPP_XA1---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_XA1_BIT;
	LL_GPIO_Init(HVPP_XA1_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_XA1_PORT, HVPP_XA1_BIT);
	//---HVPP_PAGEL---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_PAGEL_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_PAGEL_BIT);
	//---HVPP_BS2---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_BS2_BIT;
	LL_GPIO_Init(HVPP_WR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_WR_PORT, HVPP_BS2_BIT);
	//---HVPP_DATA---����Ϊ��
	GPIO_InitStruct.Pin = HVPP_DATA_BUS_BIT;
	LL_GPIO_Init(HVPP_DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(HVPP_DATA_BUS_PORT, HVPP_DATA_BUS_BIT);
	//---�����ź�Ϊ����ģʽ
	HVPP_CTRL_DIR_TO_HZ;
	//---����Ϊ��ȡģʽ
	HVPPx->msgDataBusState=HVPP_DATA_BUS_MODE_READ;
	//---�ر���������
	HVPP_DATA_BUS_DIR_TO_HZ;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʱ������ĸ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HVPP_XTAL_CLK(HVPP_HandleType* HVPPx,UINT8_T clkNum)
{
	UINT8_T i=0;
	//---ִ�ж˿ڵķ�ת
	for (i=0;i<clkNum;i++)
	{
		HVPPx->pMsgDelayus(HVPPx->msgXtalPulseWidth);
		HVPP_XTAL_OUT_1;
		HVPPx->pMsgDelayus(HVPPx->msgXtalPulseWidth);
		HVPP_XTAL_OUT_0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ʱ������Ŀ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HVPP_XTAL_PULSE(HVPP_HandleType* HVPPx)
{
	HVPPx->pMsgDelayus(HVPPx->msgXtalPulseWidth);
	HVPP_XTAL_OUT_1;
	HVPPx->pMsgDelayus(HVPPx->msgXtalPulseWidth);
	HVPP_XTAL_OUT_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_Init(HVPP_HandleType* HVPPx,void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	HVPPx->msgState = 0;
	HVPPx->msgXtalPulseWidth=5;
	HVPPx->msgHvFastMode=0;
	HVPPx->msgFactoryPattern=0;
	HVPPx->msgSelfPower=0;
	HVPPx->msgHvCmd=0x00;
	HVPPx->msgLoadCmd = 0x00;
	HVPPx->msgWaitms=1;
	HVPPx->msgProgWRLus=500;
	HVPPx->msgProgWRHus = 800;
	//---���΢����ʱ
	if (pFuncDelayus!=NULL)
	{
		HVPPx->pMsgDelayus=pFuncDelayus;
	}
	else
	{
		HVPPx->pMsgDelayus =DelayTask_us;
	}
	//---��Ӻ�����ʱ
	if (pFuncDelayms != NULL)
	{
		HVPPx->pMsgDelayms = pFuncDelayms;
	}
	else
	{
		HVPPx->pMsgDelayms = DelayTask_ms;
	}
	//---��Ӷ�ʱ����
	if (pFuncTimerTick!=NULL)
	{
		HVPPx->pMsgTimeTick=pFuncTimerTick;
	}
	else
	{
		HVPPx->pMsgTimeTick=SysTickTask_GetTick;
	}
	HVPP_GPIO_Init(HVPPx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_DeInit(HVPP_HandleType* HVPPx)
{
	HVPPx->msgSelfPower = 0;
	HVPPx->msgXtalPulseWidth = 5;
	HVPP_GPIO_DeInit(HVPPx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸1�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HVPP_AddWatchDevice0(void)
{
	HVPP_WatchTask(HVPP_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HVPP_WatchTask(HVPP_HandleType* HVPPx)
{
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (HVPPx->msgState != 0)
	{
		//---��ȡ��ǰʱ�����
		nowTime = HVPPx->pMsgTimeTick();
		//---����ʱ����
		if (HVPPx->msgRecordTick > nowTime)
		{
			cnt = (0xFFFFFFFF - HVPPx->msgRecordTick + nowTime);
		}
		else
		{
			cnt = nowTime - HVPPx->msgRecordTick;
		}
		//if (cnt > ISP_STATE_TIME_OUT_MS)
		//---����Ƿ�����ʱ�¼�
		if (cnt > HVPPx->msgIntervalTime)
		{
			HVPP_ExitProg(HVPPx);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_AddWatch(HVPP_HandleType* HVPPx)
{
	//---ˢ��ʱ��
	HVPP_RefreshWatch(HVPPx);
	//---ʹ�õ�HVPP�Ķ˿�,��ע����Ӧ��������
	SysTickTask_CreateTickTask(HVPP_AddWatchDevice0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_RemoveWatch(HVPP_HandleType* HVPPx)
{
	SysTick_DeleteTickTask(HVPP_AddWatchDevice0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_RefreshWatch(HVPP_HandleType* HVPPx)
{
	//---������ѵ���Ϊ���ֵ����λ��ms
	HVPPx->msgIntervalTime = HVPP_STATE_TIME_OUT_MS;
	//---ˢ�¼�¼ʱ��
	HVPPx->msgRecordTick = HVPPx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_SetIntervalTime(HVPP_HandleType* HVPPx, UINT16_T intervalTime)
{
	//---������ѵ���ʱ�䣬��λ��ms
	HVPPx->msgIntervalTime = intervalTime;
	//---ˢ�¼�¼ʱ��
	HVPPx->msgRecordTick = HVPPx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_GetIntervalTime(HVPP_HandleType* HVPPx)
{
	return HVPPx->msgIntervalTime;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ����������Ĳ�ͬ�����и�ѹ���벻�ݵ�ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ProgModeEnter(HVPP_HandleType* HVPPx,UINT8_T pagel,UINT8_T xa1,UINT8_T xa0,UINT8_T bs1)
{
	//>>>---���ò������ݶ˿ںͲ������ݿ��ƶ˿�δ����ģʽ���Ҳ������ݷ���Ϊ�豸������ģʽ��֮��˿ڴ��ڸ���״̬
	HVPP_DUT_RST_TO_GND;
	//---���磬�Թ����ʱ����е�Դ�ϵ磬����Ϊ�ͷŵ�Դ����״̬
	((HVPPx->msgSelfPower == 0) ? HVPP_DUT_POWER_OFF : HVPP_DUT_POWER_HZ);
	HVPPx->pMsgDelayms(1);
	//---�л��������߷���
	HVPP_DATA_BUS_DIR_TO_DEVICE;
	//---������������Ϊдģʽ
	HVPP_DATA_BUS_WRITE;
	//---���ÿ�������Ϊдģʽ
	HVPP_CTRL_INIT_WRITE;
	//---�ȴ�״̬�ȶ�
	HVPP_WAIT_STATE_STABLE;
	//---�ϵ磬�Թ����ʱ����е�Դ�ϵ磬����Ϊ�ͷŵ�Դ����״̬
	((HVPPx->msgSelfPower == 0) ? HVPP_DUT_POWER_ON : HVPP_DUT_POWER_HZ);
	HVPPx->pMsgDelayms(5);
	HVPP_XTAL_CLK(HVPPx,8);
	//---PAGEL
	((pagel != 0) ? HVPP_PAGEL_OUT_1 : HVPP_PAGEL_OUT_0);
	//---XA1
	((xa1 != 0) ? HVPP_XA1_OUT_1 : HVPP_XA1_OUT_0);
	//---XA0
	((xa0 != 0) ? HVPP_XA0_OUT_1 : HVPP_XA0_OUT_0);
	//---BS1
	((bs1 != 0) ? HVPP_BS1_OUT_1 : HVPP_BS1_OUT_0);
	//---����һ��ʱ�䲻С��100ns
	HVPPx->pMsgDelayus(5);
	//---HV
	//HVPP_DUT_RST_TO_12V;
	//---����һ��ʱ�䲻С��100ns
	HVPPx->pMsgDelayus(5);
	//---��������
	HVPPx->msgDataBusState = HVPP_DATA_BUS_MODE_WRITE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����и�ѹģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ProgModeExit(HVPP_HandleType* HVPPx)
{
	//---RST���͵���
	HVPP_DUT_RST_TO_GND;
	//---���ݶ˿�����Ϊ��ȡģʽ
	HVPP_DATA_BUS_READ;
	//---�����߷���ʹ�豸������
	HVPP_DATA_BUS_DIR_TO_HOST;
	//---���ƶ˿�����Ϊ���ģʽ
	//HVPP_CTRL_BUS_VAL(0x7F);
	//HVPP_CTRL_INIT_READ;
	//---���ÿ�����Ϊ����̬
	HVPP_CTRL_DIR_TO_HZ;
	//---�رյ�Դ,�Թ����ʱ����е�Դ�ϵ磬����Ϊ�ͷŵ�Դ����״̬
	((HVPPx->msgSelfPower == 0) ? HVPP_DUT_POWER_OFF : HVPP_DUT_POWER_HZ);
	HVPPx->pMsgDelayms(1);
	//---�ͷ�RST�Ŀ���
	HVPP_DUT_RST_TO_HZ;
	//---���ÿ�����Ϊ����̬
	//HVPP_CTRL_DIR_TO_HZ;
	//---��������
	HVPPx->msgDataBusState = HVPP_DATA_BUS_MODE_READ;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ
//////�������: hvModeCmd---��ѹ���0x00---����ģʽ��0x0x---����ģʽ����������ģʽ
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_EnterProg(HVPP_HandleType* HVPPx, UINT8_T hvProgCmd)
{
	HVPPx->msgState=1;
	//---У�������ǲ�����ͬ����
	if (hvProgCmd!= HVPPx->msgHvCmd)
	{
		//---ִ���˳�����ģʽ
		HVPP_ExitProg(HVPPx);
	}
	HVPPx->msgHvCmd=hvProgCmd;
	HVPPx->msgHvFastMode=((hvProgCmd!=0)?1:0);
	//---������ģʽ
	return  HVPP_ProgModeEnter(HVPPx,hvProgCmd&0x08, hvProgCmd & 0x04, hvProgCmd & 0x02,hvProgCmd & 0x01);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ExitProg(HVPP_HandleType* HVPPx)
{
	HVPPx->msgState = 0;
	HVPPx->msgHvFastMode = 0;
	HVPPx->msgHvCmd = 0x00;
	HVPPx->msgLoadCmd=0x00;
	return HVPP_ProgModeExit(HVPPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ׼���ñ�־λ
//////�������:
//////�������: 0---׼���ã���0---δ׼���ã������쳣״̬
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadReady(HVPP_HandleType* HVPPx)
{
	UINT8_T _return = 0;
	//---��ȡʱ���ǩ
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;
	//---��ȡ��ǰʱ���ǩ
	if (HVPPx->pMsgTimeTick != NULL)
	{
		oldTime = HVPPx->pMsgTimeTick();
	}
	//---��ѯæ��־λ
	while (1)
	{
		//---���RDY_BSY��0---æµ״̬��1---����״̬
		_return=HVPP_RDY_BSY_STATE;
		//---У���Ƿ��ǿ���״̬����0Ϊ����״̬
		if (_return != 0x00)
		{
			_return = OK_0;
			break;
		}
		else
		{
			if (HVPPx->pMsgTimeTick != NULL)
			{
				//---��ǰʱ��
				nowTime = HVPPx->pMsgTimeTick();
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
				if (cnt > 100)
				{
					//---���ͷ�����ʱ����
					_return = ERROR_2;
					break;
				}
			}
			else
			{
				nowTime++;
				if (nowTime > 100000)
				{
					//---���ͷ�����ʱ����
					_return = ERROR_3;
					break;
				}
			}
		}
		WDT_RESET();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�оƬ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_EraseChip(HVPP_HandleType* HVPPx)
{
	UINT8_T _return=OK_0;
	UINT8_T i = 0;
	//---ʹ���������
	HVPP_ENABLE_CMD_LOAD;
	//---����оƬ��������
	HVPP_DATABUS_WRITE(HVPPx, HVPP_CMD_CHIP_ERASE);
	//---��XTALһ�����������ڼ�������
	HVPP_XTAL_PULSE(HVPPx);
	//---У���ǲ��ǿ���ģʽ
	if (HVPPx->msgHvFastMode==0)
	{
		//---�ȴ�������ɣ���ʶ��RDY_BSY�ӵ͵�ƽ��ɸߵ�ƽ
		_return = HVPP_ReadReady(HVPPx);
	}
	else
	{
		//>>>---����ģʽ
		//---ʹ�ܲ���
		HVPP_WR_OUT_0;
		//---�ȴ���ʱ
		HVPPx->pMsgDelayus(HVPPx->msgProgWRLus);
		//---��ʹ�ܲ���
		HVPP_WR_OUT_1;
		//---�ȴ���ʱ
		HVPPx->pMsgDelayus(HVPPx->msgProgWRHus);
	}	
	//---�ͷ�״̬,Ϊ����ģʽ
	//HVPP_XA_LOAD_IDLE;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����и�ѹģʽ�¶�ȡCHIP��ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadChipID(HVPP_HandleType* HVPPx, UINT8_T* pVal)
{
	UINT8_T i=0;
	//---ʹ���������
	HVPP_ENABLE_CMD_LOAD;
	//---���ض�ȡУ׼�ֺ�ID��Ϣ������
	HVPP_DATABUS_WRITE(HVPPx,HVPP_CMD_READ_ID_AND_CALIBRATION);
	//---��XTALһ�����������ڼ�������
	HVPP_XTAL_PULSE(HVPPx);
	for (i=0;i<3;i++)
	{
		//---���ص�ַ���ֽ�
		HVPP_ENABLE_ADDR_LOAD_LOW;
		//---���͵�ַ
		HVPP_DATABUS_WRITE(HVPPx, i);
		//---��XTALһ�����������ڼ��ص�ַ���ֽ�
		HVPP_XTAL_PULSE(HVPPx);
		//---׼����ȡ���ֽ�����
		HVPP_BS1_OUT_0;
		//---���������л�Ϊ��ȡģʽ
		HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_DIR);
		//---ʹ�ܶ�ȡ
		HVPP_OE_OUT_0;
		//---�ȴ������ȶ�
		HVPP_WAIT_STATE_STABLE;
		//---��ȡ����
		*(pVal++)= HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
		//---��ʹ�ܶ�ȡ
		HVPP_OE_OUT_1;
	}
	//---�ͷ�״̬,Ϊ����ģʽ
	//HVPP_XA_LOAD_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����и�ѹģʽ�¶�ȡCHIP��У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadChipCalibration(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T i = 0;
	//---ʹ���������
	HVPP_ENABLE_CMD_LOAD;
	//---���ض�ȡУ׼�ֺ�ID��Ϣ������
	HVPP_DATABUS_WRITE(HVPPx, HVPP_CMD_READ_ID_AND_CALIBRATION);
	//---��XTALһ�����������ڼ�������
	HVPP_XTAL_PULSE(HVPPx);
	for (i = 0; i < length; i++)
	{
		//---���ص�ַ���ֽ�
		HVPP_ENABLE_ADDR_LOAD_LOW;
		//---���͵�ַ
		HVPP_DATABUS_WRITE(HVPPx, i);
		//---��XTALһ�����������ڼ��ص�ַ���ֽ�
		HVPP_XTAL_PULSE(HVPPx);
		//---׼����ȡ���ֽ�����
		HVPP_BS1_OUT_1;
		//---���������л�Ϊ��ȡģʽ
		HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_DIR);
		//---ʹ�ܶ�ȡ
		HVPP_OE_OUT_0;
		//---�ȴ������ȶ�
		HVPP_WAIT_STATE_STABLE;
		//---��ȡ����
		*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
		//---��ʹ�ܶ�ȡ
		HVPP_OE_OUT_1;
	}
	//---�ͷ�״̬,Ϊ����ģʽ
	//HVPP_XA_LOAD_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����и�ѹģʽ�¶�ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadChipFuse(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	//---ʹ���������
	HVPP_ENABLE_CMD_LOAD;
	//---���ض�ȡ��˿λ����
	HVPP_DATABUS_WRITE(HVPPx, HVPP_CMD_READ_FUSE_AND_LOCK);
	//---��XTALһ�����������ڼ�������
	HVPP_XTAL_PULSE(HVPPx);
	//---׼����ȡ��λ��˿λ
	HVPP_BS_OUT_00;
	//---���������л�Ϊ��ȡģʽ
	HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_DIR);
	//---ʹ�ܶ�ȡ
	HVPP_OE_OUT_0;
	//---�ȴ������ȶ�
	HVPP_WAIT_STATE_STABLE;
	//---��ȡ����
	*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
	//---׼����ȡ��λ��˿λ
	HVPP_BS_OUT_11;
	//---�ȴ������ȶ�
	HVPP_WAIT_STATE_STABLE;
	//---��ȡ����
	*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
	//---��ȡ��˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---׼����ȡ��λ��˿λ
		HVPP_BS_OUT_10;
		//---�ȴ������ȶ�
		HVPP_WAIT_STATE_STABLE;
		//---��ȡ����
		*(pVal) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
	}
	else
	{
		*pVal = 0xFF;
	}
	//---��ʹ�ܶ�ȡ
	HVPP_OE_OUT_1;
	//---�ͷ�״̬,Ϊ����ģʽ
	//HVPP_XA_LOAD_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����и�ѹģʽ�¶�ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadChipLock(HVPP_HandleType* HVPPx, UINT8_T* pVal)
{
	//---ʹ���������
	HVPP_ENABLE_CMD_LOAD;
	//---���ض�ȡ��˿λ����
	HVPP_DATABUS_WRITE(HVPPx, HVPP_CMD_READ_FUSE_AND_LOCK);
	//---��XTALһ�����������ڼ�������
	HVPP_XTAL_PULSE(HVPPx);
	//---׼����ȡ����λ
	HVPP_BS_OUT_01;
	//---���������л�Ϊ��ȡģʽ
	HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_DIR);
	//---ʹ�ܶ�ȡ
	HVPP_OE_OUT_0;
	//---�ȴ������ȶ�
	HVPP_WAIT_STATE_STABLE;
	//---��ȡ����
	*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
	//---��ʹ�ܶ�ȡ
	HVPP_OE_OUT_1;
	//---�ͷ�״̬,Ϊ����ģʽ
	//HVPP_XA_LOAD_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_ReadChipRom(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ���ż��
	if ((length & 0x01) != 0)
	{
		return ERROR_1;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---У������
	if (HVPPx->msgLoadCmd==0)
	{
		//---ʹ���������
		HVPP_ENABLE_CMD_LOAD;
		//---���ض�ȡ��˿λ����
		HVPP_DATABUS_WRITE(HVPPx, HVPP_CMD_READ_ID_AND_CALIBRATION);
		//---��XTALһ�����������ڼ�������
		HVPP_XTAL_PULSE(HVPPx);
	}
	//---��ȡROMҳ��Ϣ���ȵ�λ���λ
	for ( i = 0; i < length; i++)
	{
		//---���ص�ַ���ֽ�
		HVPP_ENABLE_ADDR_LOAD_LOW;
		//---���͵�ַ
		HVPP_DATABUS_WRITE(HVPPx, i+addr);
		//---��XTALһ�����������ڼ��ص�ַ���ֽ�
		HVPP_XTAL_PULSE(HVPPx);
		//---׼����ȡ���ֽ�����
		HVPP_BS1_OUT_0;
		//---���������л�Ϊ��ȡģʽ
		HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_DIR);
		//---ʹ�ܶ�ȡ
		HVPP_OE_OUT_0;
		//---�ȴ������ȶ�
		HVPP_WAIT_STATE_STABLE;
		*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
		//---׼����ȡ���ֽ�����
		HVPP_BS1_OUT_1;
		//---�ȴ������ȶ�
		HVPP_WAIT_STATE_STABLE;
		//---��ȡ����
		*(pVal++) = HVPP_DATABUS_READ(HVPPx, HVPP_DATA_BUS_READ_VAL);
		//---��ʹ�ܶ�ȡ
		HVPP_OE_OUT_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ROMҳ��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_EraseChipRom(HVPP_HandleType* HVPPx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_WriteChipID(HVPP_HandleType* HVPPx,UINT8_T* pVal)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_WriteChipCalibration(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T length)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ,���˳�������ǵ�λ����λ����չλ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_WriteChipFuse(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T HVPP_WriteChipLock(HVPP_HandleType* HVPPx, UINT8_T val)
{
	return OK_0;
}
