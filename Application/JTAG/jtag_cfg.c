#include"jtag_cfg.h"

//===ȫ�ֱ�������
JTAG_HandleType	g_JtagDevice0 = { 0 };
//===ȫ��ָ�����
pJTAG_HandleType	pJtagDevice0 = &g_JtagDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_Device0_RST(UINT8_T rstState)
{
#ifdef JTAG_USE_HV_RESET
	if (rstState == JTAG_RST_TO_GND)
	{
		RST_PORT_TO_GND;
	}
	else if (rstState == JTAG_RST_TO_VCC)
	{
		RST_PORT_TO_VCC;
	}
	else
	{
		RST_PORT_TO_HZ;
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_Device1_RST(UINT8_T rstState)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_Device2_RST(UINT8_T rstState)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Device0_Init(JTAG_HandleType* JTAGx)
{
	//---Ĭ��״̬��test_logic_reset
	JTAGx->msgTapState = TEST_LOGIC_RESET;
#ifdef JTAG_USE_HV_RESET
	JTAGx->msgPortRst = JTAG_Device0_RST;
	//---TCK->PD1---host->device
	JTAGx->msgTCK.msgPort = GPIOD;
	JTAGx->msgTCK.msgBit = LL_GPIO_PIN_1;
	//---TMS->PD0---host->device
	JTAGx->msgTMS.msgPort = GPIOD;
	JTAGx->msgTMS.msgBit = LL_GPIO_PIN_0;
	//---TDI->PD3---host->device
	JTAGx->msgTDI.msgPort = GPIOD;
	JTAGx->msgTDI.msgBit = LL_GPIO_PIN_3;
	//---TDO->PD2---device->host
	JTAGx->msgTDO.msgPort = GPIOD;
	JTAGx->msgTDO.msgBit = LL_GPIO_PIN_2;
#else
	//---TCK->PB3---host->device
	JTAGx->msgTCK.msgPort = GPIOB;
	JTAGx->msgTCK.msgBit = LL_GPIO_PIN_3;
	//---TMS->PC5---host->device
	JTAGx->msgTMS.msgPort = GPIOC;
	JTAGx->msgTMS.msgBit = LL_GPIO_PIN_5;
	//---RST->PC4---host->device
	JTAGx->msgRST.msgPort = GPIOC;
	JTAGx->msgRST.msgBit = LL_GPIO_PIN_4;
	//---TDI->PA7---host->device
	JTAGx->msgTDI.msgPort = GPIOA;
	JTAGx->msgTDI.msgBit = LL_GPIO_PIN_7;
	//---TDO->PA6---device->host
	JTAGx->msgTDO.msgPort = GPIOA;
	JTAGx->msgTDO.msgBit = LL_GPIO_PIN_6;
#endif
	//---OEʹ�õĶ˿�
#ifdef JTAG_USE_lEVEL_SHIFT
	#ifdef JTAG_USE_HV_RESET
		//---OE->PD13---���Ƶ�ƽװ����ʹ��
		JTAGx->msgOE.msgPort = GPIOD;
		JTAGx->msgOE.msgBit = LL_GPIO_PIN_11;
	#else
		 //---OE->PD13---���Ƶ�ƽװ����ʹ��
		JTAGx->msgOE.msgPort = GPIOD;
		JTAGx->msgOE.msgBit = LL_GPIO_PIN_13;
	#endif
#endif
	JTAGx->msgPluseWidth = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Device1_Init(JTAG_HandleType* JTAGx)
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
UINT8_T JTAG_Device2_Init(JTAG_HandleType* JTAGx)
{
	JTAGx->msgTapState = TEST_LOGIC_RESET;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_GPIO_Init(JTAG_HandleType* JTAGx)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(JTAGx->msgTDI.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(JTAGx->msgTDO.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(JTAGx->msgTMS.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(JTAGx->msgTCK.msgPort, PERIPHERAL_CLOCK_ENABLE);
	//---JTAG��OEʹ�ܶ�
#ifdef JTAG_USE_lEVEL_SHIFT
	GPIOTask_Clock(JTAGx->msgOE.msgPort, PERIPHERAL_CLOCK_ENABLE);
#endif
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---TDI---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTDI.msgBit;
	LL_GPIO_Init(JTAGx->msgTDI.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_0(JTAGx->msgTDI);
	//---TCK---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTCK.msgBit;
	LL_GPIO_Init(JTAGx->msgTCK.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_0(JTAGx->msgTCK);
	//---TMS---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgTMS.msgBit;
	LL_GPIO_Init(JTAGx->msgTMS.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTMS);

	//---RST������
#ifdef JTAG_USE_HV_RESET
	//---RST---���Ϊ��
	JTAGx->msgPortRst(JTAG_RST_TO_VCC);
#else
	//---ʹ�ܶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(JTAGx->msgRST.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---RST---���Ϊ��
	GPIO_InitStruct.Pin = JTAGx->msgRST.msgBit;
	LL_GPIO_Init(JTAGx->msgRST.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgRST);
#endif
#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE---���Ϊ�ͣ�����Ч
	GPIO_InitStruct.Pin = JTAGx->msgOE.msgBit;
	LL_GPIO_Init(JTAGx->msgOE.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_0(JTAGx->msgOE);
#endif
	//---TDO---���룬����ʹ��
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ����ģʽ
	GPIO_InitStruct.Pin = JTAGx->msgTDO.msgBit;
	LL_GPIO_Init(JTAGx->msgTDO.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTDO);
	//---�˿ڳ�ʼ����
	JTAGx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_GPIO_DeInit(JTAG_HandleType* JTAGx)
{
	//---RST�˿�����
#ifdef JTAG_USE_HV_RESET
	//---������Դ
	JTAGx->msgPortRst(JTAG_RST_TO_VCC);
#else
	JTAG_GPIO_OUT_1(JTAGx->msgRST);
#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---����״̬Ϊ����ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;												//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif

	//---TDI---��������
	GPIO_InitStruct.Pin = JTAGx->msgTDI.msgBit;
	LL_GPIO_Init(JTAGx->msgTDI.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTDI);
	//---TCK---��������
	GPIO_InitStruct.Pin = JTAGx->msgTCK.msgBit;
	LL_GPIO_Init(JTAGx->msgTCK.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTCK);
	//---TMS---��������
	GPIO_InitStruct.Pin = JTAGx->msgTMS.msgBit;
	LL_GPIO_Init(JTAGx->msgTMS.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTMS);
	//---TDO---��������
	GPIO_InitStruct.Pin = JTAGx->msgTDO.msgBit;
	LL_GPIO_Init(JTAGx->msgTDO.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgTDO);

#ifdef JTAG_USE_lEVEL_SHIFT
	//---OE---���Ϊ�ͣ�����Ч
	JTAG_GPIO_OUT_1(JTAGx->msgOE);
#endif
	//---RST�˿�����
#ifdef JTAG_USE_HV_RESET
	//---�ͷ�RST�˿ڣ�����Ϊ����̬
	JTAGx->msgPortRst(JTAG_RST_TO_HZ);
#else
	//---RST---��������
	GPIO_InitStruct.Pin = JTAGx->msgRST.msgBit;
	LL_GPIO_Init(JTAGx->msgRST.msgPort, &GPIO_InitStruct);
	JTAG_GPIO_OUT_1(JTAGx->msgRST);
#endif
	//---�˿�δ��ʼ����
	JTAGx->msgInit = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_Init(JTAG_HandleType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ�õ���Դ
	if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_ONE))
	{
		JTAG_Device0_Init(JTAGx);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_TWO))
	{
		JTAG_Device1_Init(JTAGx);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_THREE))
	{
		JTAG_Device2_Init(JTAGx);
	}
	else
	{
		return ERROR_1;
	}
	JTAG_GPIO_Init(JTAGx);
	//---ע��ms����ʱ����
	if (pFuncDelayms != NULL)
	{
		JTAGx->pMsgDelayms = pFuncDelayms;
	}
	else
	{
		JTAGx->pMsgDelayms = DelayTask_us;
	}
	//---ע��us��ʱ����
	if (pFuncDelayus != NULL)
	{
		JTAGx->pMsgDelayus = pFuncDelayus;
	}
	else
	{
		JTAGx->pMsgDelayus = DelayTask_us;
	}
	//---ע��δ���
	if (pFuncTimerTick != NULL)
	{
		JTAGx->pMsgTimeTick = pFuncTimerTick;
	}
	else
	{
		JTAGx->pMsgTimeTick = SysTickTask_GetTick;;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�TMSΪ�ߣ�TCK��5�����壬�ܹ�ֱ�ӻص�TestlogicReset״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunTestlogicReset(JTAG_HandleType* JTAGx)
{
	UINT8_T i = 0;
	JTAG_GPIO_OUT_1(JTAGx->msgTMS);
	for (i = 0; i < 5; i++)
	{
		JTAG_TCK_PULSE(JTAGx);
	}
	JTAGx->msgTapState = TEST_LOGIC_RESET;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ڿ���״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunTestIdle(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			//---capture dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			break;
	}
	//---run_test_idle
	JTAG_TMS_OUT_0(JTAGx);
	JTAGx->msgTapState = RUN_TEST_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������SelectDRScan״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunSelectDRScan(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);;
			break;
	}
	//---У���Ƿ񱣳�ʱ�Ӳ���
	if (JTAGx->msgTapState != SELECT_DR_SCAN)
	{
		//---select_dr_scan
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = SELECT_DR_SCAN;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Capture DR
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunCaptureDR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != CAPTURE_DR)
	{
		//---capture_dr
		JTAG_TMS_OUT_0(JTAGx);
	}
	JTAGx->msgTapState = CAPTURE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ShiftDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunShiftDR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_DR:
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	JTAGx->msgTapState = SHIFT_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Exit1DR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit1DR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_DR:
			break;
		case SHIFT_DR:
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_DR:
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != EXIT1_DR)
	{
		//---exit1_dr
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = EXIT1_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunPauseDR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			break;
		case EXIT2_DR:
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != PAUSE_DR)
	{
		//---pause_dr
		JTAG_TMS_OUT_0(JTAGx);
	}
	JTAGx->msgTapState = PAUSE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������Exit2DR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit2DR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_DR:
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_DR:
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_GPIO_OUT_1(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---capture_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_GPIO_OUT_0(JTAGx->msgTMS);
			JTAG_TCK_PULSE(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != EXIT2_DR)
	{
		//---exit2_dr
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = EXIT2_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������UpdateDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunUpdateDR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_dr
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != UPDATE_DR)
	{
		//---update_dr
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = UPDATE_DR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������SelectiRScan״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunSelectIRScan(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			break;
		case SELECT_DR_SCAN:
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			break;
		case SELECT_IR_SCAN:
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	//---select_dr_scan
	JTAG_TMS_OUT_1(JTAGx);
	//---У���Ƿ񱣳�ʱ�Ӳ���
	if (JTAGx->msgTapState != SELECT_IR_SCAN)
	{
		//---select_ir_scan
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = SELECT_IR_SCAN;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������CaptureIR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunCaptureIR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_IR_SCAN:
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---update_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != CAPTURE_IR)
	{
		//---capture_ir
		JTAG_TMS_OUT_0(JTAGx);
	}
	JTAGx->msgTapState = CAPTURE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ShiftDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunShiftIR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_IR:
			//---pasuse_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	JTAGx->msgTapState = SHIFT_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit1IR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_IR:
			break;
		case SHIFT_IR:
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != EXIT1_IR)
	{
		//---exit1_ir
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = EXIT1_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunPauseIR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			break;
		case EXIT2_IR:
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---shift_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	//---pause_ir
	JTAG_TMS_OUT_0(JTAGx);
	JTAGx->msgTapState = PAUSE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunExit2IR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case EXIT1_IR:
			//---pasuse_ir
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			break;
		case UPDATE_IR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			//---pause_dr
			JTAG_TMS_OUT_0(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != EXIT2_IR)
	{
		//---exit2_ir
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = EXIT2_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������PauseDR״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RunUpdateIR(JTAG_HandleType* JTAGx)
{
	switch (JTAGx->msgTapState)
	{
		case RUN_TEST_IDLE:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_DR_SCAN:
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_DR:
			//---exit1_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case PAUSE_DR:
			//---exit2_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_DR:
			//---update_dr
			JTAG_TMS_OUT_1(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case UPDATE_DR:
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SELECT_IR_SCAN:
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case CAPTURE_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case SHIFT_IR:
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT1_IR:
			break;
		case PAUSE_IR:
			//---exit2_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
		case EXIT2_IR:
			break;
		case UPDATE_IR:
			break;
		case TEST_LOGIC_RESET:
		default:
			JTAG_RunTestlogicReset(JTAGx);
			//---run_test_idle
			JTAG_TMS_OUT_0(JTAGx);
			//---select_dr_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---select_ir_scan
			JTAG_TMS_OUT_1(JTAGx);
			//---capture_ir
			JTAG_TMS_OUT_0(JTAGx);
			//---exit1_ir
			JTAG_TMS_OUT_1(JTAGx);
			break;
	}
	if (JTAGx->msgTapState != UPDATE_IR)
	{
		//---update_ir
		JTAG_TMS_OUT_1(JTAGx);
	}
	JTAGx->msgTapState = UPDATE_IR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����IR����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ShiftIR_BIT(JTAG_HandleType* JTAGx, UINT8_T irCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT8_T i = 0;
	UINT8_T _return = OK_0;
	//---capture_ir
	JTAG_RunCaptureIR(JTAGx);
	//---��������
	for (i = 0; i < bitCount; i++)
	{
		//---ʱ������
		JTAG_TCK_PULSE(JTAGx);
		//---��������
		((irCmd & 0x01) != 0) ? JTAG_GPIO_OUT_1(JTAGx->msgTDI) : JTAG_GPIO_OUT_0(JTAGx->msgTDI);
		//---��λ����
		irCmd >>= 1;
		//---��ȡ���
		_return |= ((JTAG_GPIO_STATE(JTAGx->msgTDO) != 0) ? (1 << i) : 0);
	}
	JTAGx->msgTapState = SHIFT_IR;
	//---У���Ƿ������ڿ���״̬
	if (isRunTestIdle)
	{
		//---run_test_idle
		JTAG_RunTestIdle(JTAGx);
	}
	//---select_dr_scan
	JTAG_RunSelectDRScan(JTAGx);
	return ((_return == 0x01) ? OK_0 : ERROR_1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T JTAG_ShiftDR_BIT(JTAG_HandleType* JTAGx, UINT32_T drCmd, UINT8_T bitCount, UINT8_T isRunTestIdle)
{
	UINT32_T i = 0;
	UINT32_T _return = 0;
	//---capture_dr�������ݼĴ���״̬
	JTAG_RunCaptureDR(JTAGx);
	for (i = 0; i < bitCount; i++)
	{
		//---ʱ������
		JTAG_TCK_PULSE(JTAGx);
		//---��������
		((drCmd & 0x01) != 0) ? JTAG_GPIO_OUT_1(JTAGx->msgTDI) : JTAG_GPIO_OUT_0(JTAGx->msgTDI);
		//---��λ����
		drCmd >>= 1;
		//---��ȡ���
		_return |= ((JTAG_GPIO_STATE(JTAGx->msgTDO) != 0) ? (1 << i) : 0);
	}
	JTAGx->msgTapState = SHIFT_DR;
	//---У���Ƿ������ڿ���״̬
	if (isRunTestIdle != 0)
	{
		//---run_test_idle
		JTAG_RunTestIdle(JTAGx);
	}
	//---select_dr_scan
	JTAG_RunSelectDRScan(JTAGx);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��²������TAP��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TAPReset(JTAG_HandleType* JTAGx, UINT8_T bit)
{
	JTAG_ShiftIR_BIT(JTAGx, AVR_RESET, 4, 1);
	JTAG_ShiftDR_BIT(JTAGx, bit, 1, 1);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��²������TAP��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TAPClear(JTAG_HandleType* JTAGx)
{
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PRIVATEE3, 4, 0);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---��д����
	JTAG_ShiftDR_BIT(JTAGx, 0x0D, 5, 0);
	//---��д����
	JTAG_ShiftDR_BIT(JTAGx, 0, 16, 0);
	//---����Reset �Ĵ���
	JTAG_TAPReset(JTAGx, 1);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��²������TAP��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TAPPreEnter(JTAG_HandleType* JTAGx)
{
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_ENABLE, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---��ȡ����
	return ((JTAG_ShiftDR_BIT(JTAGx, 0xA370, 16, 1) == 0) ? OK_0 : ERROR_1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TapNoOperationCommand(JTAG_HandleType* JTAGx)
{
	UINT16_T _return = OK_0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���Ϳ�����
	JTAG_ShiftDR_BIT(JTAGx, 0x2300, 15, 1);
	//---���Ϳ�����
	_return = JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	//---У������
	if (_return != 0x2300)
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��²������TAP��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_TAPExit(JTAG_HandleType* JTAGx)
{
	UINT16_T _return = JTAG_TapNoOperationCommand(JTAGx);
	//---У�����
	if (_return != OK_0)
	{
		return ERROR_1;
	}
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_ENABLE, 4, 0);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	_return = JTAG_ShiftDR_BIT(JTAGx, 0x0000, 16, 0);
	//---����Reset �Ĵ���
	JTAG_TAPReset(JTAGx, 0);
	//---���ö˿�δ����ģʽ
	JTAG_GPIO_DeInit(JTAGx);
	//---У������
	if (_return != 0xA370)
	{
		return ERROR_2;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_EnterProg(JTAG_HandleType* JTAGx)
{
	UINT8_T _return=OK_0;
	if (JTAGx->msgInit == 0)
	{
		//---��ʼ���˿�
		JTAG_GPIO_Init(JTAGx);
	}
	else
	{
	#ifdef JTAG_USE_lEVEL_SHIFT
		//---OE---���Ϊ�ͣ�����Ч
		JTAG_GPIO_OUT_1(JTAGx->msgOE);
	#endif
	}
	//---����ǰ״̬����֤���ģʽ�ܹ�����
	JTAG_TAPClear(JTAGx);
	//---׼��������ģʽ
	_return = JTAG_TAPPreEnter(JTAGx);
	//---У�������
	if (_return == OK_0)
	{
		JTAGx->msgState = JTAG_PROG_PREPARE;
	}
	else
	{
		JTAGx->msgState = JTAG_PROG_NONE;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ExitProg(JTAG_HandleType* JTAGx)
{
	//---���Eepromҳ���ģʽ
	JTAGx->msgEepromPageMode = 0;
	//---������ݻ����������
	JTAGx->msgPageWordIndex = 0;
	//---���״̬Ϊ����ģʽ
	JTAGx->msgState = JTAG_PROG_NONE;
	//---��λ��ǩ
	JTAGx->msgJtagCmd = 0;
	//---�Ƴ�ע��ļ�غ���
	JTAG_RemoveWatch(JTAGx);
	//---ִ���˳�����
	return JTAG_TAPExit(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_WatchTask(JTAG_HandleType* JTAGx)
{
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (JTAGx->msgState != JTAG_PROG_NONE)
	{
		//---��ȡ��ǰʱ�����
		nowTime = JTAGx->pMsgTimeTick();
		//---����ʱ����
		if (JTAGx->msgRecordTick > nowTime)
		{
			cnt = (0xFFFFFFFF - JTAGx->msgRecordTick + nowTime);
		}
		else
		{
			cnt = nowTime - JTAGx->msgRecordTick;
		}
		//---����Ƿ�����ʱ�¼�
		if (cnt > JTAGx->msgIntervalTime)
		{
			JTAG_ExitProg(JTAGx);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸1�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_AddWatchDevice0(void)
{
	JTAG_WatchTask(JTAG_TASK_ONE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸2�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_AddWatchDevice1(void)
{
	JTAG_WatchTask(JTAG_TASK_TWO);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����豸3�ļ�غ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void JTAG_AddWatchDevice2(void)
{
	JTAG_WatchTask(JTAG_TASK_THREE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RemoveWatch(JTAG_HandleType* JTAGx)
{
	//---ʹ�õ�JTAG�Ķ˿�
	if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_ONE))
	{
		SysTick_DeleteTickTask(JTAG_AddWatchDevice0);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_TWO))
	{
		SysTick_DeleteTickTask(JTAG_AddWatchDevice1);
	}
	else if ((JTAGx != NULL) && (JTAGx == JTAG_TASK_THREE))
	{
		SysTick_DeleteTickTask(JTAG_AddWatchDevice2);
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_RefreshWatch(JTAG_HandleType* JTAGx)
{
	//---������ѵ���Ϊ���ֵ����λ��ms
	JTAGx->msgIntervalTime = JTAG_STATE_TIME_OUT_MS;
	//---ˢ�¼�¼ʱ��
	JTAGx->msgRecordTick = JTAGx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_AddWatch(JTAG_HandleType* JTAGx)
{
	UINT8_T _return = OK_0;
	if (JTAGx != NULL)
	{
		//---ˢ��ʱ��
		_return = JTAG_RefreshWatch(JTAGx);
		//---ʹ�õ�JTAG�Ķ˿�,��ע����Ӧ��������
		if (JTAGx == JTAG_TASK_ONE)
		{
			SysTickTask_CreateTickTask(JTAG_AddWatchDevice0);
		}
		else if (JTAGx == JTAG_TASK_TWO)
		{
			SysTickTask_CreateTickTask(JTAG_AddWatchDevice1);
		}
		else if (JTAGx == JTAG_TASK_THREE)
		{
			SysTickTask_CreateTickTask(JTAG_AddWatchDevice2);
		}
		else
		{
			_return = ERROR_1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_SetIntervalTime(JTAG_HandleType* JTAGx, UINT16_T intervalTime)
{
	//---������ѵ���ʱ�䣬��λ��ms
	JTAGx->msgIntervalTime = intervalTime;
	//---ˢ�¼�¼ʱ��
	JTAGx->msgRecordTick = JTAGx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�׼��������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T JTAG_GetIntervalTime(JTAG_HandleType* JTAGx)
{
	return JTAGx->msgIntervalTime;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ���ѵ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WaitPollChipComplete(JTAG_HandleType* JTAGx, UINT16_T cmd)
{
	UINT8_T _return = OK_0;
	UINT32_T tempID = 0;
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT64_T cnt = 0;
	oldTime=((JTAGx->pMsgTimeTick != NULL)? JTAGx->pMsgTimeTick():0);
	while (1)
	{
		tempID = JTAG_ShiftDR_BIT(JTAGx, cmd, 15, 0);
		//---У�鷵��ֵ
		if ((tempID & 0x0200) != 0)
		{
			_return = OK_0;
			break;
		}
		else
		{
			if (JTAGx->pMsgTimeTick != NULL)
			{
				//---��ǰʱ��
				nowTime = JTAGx->pMsgTimeTick();
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
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_EraseChip(JTAG_HandleType* JTAGx)
{
	UINT8_T i = 0;
	//---ʹ��JTAGָ��
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ز�������
	JTAG_ShiftDR_BIT(JTAGx, 0x2380, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3180, 15, 0);
	JTAG_ShiftDR_BIT(JTAGx, 0x3380, 15, 0);
	JTAG_ShiftDR_BIT(JTAGx, 0x3380, 15, 0);
	//---�ȴ��������
	return JTAG_WaitPollChipComplete(JTAGx, 0x3380);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡJTAGID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadIDChip(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T i = 0;
	UINT32_T tempID = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, IDCODE, 4, 0);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---��ȡ����
	tempID = JTAG_ShiftDR_BIT(JTAGx, 0, 32, 1);
	//---���԰汾��Ϣ
	tempID &= 0x0FFFFFFF;
	//---У�黺����
	if (pVal != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			pVal[i] = (UINT8_T)tempID;
			tempID >>= 8;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡJTAGID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipID(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T i = 0;
	UINT32_T tempID = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ض�ȡ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2308, 15, 1);
	//---��ѵ��ȡChipID
	for (i = 0; i < 3; i++)
	{
		//---���ص�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 + i, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3200, 15, 0);
		//---��ȡ���
		tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 0);
		*(pVal++) = (UINT8_T)(tempID);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��Ϣ������ChipID��JtagID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChip(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	JTAG_ReadIDChip(JTAGx, pVal);
	return JTAG_ReadChipID(JTAGx, pVal + 4);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡУ׼����Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipCalibration(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T i = 0;
	UINT32_T tempID = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ض�ȡ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2308, 15, 1);
	//---��ȡָ����С������
	for (i = 0; i < length; i++)
	{
		//---���ص�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 + i, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3600, 15, 0);
		//---��ȡ���
		tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 0);
		*(pVal++) = (UINT8_T)(tempID);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��˿λ��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipFuse(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T i = 0;
	UINT32_T tempID = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ض�ȡ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2304, 15, 1);
	//---��ȡ��˿λ��λֵ
	JTAG_ShiftDR_BIT(JTAGx, 0x3200, 15, 1);
	//---��ȡ��˿λ��λֵ
	tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	*(pVal++) = (UINT8_T)tempID;
	//---��ȡ��˿λ��λֵ
	JTAG_ShiftDR_BIT(JTAGx, 0x3E00, 15, 1);
	//---��ȡ��˿λ��λֵ
	tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3F00, 15, 1);
	*(pVal++) = (UINT8_T)tempID;
	//---У����չλ
	if (isNeedExternFuse != 0)
	{
		//---��ȡ��˿λ��չλֵ
		JTAG_ShiftDR_BIT(JTAGx, 0x3A00, 15, 1);
		//---��ȡ��˿λ��չλֵ
		tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3B00, 15, 1);
		*(pVal++) = (UINT8_T)tempID;
	}
	else
	{
		*pVal = 0xFF;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����λ��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipLock(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT32_T tempID = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ض�ȡ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2304, 15, 1);
	//---��ȡ����λֵ
	JTAG_ShiftDR_BIT(JTAGx, 0x3600, 15, 1);
	//---��ȡ����λֵ
	tempID = JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	*(pVal++) = ((UINT8_T)tempID) | 0xFC;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡROMҳ��Ϣ
//////�������:	pVal---���ݻ�����
//////			addr---���ݵ�ַ����ַ���ֵ�ַ
//////			length---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ��ȣ��ڲ�������ֳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipRom(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T i = 0;
	UINT32_T tempROM = 0;
	//---�ж����ݳ����Ƿ���ż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---�ж��Ƿ��ѽ�����������
	if ((JTAGx->msgJtagCmd == 0) || (JTAGx->msgState != JTAG_PROG_READ_ROM))
	{
		//---��������
		JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
		//---׼����������
		JTAG_RunCaptureDR(JTAGx);
		//---���ض�ȡ����
		JTAG_ShiftDR_BIT(JTAGx, 0x2308, 15, 1);
		//---��λ��ǩ
		JTAGx->msgJtagCmd = 1;
		JTAGx->msgState = JTAG_PROG_READ_ROM;
	}
	//---��ȡROMҳ��Ϣ
	for (i = 0; i < length; i++)
	{
		//---��ȡ���ֽ�����,���ص�ַ
		JTAG_ShiftDR_BIT(JTAGx, (0x0300 | (i + addr)), 15, 1);
		//---��ȡ���
		JTAG_ShiftDR_BIT(JTAGx, 0x3200, 15, 0);
		//---��ȡ���ֽ�����
		tempROM = JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 0);
		*(pVal++) = (UINT8_T)(tempROM);
		//---��ȡ���ֽ����ݣ����ص�ַ
		JTAG_ShiftDR_BIT(JTAGx, (0x0300 | (i + addr)), 15, 1);
		//---��ȡ���
		JTAG_ShiftDR_BIT(JTAGx, 0x3600, 15, 0);
		//---��ȡ���ֽ�����
		tempROM = JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 0);
		*(pVal++) = (UINT8_T)(tempROM);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WriteChipFuse(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = OK_0;
	UINT32_T tempFuse = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ر����˿λ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2340, 15, 1);
	//---���ص�λ����
	JTAG_ShiftDR_BIT(JTAGx, 0x1300 | *(pVal++), 15, 1);
	//---д��˿λ��λ
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3100, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	//---�ȴ���̵�λ��˿λ����
	_return = JTAG_WaitPollChipComplete(JTAGx, 0x3300);
	if (_return != OK_0)
	{
		return ERROR_1;
	}
	//---���ظ�λ����
	JTAG_ShiftDR_BIT(JTAGx, 0x1300 | *(pVal++), 15, 1);
	//---д��˿λ��λ
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3500, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	//---�ȴ���̸�λ��˿λ����
	_return = JTAG_WaitPollChipComplete(JTAGx, 0x3700);
	if (_return != OK_0)
	{
		return ERROR_2;
	}
	//---У������չ��˿λ
	if (isNeedExternFuse)
	{
		//---������չλ����
		JTAG_ShiftDR_BIT(JTAGx, 0x1300 | *pVal, 15, 1);
		//---д��˿λ��λ
		JTAG_ShiftDR_BIT(JTAGx, 0x3B00, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3900, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3B00, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3B00, 15, 1);
		//---�ȴ������չλ��˿λ����
		_return = JTAG_WaitPollChipComplete(JTAGx, 0x3700);
		if (_return != OK_0)
		{
			return ERROR_3;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WriteChipLock(JTAG_HandleType* JTAGx, UINT8_T lockVal)
{
	UINT32_T tempLock = 0;
	//---��������
	JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
	//---׼����������
	JTAG_RunCaptureDR(JTAGx);
	//---���ر�̼���λ����
	JTAG_ShiftDR_BIT(JTAGx, 0x2320, 15, 1);
	//---���ؼ���λ����
	JTAG_ShiftDR_BIT(JTAGx, 0x13C0 | lockVal, 15, 1);
	//---д����λ
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3100, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	//---�ȴ���̼���λ����
	return ((JTAG_WaitPollChipComplete(JTAGx, 0x3300) == OK_0) ? OK_0 : ERROR_5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:  pVal	---���ݻ�����
//////			highAddr---���ݵ�ַ�ĸ��ֽڣ���ַ���ֽڵ�ַ
//////			lowAddr ---���ݵ�ַ�ĵ��ֽڣ���ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipEepromAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT32_T tempeEPROM = 0;
	UINT16_T i = 0;
	//---У���Ƿ����������
	if ((JTAGx->msgJtagCmd == 0) || (JTAGx->msgState != JTAG_PROG_READ_EEPROM))
	{
		//---��������
		JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
		//---׼����������
		JTAG_RunCaptureDR(JTAGx);
		//---���ض�ȡ����
		JTAG_ShiftDR_BIT(JTAGx, 0x2303, 15, 1);
		JTAGx->msgJtagCmd = 1;
		JTAGx->msgState = JTAG_PROG_READ_EEPROM;
	}
	//---��ȡEEPROM��Ϣ
	for (i = 0; i < length; i++)
	{
		//---���ظߵ�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0700 | highAddr, 15, 1);
		//---���ص͵�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 | lowAddr, 15, 1);
		//---׼����ȡ����
		JTAG_ShiftDR_BIT(JTAGx, 0x3300 | lowAddr, 15, 0);
		JTAG_ShiftDR_BIT(JTAGx, 0x3200, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 0);
		*(pVal++) = (UINT8_T)(tempeEPROM);
		//---��λ��ַƫ��
		lowAddr++;
		//---У���λ��ַƫ��
		if (lowAddr == 0)
		{
			//---��λ��ַƫ��
			highAddr++;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:  pVal	---���ݻ�����
//////			addr	---���ݵ�ַ����ַ���ֽڵ�ַ
//////			length	---��ȡ���ݵĳ��ȣ����ݳ������ֽڳ���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipEepromLongAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT16_T addr, UINT16_T length)
{
	return JTAG_ReadChipEepromAddr(JTAGx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳ���ģʽ���������ݵ�EEPROM�ı�̻�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_UpdateChipEepromPage(JTAG_HandleType* JTAGx, UINT8_T highAddr, UINT8_T lowAddr, UINT8_T* pVal)
{
	UINT32_T tempVal = 0;
	UINT8_T i = 0;
	//---У���Ƿ����Flashд��ģʽ
	if ((JTAGx->msgJtagCmd == 0) || (JTAGx->msgState != JTAG_PROG_WRITE_EEPROM))
	{
		//---��������
		JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
		//---׼����������
		JTAG_RunCaptureDR(JTAGx);
		//---���EEPROM
		JTAG_ShiftDR_BIT(JTAGx, 0x2311, 15, 1);
		JTAGx->msgJtagCmd = 1;
		JTAGx->msgState = JTAG_PROG_WRITE_EEPROM;
	}
	//---���ظ�λ��ַ
	JTAG_ShiftDR_BIT(JTAGx, 0x0700 | highAddr, 15, 1);
	//---��仺����
	for (i = 0; i < JTAGx->msgEerpomPerPageByteSize; i++)
	{
		//---���ص�λ��ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 | lowAddr, 15, 1);
		//---��������
		JTAG_ShiftDR_BIT(JTAGx, 0x1300 | *(pVal++), 15, 1);
		//---��������
		JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x7700, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
		lowAddr++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳ���ģʽ��ִ��ҳд�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_UpdateChipEeprom(JTAG_HandleType* JTAGx)
{
	//---ʹ��ҳд��
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3100, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3300, 15, 1);
	//---�ȴ�ҳд�����
	return JTAG_WaitPollChipComplete(JTAGx, 0x3300);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳ���ģʽ������EEPROM�ı��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WriteChipEepromPage(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	UINT8_T _return = OK_0;
	UINT32_T pageAddr = 0;
	UINT16_T i = 0;
	//---��鵱ǰ���ģʽ
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---�����̵�ҳ��
		pageNum /= (JTAGx->msgEerpomPerPageByteSize);
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---�����ַ������Eeprom��˵���ֵ�ַҲ���ֽڵ�ַ
		pageAddr = highAddr;
		pageAddr = (pageAddr << 8) + lowAddr;
		//---��ҳ���Eeprom����
		for (i = 0; i < pageNum; i++)
		{
			//---������ݻ���
			_return = JTAG_UpdateChipEepromPage(JTAGx, (UINT8_T)(pageAddr >> 8), (UINT8_T)(pageAddr), pVal);
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_2);
			//---ִ��ҳд�����
			_return = JTAG_UpdateChipEeprom(JTAGx);
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_3);
			//---У��ҳ��̵Ľ��
			if (_return != OK_0)
			{
				//---�����˳����
				_return = ERROR_4;
				break;
			}
			else
			{
				//---�����ַƫ��
				pageAddr += JTAGx->msgEerpomPerPageByteSize;
				//---���ݵ�ַƫ��
				pVal += JTAGx->msgEerpomPerPageByteSize;
			}
		}
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�JTAG���EEPROM��JTAGֻ֧��ҳ��̣���֧���ֽڱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WriteChipEeprom(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	//---���ָ��λ�õ�Eeprom����,���ģʽҳģʽ
	return JTAG_WriteChipEepromPage(JTAGx, pVal, highAddr, lowAddr, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipFlashAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT32_T tempeFlash = 0;
	UINT16_T i = 0;
	if ((JTAGx->msgJtagCmd == 0) || (JTAGx->msgState != JTAG_PROG_READ_FLASH))
	{
		//---��������
		JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
		//---׼����������
		JTAG_RunCaptureDR(JTAGx);
		//---�����˿λ
		JTAG_ShiftDR_BIT(JTAGx, 0x2302, 15, 1);
		JTAGx->msgJtagCmd = 1;
		JTAGx->msgState = JTAG_PROG_READ_FLASH;
	}
	//---�ж��Ƿ������չλ��ַ
	if (externAddr != 0)
	{
		//---������չλ��ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0B00 | externAddr, 15, 1);
	}
	//---��ȡROMҳ��Ϣ
	for (i = 0; i < length; i++)
	{
		//---���ظߵ�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0700 | highAddr, 15, 1);
		//---���ص͵�ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 | lowAddr, 15, 1);
		//---׼����ȡ����
		JTAG_ShiftDR_BIT(JTAGx, 0x3200, 15, 1);
		//---��ȡ��λ����
		tempeFlash = JTAG_ShiftDR_BIT(JTAGx, 0x3600, 15, 0);
		*(pVal++) = (UINT8_T)tempeFlash;
		//---��ȡ��λ����
		tempeFlash = JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 0);
		*(pVal++) = (UINT8_T)(tempeFlash);
		//---��λ��ַƫ��
		lowAddr++;
		if (lowAddr == 0)
		{
			//---��λ��ַƫ��
			highAddr++;
			//---�ж��Ƿ�����չλ�仯
			if (highAddr == 0)
			{
				//---��չλ��ַƫ��
				externAddr++;
				//---������չλ��ַ
				JTAG_ShiftDR_BIT(JTAGx, 0x0B00 | externAddr, 15, 1);
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ַ��ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_ReadChipFlashLongAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT32_T addr, UINT16_T length)
{
	return  JTAG_ReadChipFlashAddr(JTAGx, pVal, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳ���ģʽ���������ݵ�FLASH�ı�̻�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_UpdateChipFlashPage(JTAG_HandleType* JTAGx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT8_T* pVal, UINT16_T length)
{
	UINT32_T tempVal = 0;
	UINT8_T i = 0;
	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0x00)
	{
		return ERROR_2;
	}
	//---����λ���㵱����2����
	length >>= 1;
	//---У���Ƿ����Flashд��ģʽ
	if ((JTAGx->msgJtagCmd == 0) || (JTAGx->msgState != JTAG_PROG_WRITE_FLASH))
	{
		//---��������
		JTAG_ShiftIR_BIT(JTAGx, PROG_COMMANDS, 4, 1);
		//---׼����������
		JTAG_RunCaptureDR(JTAGx);
		//---�����˿λ
		JTAG_ShiftDR_BIT(JTAGx, 0x2310, 15, 1);
		JTAGx->msgJtagCmd = 1;
		JTAGx->msgState = JTAG_PROG_WRITE_FLASH;
	}
	//---�����Ƿ���Ҫ���ظߵ�ַ�͵͵�ַ
	if (JTAGx->msgPageWordIndex == 0)
	{
		if (externAddr != 0)
		{
			//---������չλ��ַ
			JTAG_ShiftDR_BIT(JTAGx, 0x0B00 | externAddr, 15, 1);
		}
		//---���ظ�λ��ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0700 | externAddr, 15, 1);
	}
	//---��仺����
	for (i = 0; i < length; i++)
	{
		//---���ص�λ��ַ
		JTAG_ShiftDR_BIT(JTAGx, 0x0300 | lowAddr, 15, 1);
		//---���ص�λ����
		JTAG_ShiftDR_BIT(JTAGx, 0x1300 | *(pVal++), 15, 1);
		//---���ظ�λ����
		JTAG_ShiftDR_BIT(JTAGx, 0x1700 | *(pVal++), 15, 1);
		//---��������
		JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x7700, 15, 1);
		JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
		lowAddr++;
	}
	//---���»���������ţ�
	JTAGx->msgPageWordIndex += length;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳ���ģʽ��ִ��ҳд�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_UpdateChipFlash(JTAG_HandleType* JTAGx)
{
	//---ʹ��ҳд��
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3500, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	JTAG_ShiftDR_BIT(JTAGx, 0x3700, 15, 1);
	//---�ȴ�ҳд�����
	return JTAG_WaitPollChipComplete(JTAGx, 0x3700);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ����ָ��������д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_WriteChipFlashPage(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT32_T pageAddr = 0;
	//---��鵱ǰ���ģʽ
	if (JTAGx->msgState == 0)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---������ݻ���
		_return = JTAG_UpdateChipFlashPage(JTAGx, externAddr, highAddr, lowAddr, pVal, length);
		//---���㷵�ؽ��
		_return = (_return == OK_0 ? OK_0 : ERROR_1);
		//---������������ִ������д�����
		if ((_return == OK_0) && (JTAGx->msgPageWordIndex == JTAGx->msgFlashPerPageWordSize))
		{
			//---ִ��дҳ����
			_return = JTAG_UpdateChipFlash(JTAGx);
			//---���ݻ�������
			JTAGx->msgPageWordIndex = 0;
			//---���㷵�ؽ��
			_return = (_return == OK_0 ? OK_0 : ERROR_2);
		}
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Flash�����Ƿ�Ϊ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_CheckChipFlashEmpty(JTAG_HandleType* JTAGx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	UINT8_T _return = OK_0;
	UINT16_T length = 0;
	UINT16_T pageNum = 0;
	UINT16_T i = 0;
	UINT32_T addr = 0;
	//---����ÿҳ�ֽ���
	length = pageByteSizeH;
	length = (length << 8) + pageByteSizeL;
	//---����ҳ��
	pageNum = pageNumH;
	pageNum = (pageNum << 8) + pageNumL;
	//---�����ڴ�
	UINT8_T* pFlashBuffer = (UINT8_T*)MyMalloc(length);
	//---�жϻ���ռ������Ƿ�ɹ�
	if (pFlashBuffer == NULL)
	{
		_return = ERROR_1;
		goto GoToExit;
	}
	for (i = 0; i < pageNum; i++)
	{
		_return = JTAG_ReadChipFlashLongAddr(JTAGx, pFlashBuffer, addr, length);
		if (_return != OK_0)
		{
			_return = ERROR_2;
			goto GoToExit;
		}
		//---У�������Ƿ�ȫ��Ϊ0xFF
		_return = CompareByte(pFlashBuffer, 0xFF, length);
		if (_return != OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
		//---�����ַƫ��
		addr += (length >> 1);
	}
	//---�˳����
GoToExit:
	//---�ͷŻ���ռ�
	MyFree(pFlashBuffer);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Eeprom�����Ƿ�Ϊ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_CheckChipFlashEmptyLong(JTAG_HandleType* JTAGx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return JTAG_CheckChipFlashEmpty(JTAGx, (UINT8_T)(pageByteSize >> 8), (UINT8_T)(pageByteSize), (UINT8_T)(pageNum >> 8), (UINT8_T)(pageNum));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У��Eeprom�����Ƿ�Ϊ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_CheckChipEepromEmpty(JTAG_HandleType* JTAGx, UINT8_T byteSize, UINT8_T num)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT16_T addr = 0;
	//---�����ڴ�
	UINT8_T* pEepromBuffer = (UINT8_T*)MyMalloc(byteSize);
	//---�жϻ���ռ������Ƿ�ɹ�
	if (pEepromBuffer == NULL)
	{
		_return = ERROR_1;
		goto GoToExit;
	}
	for (i = 0; i < num; i++)
	{
		_return = JTAG_ReadChipEepromLongAddr(JTAGx, pEepromBuffer, addr, byteSize);
		if (_return != OK_0)
		{
			_return = ERROR_2;
			goto GoToExit;
		}
		//---У�������Ƿ�ȫ��Ϊ0xFF
		_return = CompareByte(pEepromBuffer, 0xFF, byteSize);
		if (_return != OK_0)
		{
			_return = ERROR_3;
			goto GoToExit;
		}
		//---�����ַƫ��
		addr += byteSize;
	}
	//---�˳����
GoToExit:
	//---�ͷŻ���ռ�
	MyFree(pEepromBuffer);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����������Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAG_SetConfigInfo(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	//---Flashÿҳ����
	JTAGx->msgFlashPerPageWordSize = *(pVal++);
	JTAGx->msgFlashPerPageWordSize = (JTAGx->msgFlashPerPageWordSize << 8) + *(pVal++);
	//---Eepromÿҳ�ֽ���
	JTAGx->msgEerpomPerPageByteSize = *(pVal++);
	JTAGx->msgEerpomPerPageByteSize = (JTAGx->msgEerpomPerPageByteSize << 8) + *(pVal++);
	//---Eeprom�Ƿ�֧��ҳ���ģʽ
	JTAGx->msgEepromPageMode = *(pVal++);
	return OK_0;
}