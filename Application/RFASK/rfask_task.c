#include "rfask_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
//void RFASKTask_Init(RFASK_HandlerType *rfask)
//{
//	RFASKLib_Init(rfask);
//	RFASKLib_SetFreqCurrentPointCmd(&rfask->msgFreqCurrentPointOne, CMD_RFASK_CMD1_FREQ_CURRENT_POINT_ONE);
//	RFASKLib_SetFreqCurrentPointCmd(&rfask->msgFreqCurrentPointTwo, CMD_RFASK_CMD1_FREQ_CURRENT_POINT_TWO);
//}

void RFASKTask_Init(RFASK_HandlerType* rfask, AT24CXX_HandlerType* AT24CXXx)
{
	//AT24CXXTask_I2C_EraseChip(AT24CXXx);
	//---���������ĳ�ʼ��
	RFASKLib_Init(rfask);
	//---eeprom�б���Ĳ���
	if (AT24CXXx!=NULL)
	{
		RFASK_EEPROMInit(rfask, AT24CXXx);
	}
	//---��������
	RFASKLib_SetFreqCurrentPointCmd(&rfask->msgFreqCurrentPointOne, CMD_RFASK_CMD1_FREQ_CURRENT_POINT_ONE);
	RFASKLib_SetFreqCurrentPointCmd(&rfask->msgFreqCurrentPointTwo, CMD_RFASK_CMD1_FREQ_CURRENT_POINT_TWO);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T RFASKTask_CalcXTAL(RFASK_HandlerType *rfask, UINT32_T rfX100MHz)
{
	return RFASKLib_CalcXTAL(rfask, rfX100MHz);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_SetDeviceType(RFASK_HandlerType *rfask, UINT8_T deviceType)
{
	return RFASKLib_SetDeviceType(rfask, deviceType);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T RFASKTask_GetDeviceType(RFASK_HandlerType *rfask)
{
	return RFASKLib_GetDeviceType(rfask);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T RFASKTask_SetClockFreq(RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x, UINT32_T rfX100MHz)
{
	UINT8_T _return = OK_0;
	//---��ȡ�趨�ľ���ֵ
	UINT32_T freqTemp = RFASKLib_CalcXTAL(rfask, rfX100MHz);
	////---����ʱ��оƬWM8510
	//return WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, freqTemp);
	//---20190504,�����豸��ʱ���������У׼����
	_return= WM8510Task_I2C_SetFreqHzWithAllFreqRegAndCalibrateFreqKHzOutPut(WM8510x, freqTemp);
	if (_return!=OK_0)
	{
		//---��λWM8510
		WM8510Task_I2C_Reset(WM8510x);
		//---�ٴ��������ʱ�Ӳ�У׼�����ʱ������쳣�������MCU�������λ
		_return= WM8510Task_I2C_SetFreqHzWithAllFreqRegAndCalibrateFreqKHzOutPut(WM8510x, freqTemp);
		if (_return!=OK_0)
		{
			//---�����λ�������λ�Ѿ���֤�����Գɹ�
			SOFT_RESET();
			////---Ӳ����λ,�ȴ����Ź�����
			//while (1);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� WM8510��Ƶ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
//UINT8_T  RFASKTask_WM8510Task(USART_HandlerType* USARTx, WM8510_HandlerType* WM8510x)
UINT8_T  RFASKTask_WM8510Task(USART_HandlerType*USARTx, WM8510_HandlerType *WM8510x, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;
	UINT32_T freqTemp = 0;

	//---���ݷ��ͱ�ͷ
	USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);

	//---ִ����������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex])
	{
		//---����WM8510�����Ƶ��
		case CMD_RFASK_CMD2_SET_WM8510:
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//---����WM8510�����Ƶ��
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������Ƶ��
			_return = WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, freqTemp);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---��ȡWM8510���õ����Ƶ��
		case CMD_RFASK_CMD2_GET_WM8510:
			//---�ⲿ����ģʽ��������ļ���
			TimerTask_CalcFreq_Task(1);
			//---��ȡ��ǰ�����Ƶ��KHz,���ӻ�ȡ�����ʱ��Ϊ10ms������ʱ�任ȡ����
			freqTemp = (UINT32_T)TimerTask_GetFreqKHz(); // (UINT32_T)(TimerTask_GetFreqKHz()/10);
			//---��ȡ��ǰ�����Ƶ��Hz
			freqTemp *= 1000;
			USARTTask_RealTime_AddSize(USARTx, 7);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---��������䵽������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 0));
			break;
			//---��λWM8510�����
		case CMD_RFASK_CMD2_RESET_WM8510:
			WM8510Task_I2C_Reset(pWm8510Device0);
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---ʱ�����ͨ��1�Ŀ���
		case CMD_RFASK_CMD2_CHANNELA_WM8510:
			//---Aͨ��Ƶ�����
			if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0x00)
			{
				CLKA_FREQ_ON;
			}
			else
			{
				CLKA_FREQ_OFF;
			}
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---ʱ�����ͨ��2�Ŀ���
		case CMD_RFASK_CMD2_CHANNELB_WM8510:
			//---Bͨ��Ƶ�����
			if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0x00)
			{
				CLKB_FREQ_ON;
			}
			else
			{
				CLKB_FREQ_OFF;
			}
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---ʱ�����ͨ��3�Ŀ���
		case CMD_RFASK_CMD2_CHANNELC_WM8510:
			//---Cͨ��Ƶ�����
			if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0x00)
			{
				CLKC_FREQ_ON;
			}
			else
			{
				CLKC_FREQ_OFF;
			}
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---ʱ�����ͨ��4�Ŀ���
		case CMD_RFASK_CMD2_CHANNELD_WM8510:
			//---Dͨ��Ƶ�����
			if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0x00)
			{
				CLKD_FREQ_ON;
			}
			else
			{
				CLKD_FREQ_OFF;
			}
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---ʱ�����ȫ��ͨ���Ŀ���
		case CMD_RFASK_CMD2_CHANNELS_WM8510:
			//---����ͨ��Ƶ�����
			if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex] != 0x00)
			{
				CLKA_FREQ_ON;
				CLKB_FREQ_ON;
				CLKC_FREQ_ON;
				CLKD_FREQ_ON;
			}
			else
			{
				CLKA_FREQ_OFF;
				CLKB_FREQ_OFF;
				CLKC_FREQ_OFF;
				CLKD_FREQ_OFF;
			}
			USARTTask_RealTime_AddSize(USARTx, 3);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
		default:
			_return = ERROR_1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����Ԥ��Ƶ�ʵĲ�������
//////////////////////////////////////////////////////////////////////////////
//UINT8_T RFASKTask_YSELTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x)
UINT8_T RFASKTask_YSELTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;
	UINT32_T freqTemp = 0;
	//---���ݷ��ͱ�ͷ
	USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
	//---ִ����������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex])
	{
		//---����Ƶ�ʵ�1
		case CMD_RFASK_CMD2_YSEL1_FREQ_SET:
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel1 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL1_ADDR_X1, rfask->msgFreqX100MHzYSel1, 4);
			break;
			//---����Ƶ�ʵ�2
		case CMD_RFASK_CMD2_YSEL2_FREQ_SET:
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel2 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL2_ADDR_X1, rfask->msgFreqX100MHzYSel2, 4);
			break;
			//---����Ƶ�ʵ�3
		case CMD_RFASK_CMD2_YSEL3_FREQ_SET:
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel3 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL3_ADDR_X1, rfask->msgFreqX100MHzYSel3, 4);
			break;
			//---����Ƶ�ʵ�4
		case CMD_RFASK_CMD2_YSEL4_FREQ_SET:
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel4 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL4_ADDR_X1, rfask->msgFreqX100MHzYSel4, 4);
			break;
			//---��ȡƵ�ʵ�1
		case CMD_RFASK_CMD2_YSEL1_FREQ_GET:
			freqTemp = rfask->msgFreqX100MHzYSel1;
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 4));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ص�һ��Ĭ��Ƶ��1
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			break;
			//---��ȡƵ�ʵ�2
		case CMD_RFASK_CMD2_YSEL2_FREQ_GET:
			freqTemp = rfask->msgFreqX100MHzYSel2;
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 4));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ص�һ��Ĭ��Ƶ��1
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			break;
			//---��ȡƵ�ʵ�3
		case CMD_RFASK_CMD2_YSEL3_FREQ_GET:
			freqTemp = rfask->msgFreqX100MHzYSel3;
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 4));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ص�һ��Ĭ��Ƶ��1
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			break;
			//---��ȡƵ�ʵ�4
		case CMD_RFASK_CMD2_YSEL4_FREQ_GET:
			freqTemp = rfask->msgFreqX100MHzYSel4;
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 4));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ص�һ��Ĭ��Ƶ��1
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			break;
			//---����ȫ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL_FREQ_SET:
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			
			//---����Ƶ�ʵ�1
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel1 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL1_ADDR_X1, rfask->msgFreqX100MHzYSel1, 4);

			//---����Ƶ�ʵ�2
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 5];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 6];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 7];
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel2 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL2_ADDR_X1, rfask->msgFreqX100MHzYSel2, 4);

			//---����Ƶ�ʵ�3
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 8];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 9];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 10];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 11];
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel3 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL3_ADDR_X1, rfask->msgFreqX100MHzYSel3, 4);

			//---����Ƶ�ʵ�4
			freqTemp = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 12];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 13];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 14];
			freqTemp = (freqTemp << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 15];
			//---���浱ǰ�趨��ֵ
			rfask->msgFreqX100MHzYSel4 = freqTemp;
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_FREQ_YSEL4_ADDR_X1, rfask->msgFreqX100MHzYSel4, 4);
			
			break;
			//---��ȡȫ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL_FREQ_GET:
			freqTemp = rfask->msgFreqX100MHzYSel1;
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 16));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ص�һ��Ĭ��Ƶ��1
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			//---���ص�һ��Ĭ��Ƶ��2
			freqTemp = rfask->msgFreqX100MHzYSel2;
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			//---���ص�һ��Ĭ��Ƶ��3
			freqTemp = rfask->msgFreqX100MHzYSel3;
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			//---���ص�һ��Ĭ��Ƶ��2
			freqTemp = rfask->msgFreqX100MHzYSel4;
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 24));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 16));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(freqTemp));
			break;
			//---���������һ��Ԥ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL1_FREQ_OUT:
			//---�������Ƶ��
			_return = WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, RFASKTask_CalcXTAL(rfask, rfask->msgFreqX100MHzYSel1));
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---��������ڶ���Ԥ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL2_FREQ_OUT:
			//---�������Ƶ��
			_return = WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, RFASKTask_CalcXTAL(rfask, rfask->msgFreqX100MHzYSel2));
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---�������������Ԥ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL3_FREQ_OUT:
			//---�������Ƶ��
			_return = WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, RFASKTask_CalcXTAL(rfask, rfask->msgFreqX100MHzYSel3));
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
			//---����������ĸ�Ԥ��Ƶ�ʵ�
		case CMD_RFASK_CMD2_YSEL4_FREQ_OUT:
			//---�������Ƶ��
			_return = WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, RFASKTask_CalcXTAL(rfask, rfask->msgFreqX100MHzYSel4));
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, _return);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			break;
		default:
			_return = ERROR_1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡƵ�ʵ���ɨ�輤���SITE��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_ActivateSites(RFASK_HandlerType *rfask, UINT8_T activateSites)
{
	return RFASKLib_ActivateSites(rfask, activateSites);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_SitesCurrent(RFASK_HandlerType *rfask)
{
	UINT8_T i = 0;
	UINT64_T sitePower = 0;
	//---��ȡADC�Ĳ������
	ADCTask_RFASKTask_GetADC(&rfask->msgSiteADC[0], FREQ_CURRENT_MAX_SITE);
	//---װ�����Ϊ����ֵ
	for (i = 0; i < FREQ_CURRENT_MAX_SITE; i++)
	{
		//---�������
		sitePower = rfask->msgSiteADC[i];

		//---�������
		sitePower *= FREQ_CURRENT_ADC_VREF_MV;
		sitePower *= 10000;
		sitePower /= rfask->msgSampleX100Res;
		sitePower /= rfask->msgAmpTimes;

		//---�����ת���ɵ���ֵ
		rfask->msgSiteCurrent[i] = (UINT16_T)((sitePower >> 12) + 1);
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
UINT8_T  RFASKTask_SetFreqCurrentPointCmd(FREQ_CURRENT_HandlerType *rfaskFreqCurrent, UINT8_T cmd)
{
	return RFASKLib_SetFreqCurrentPointCmd(rfaskFreqCurrent, cmd);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� Ƶ�ʵ���ɨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_FreqCurrentTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, UINT8_T activateSites)
{
	UINT8_T _return = OK_0;
	//---����Ƶ�ʵ���ɨ��ļ����SITE
	RFASKTask_ActivateSites(rfask, activateSites);
	//---����Ƶ�ʵ��������̴���
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� Ƶ�ʵ���ɨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
//UINT8_T  RFASKTask_FreqCurrentPointOneTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x)
UINT8_T  RFASKTask_FreqCurrentPointOneTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;

	//---ִ����������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex])
	{
		//---��ȡƵ�ʵ���ɨ���Ƶ�ʲ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 11);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz >> 24));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz >> 16));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz >> 8));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz));
			//---����Ƶ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz >> 8));
			//---����Ƶ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz));
			//---�ɼ���ĸ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgFreqPointNum >> 8));
			//---�ɼ���ĸ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgFreqPointNum));
			break;
			//---����Ƶ�ʵ���ɨ���Ƶ�ʲ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---������ʼƵ��
			rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_START_FREQ_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz, 4);

			//---���ò���Ƶ��
			rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 5];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_STEP_FREQ_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz, 2);

			//---���òɼ���ĸ���
			rfask->msgFreqCurrentPointOne.msgFreqPointNum = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 6];
			rfask->msgFreqCurrentPointOne.msgFreqPointNum = (rfask->msgFreqCurrentPointOne.msgFreqPointNum << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 7];
			//---���Ʋ�����Ĵ�С�����ֵ��Ӱ���ϱ���λ����ʱ�����ݻ������Ĵ�С
			if (rfask->msgFreqCurrentPointOne.msgFreqPointNum > FREQ_CURRENT_FREQ_POINT_MAX_NUM)
			{
				rfask->msgFreqCurrentPointOne.msgFreqPointNum = FREQ_CURRENT_FREQ_POINT_MAX_NUM;
			}
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_POINT_NUM_ADDR_X1, rfask->msgFreqCurrentPointOne.msgFreqPointNum, 2);
			
			//---����ֹͣƵ��
			rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz = rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz;
			rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz *= rfask->msgFreqCurrentPointOne.msgFreqPointNum;
			rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz += rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz;
			break;
			//---��ȡƵ�ʵ���ɨ��ĵ�������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 2 + 2 + 2 + 2 + 2 + 2 + 2));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---��ȡ��ʼ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA >> 8));
			//---��ȡ��ʼ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA));
			//---��ȡ��ʼ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA >> 8));
			//---��ȡ��ʼ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA));
			//---ADC����ĵ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPointNum >> 8));
			//---ADC����ĵ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPointNum));
			//---ADC�ϸ�����ֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPassMax >> 8));
			//---ADC�ϸ�����ֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPassMax));
			//---ADC�ϸ����Сֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPassMin >> 8));
			//---ADC�ϸ����Сֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgADCPassMin));
			//---��ȡ��ֹ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA >> 8));
			//---��ȡ��ֹ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA));
			//---��ȡ��ֹ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA >> 8));
			//---��ȡ��ֹ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA));
			break;
			//---����Ƶ�ʵ���ɨ��ĵ�������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---������ʼ��������
			rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---������ʼ��������
			rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA, 2);

			//---������ʼ����С����
			rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			//---������ʼ����С����
			rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_START_MIN_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA, 2);

			//---ADC����ĵ���
			rfask->msgFreqCurrentPointOne.msgADCPointNum = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			//---ADC����ĵ���
			rfask->msgFreqCurrentPointOne.msgADCPointNum = (rfask->msgFreqCurrentPointOne.msgADCPointNum << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 5];
			//---�ж������ǹ�����
			if (rfask->msgFreqCurrentPointOne.msgADCPointNum > FREQ_CURRENT_HISTORY_MAX_SIZE)
			{
				rfask->msgFreqCurrentPointOne.msgADCPointNum = FREQ_CURRENT_HISTORY_MAX_SIZE;
			}
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_ADC_POINT_NUM_ADDR_X1, rfask->msgFreqCurrentPointOne.msgADCPointNum, 2);

			//---ADC�ϸ�����ֵ
			rfask->msgFreqCurrentPointOne.msgADCPassMax = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 6];
			//---ADC�ϸ�����ֵ
			rfask->msgFreqCurrentPointOne.msgADCPassMax = (rfask->msgFreqCurrentPointOne.msgADCPassMax << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 7];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_ADC_PASS_MAX_ADDR_X1, rfask->msgFreqCurrentPointOne.msgADCPassMax, 2);

			//---ADC�ϸ����Сֵ
			rfask->msgFreqCurrentPointOne.msgADCPassMin = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 8];
			//---ADC�ϸ����Сֵ
			rfask->msgFreqCurrentPointOne.msgADCPassMin = (rfask->msgFreqCurrentPointOne.msgADCPassMin << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 9];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_ADC_PASS_MIN_ADDR_X1, rfask->msgFreqCurrentPointOne.msgADCPassMin, 2);	

			//---���ý�ֹ��������
			rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 10];
			//---���ý�ֹ��������
			rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 11];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_STOP_MAX_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA, 2);

			//---���ý�ֹ����С����
			rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 12];
			//---���ý�ֹ����С����
			rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 13];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTONE_STOP_MIN_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA, 2);
			
			break;
			//---ִ��Ƶ�ʵ���ɨ������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_DO:
			_return = RFASKTask_FreqCurrentScan(USARTx, rfask, &rfask->msgFreqCurrentPointOne, WM8510x);
			break;
		default:
			_return = ERROR_1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� Ƶ�ʵ���ɨ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
//UINT8_T  RFASKTask_FreqCurrentPointTwoTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x)
UINT8_T  RFASKTask_FreqCurrentPointTwoTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;

	//---ִ����������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex])
	{
		//---��ȡƵ�ʵ���ɨ��Ĳ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 11);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz >> 24));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz >> 16));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz >> 8));
			//---��ȡ��ʼƵ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz));
			//---����Ƶ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz >> 8));
			//---����Ƶ��
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz));
			//---�ɼ���ĸ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgFreqPointNum >> 8));
			//---�ɼ���ĸ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgFreqPointNum));
			break;
			//---����Ƶ�ʵ���ɨ��Ĳ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			
			//---������ʼƵ��
			rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			//---������ʼƵ��
			rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_START_FREQ_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz, 4);

			//---���ò���Ƶ��
			rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 5];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_STEP_FREQ_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz, 2);

			//---���òɼ���ĸ���
			rfask->msgFreqCurrentPointTwo.msgFreqPointNum = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 6];
			rfask->msgFreqCurrentPointTwo.msgFreqPointNum = (rfask->msgFreqCurrentPointTwo.msgFreqPointNum << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 7];
			//---���Ʋ�����Ĵ�С�����ֵ��Ӱ���ϱ���λ����ʱ�����ݻ������Ĵ�С
			if (rfask->msgFreqCurrentPointTwo.msgFreqPointNum > FREQ_CURRENT_FREQ_POINT_MAX_NUM)
			{
				rfask->msgFreqCurrentPointTwo.msgFreqPointNum = FREQ_CURRENT_FREQ_POINT_MAX_NUM;
			}
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_POINT_NUM_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgFreqPointNum, 2);

			//---����ֹͣƵ��
			rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz = rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz;
			rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz *= rfask->msgFreqCurrentPointTwo.msgFreqPointNum;
			rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz += rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz;
			break;
			//---��ȡƵ�ʵ���ɨ��ĵ�������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, (3 + 2 + 2 + 2 + 2 + 2 + 2 + 2));
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---��ȡ��ʼ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA >> 8));
			//---��ȡ��ʼ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA));
			//---��ȡ��ʼ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA >> 8));
			//---��ȡ��ʼ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA));
			//---ADC����ĵ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPointNum >> 8));
			//---ADC����ĵ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPointNum));
			//---ADC�ϸ�����ֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPassMax >> 8));
			//---ADC�ϸ�����ֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPassMax));
			//---ADC�ϸ����Сֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPassMin >> 8));
			//---ADC�ϸ����Сֵ
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgADCPassMin));
			//---��ȡ��ֹ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA >> 8));
			//---��ȡ��ֹ��������
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA));
			//---��ȡ��ֹ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA >> 8));
			//---��ȡ��ֹ����С����
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA));
			break;
			//---����Ƶ�ʵ���ɨ��ĵ�������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---������ʼ��������
			rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---������ʼ��������
			rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA, 2);

			//---������ʼ����С����
			rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			//---������ʼ����С����
			rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_START_MIN_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA, 2);

			//---ADC����ĵ���
			rfask->msgFreqCurrentPointTwo.msgADCPointNum = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			//---ADC����ĵ���
			rfask->msgFreqCurrentPointTwo.msgADCPointNum = (rfask->msgFreqCurrentPointTwo.msgADCPointNum << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 5];
			//---�ж������ǹ�����
			if (rfask->msgFreqCurrentPointTwo.msgADCPointNum > FREQ_CURRENT_HISTORY_MAX_SIZE)
			{
				rfask->msgFreqCurrentPointTwo.msgADCPointNum = FREQ_CURRENT_HISTORY_MAX_SIZE;
			}
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_ADC_POINT_NUM_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgADCPointNum, 2);

			//---ADC�ϸ�����ֵ
			rfask->msgFreqCurrentPointTwo.msgADCPassMax = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 6];
			//---ADC�ϸ�����ֵ
			rfask->msgFreqCurrentPointTwo.msgADCPassMax = (rfask->msgFreqCurrentPointTwo.msgADCPassMax << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 7];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_ADC_PASS_MAX_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgADCPassMax, 2);

			//---ADC�ϸ����Сֵ
			rfask->msgFreqCurrentPointTwo.msgADCPassMin = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 8];
			//---ADC�ϸ����Сֵ
			rfask->msgFreqCurrentPointTwo.msgADCPassMin = (rfask->msgFreqCurrentPointTwo.msgADCPassMin << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 9];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_ADC_PASS_MIN_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgADCPassMin, 2);

			//---���ý�ֹ��������
			rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 10];
			//---���ý�ֹ��������
			rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 11];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_STOP_MAX_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA, 2);

			//---���ý�ֹ����С����
			rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 12];
			//---���ý�ֹ����С����
			rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 13];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_POINTTWO_STOP_MIN_CURRENT_ADDR_X1, rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA, 2);
			break;
			//---ִ��Ƶ�ʵ���ɨ������
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_DO:
			_return = RFASKTask_FreqCurrentScan(USARTx, rfask, &rfask->msgFreqCurrentPointTwo, WM8510x);
			break;
		default:
			_return = ERROR_1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �ϵ�4���룬����1ma
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASKTask_FreqCurrentScan(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, FREQ_CURRENT_HandlerType *rfaskFreqCurrent, WM8510_HandlerType *WM8510x)
{
	UINT8_T  siteNum = 0;
	UINT8_T  adcPointNum = 0;
	UINT16_T detaCurrentX10uA = 0;
	UINT16_T freqPointNum = 0;
	//---���������
	UINT8_T   currentPointNum[FREQ_CURRENT_MAX_SITE] = {0};
	//---�������ֵ
	UINT16_T  currentPointCurrent[FREQ_CURRENT_MAX_SITE] = {0};
	//---������ȵĵ�
	UINT8_T   currentEqualMinPointNum[FREQ_CURRENT_MAX_SITE] = {0};
	UINT8_T   currentEqualMaxPointNum[FREQ_CURRENT_MAX_SITE] = {0};
	//---�����SITE���ϴεĵ���ֵ
	UINT16_T	siteOldCurrent[FREQ_CURRENT_MAX_SITE] = {0};
	//---SITE������ȵ�ĸ���
	UINT8_T		siteCurrentEquaPointNum[FREQ_CURRENT_MAX_SITE] = { 0 };
	//---��ʷ���ݵİ���
	UINT16_T *pMsgActivateSiteCurrentHistory;
	UINT32_T freqX100MHz = rfaskFreqCurrent->msgStartFreqX100MHz;
	UINT32_T xtalHz = 0;
	//---ֹͣ���룬����ʹ�õ��ж����ȼ��Ƚϵĸߣ�������Ϊ�ж����ȼ������⣬����Ƶ�ʵ���ɨ���쳣������
	DecodeTask_STOP();
	//---��λ���Ź�
	WDT_RESET();
	//---��ʼ���ϸ�/ʧЧ�жϽ������---��ʼ��Ϊ�ϸ�ģʽ
	//memset(rfask->msgSitePass, 0, FREQ_CURRENT_MAX_SITE);
	for (freqPointNum = 0; freqPointNum < FREQ_CURRENT_MAX_SITE; freqPointNum++)
	{
		rfask->msgSitePass[freqPointNum] = 0;
		currentPointNum[freqPointNum] = 0;
		currentPointCurrent[freqPointNum] = 0;
		currentEqualMinPointNum[freqPointNum] = 0;
		currentEqualMaxPointNum[freqPointNum] = 0;
	}
	//---�������ݵı�ͷ
	USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
	//---�������ݴ�С
	USARTTask_RealTime_AddSize(USARTx, 4 + ((rfaskFreqCurrent->msgFreqPointNum + 1) * 2)*FREQ_CURRENT_MAX_SITE);
	//---���ص�һ������
	USARTTask_RealTime_AddByte(USARTx, rfaskFreqCurrent->msgCMD);
	//--�õ����ؽ��
	USARTTask_RealTime_AddByte(USARTx, 0);
	//---���صĶ�������
	USARTTask_RealTime_AddByte(USARTx, CMD_RFASK_CMD1_FREQ_CURRENT_POINT_DO);
	freqPointNum = rfaskFreqCurrent->msgStartFreqX100MHz;
	freqPointNum /= 2000;
	freqPointNum = (freqPointNum << 3) + FREQ_CURRENT_MAX_SITE;
	//---����SITE��
	USARTTask_RealTime_AddByte(USARTx, (UINT8_T)freqPointNum);
	freqPointNum = 0;
	//---��ʱ�����
	CLK_FREQ_ON;
	//---�رյ�Դ
	DPS_POWER_HZ;
	//---����Ƶ�ʵ�����ɨ��
	for (freqPointNum = 0; freqPointNum < rfaskFreqCurrent->msgFreqPointNum; freqPointNum++)
	{
		//---�ر�ʱ�����
		// CLK_FREQ_OFF;
		//---�رյ�Դ
		DPS_POWER_OFF;
		//---����ʱ��Ƶ�ʣ�������Ƶ����RFƵ�ʣ���Ҫ����ɾ���Ƶ��
		xtalHz = RFASK_CalcXTAL(rfask, freqX100MHz);
		//---���Ŀ��Ƶ��
		WM8510Task_I2C_SetFreqHzWithAllFreqReg(WM8510x, xtalHz);
		DelayTask_us(100);
		//---��һ�ε�Ƶ�����
		freqX100MHz += rfaskFreqCurrent->msgStepFreqX100MHz;
		//---�򿪵�Դ
		DPS_POWER_ON;
		//---��ʱ�����
		// CLK_FREQ_ON;
		//if	(rfaskFreqCurrent->msgStepFreqX100MHz<300)
		//{
		//
		//	//---�ȴ��ϵ��ȶ�
		//	DelayTask_ms(8);
		//}
		//else
		//{
		//
		//	//---�ȴ��ϵ��ȶ�
		//	DelayTask_ms(6);
		//}
		//-- - �ȴ��ϵ��ȶ�
		DelayTask_ms(5);		
		//---��ʼn���㣬��ȴ�һ��
		if (freqPointNum <3)
		{
			DelayTask_ms(1);
		}
		//---ǰ10���㣬��ȼ����ϵ��ȶ�
		//if (freqPointNum <10)
		//{
		//	//---��ȡÿ��SITE�ĵ�����ADC�Ĳ������
		//	RFASKTask_SitesCurrent(rfask);
		//	DelayTask_ms(10);
		//}
		//---��ȡÿ��SITE�ĵ�����ADC�Ĳ������
		RFASKTask_SitesCurrent(rfask);
		//---��ѵ�жϸ���SITE�Ľ��
		for (siteNum = 0; siteNum < FREQ_CURRENT_MAX_SITE; siteNum++)
		{
			//---��ʼ��
			if (freqPointNum == 0)
			{
				if ((rfask->msgSiteCurrent[siteNum] < rfaskFreqCurrent->msgStartMinCurrentX100mA) || (rfask->msgSiteCurrent[siteNum] > (rfaskFreqCurrent->msgStartMaxCurrentX100mA + 200)))
				{
					//---�жϲ��ϸ�ԭ���ǵ�һ����ĵ��������Ĵ󣬱���С��С
					rfask->msgSitePass[siteNum] = 1;
				}
			}
			//---��ֹ��
			if ((rfask->msgSitePass[siteNum] == 0) && (freqPointNum == (rfaskFreqCurrent->msgFreqPointNum - 1)))
			{
				if ((rfask->msgSiteCurrent[siteNum] < rfaskFreqCurrent->msgStopMinCurrentX100mA) || (rfask->msgSiteCurrent[siteNum] > rfaskFreqCurrent->msgStopMaxCurrentX100mA))
				{
					//---�жϲ��ϸ�ԭ�������һ����ĵ��������Ĵ󣬱���С��С
					rfask->msgSitePass[siteNum] = 1 + freqPointNum;
				}
			}
			//---�жϺϸ�����
			if (rfask->msgSitePass[siteNum] == 0)
			{
				if (currentPointNum[siteNum] == 0)
				{
					//---��ȡ��ǰ����ֵ
					currentPointCurrent[siteNum] = rfask->msgSiteCurrent[siteNum];
				}
				currentPointNum[siteNum]++;				
				//---��������������ȵ�״̬�߼��жϿ�ʼ
				//---�жϵ����Ƿ����仯
				if (siteOldCurrent[siteNum]!= rfask->msgSiteCurrent[siteNum])
				{
					siteCurrentEquaPointNum[siteNum] = 0;
				}
				else
				{
					siteCurrentEquaPointNum[siteNum] ++;
					//---���������ĵ���ֵ�������仯
					//if (siteCurrentEquaPointNum[siteNum] > 3)					
					if (siteCurrentEquaPointNum[siteNum] > RFASK_FREQ_CURRENT_CONT_EQUAL_POINT_MAX_NUM)
					{
						//---�жϲ��ϸ�ԭ���Ǹõ�ĵ���֮ǰ�ļ�����С���߲�ֵ���趨�ϸ�������СֵС��������趨�ĺϸ����������ֵ��
						rfask->msgSitePass[siteNum] = 1 + freqPointNum;
					}
				}
				//---����SITE�ĵ���ֵ
				siteOldCurrent[siteNum] = rfask->msgSiteCurrent[siteNum];
				//---��������������ȵ�״̬�߼��жϽ���
				//---�ϸ�������Ƶ�ʵ��ֵ�ļ���
				if (freqPointNum < rfaskFreqCurrent->msgADCPointNum)
				{
					//---�����ʷ����
					rfask->msgSiteCurrentHistory[siteNum][freqPointNum] = rfask->msgSiteCurrent[siteNum];
				}
				else
				{
					//---��ʷ����ǰ��
					pMsgActivateSiteCurrentHistory = rfask->msgSiteCurrentHistory[siteNum];
					for (adcPointNum = 0; adcPointNum < (rfaskFreqCurrent->msgADCPointNum - 1); adcPointNum++)
					{
						*pMsgActivateSiteCurrentHistory = *(pMsgActivateSiteCurrentHistory + 1);
						pMsgActivateSiteCurrentHistory++;
					}
					//---���һ���������Ϊ��ǰ�ɼ�ֵ
					*pMsgActivateSiteCurrentHistory = rfask->msgSiteCurrent[siteNum];
					//---�ⲿ�ֲ�ֵ�ļ��㣬�������´���Ŀǰ���ֵ�����ƫ���С
					detaCurrentX10uA = 1;//---��������ֵ��ȵ�����
					if (rfask->msgSiteCurrent[siteNum] > rfask->msgSiteCurrentHistory[siteNum][0])
					{
						detaCurrentX10uA = rfask->msgSiteCurrent[siteNum] - rfask->msgSiteCurrentHistory[siteNum][0];
					}
					else if (rfask->msgSiteCurrent[siteNum] < rfask->msgSiteCurrentHistory[siteNum][0])
					{
						detaCurrentX10uA = rfask->msgSiteCurrentHistory[siteNum][0] - rfask->msgSiteCurrent[siteNum];
					}
					////---���������ֵ
					//detaVal = (UINT16_T)(rfask->msgActivateSiteCurrent[siteNum] - rfask->msgActivateSiteCurrentHistory[siteNum][0]);
					//---�жϲɼ���ϸ�����
					//if ((rfask->msgSiteCurrent[siteNum] < rfask->msgSiteCurrentHistory[siteNum][0]) || (detaCurrentX10uA < rfaskFreqCurrent->msgADCPassMin) || (adcPointNum > rfaskFreqCurrent->msgADCPassMax))
					//if((detaCurrentX10uA < rfaskFreqCurrent->msgADCPassMin) || (detaCurrentX10uA > rfaskFreqCurrent->msgADCPassMax))					
					//---С����Сֵ
					if (detaCurrentX10uA < rfaskFreqCurrent->msgADCPassMin)
					{
						currentEqualMinPointNum[siteNum]++;
						//---����������ȵĵ���
						//if (currentEqualMinPointNum[siteNum] > 3)
						if (currentEqualMinPointNum[siteNum] > RFASK_FREQ_CURRENT_CONT_EQUAL_POINT_MAX_NUM)
						{
							//---�жϲ��ϸ�ԭ���Ǹõ�ĵ���֮ǰ�ļ�����С���߲�ֵ���趨�ϸ�������СֵС��������趨�ĺϸ����������ֵ��
							rfask->msgSitePass[siteNum] = 1 + freqPointNum;
						}
					}
					//---�������ֵ
					else if (detaCurrentX10uA > rfaskFreqCurrent->msgADCPassMax)
					{
						currentEqualMaxPointNum[siteNum]++;
						//---����������ȵĵ���
						//if (currentEqualMaxPointNum[siteNum] > 3)
						if (currentEqualMaxPointNum[siteNum] > RFASK_FREQ_CURRENT_CONT_EQUAL_POINT_MAX_NUM)
						{
							//---�жϲ��ϸ�ԭ���Ǹõ�ĵ���֮ǰ�ļ�����С���߲�ֵ���趨�ϸ�������СֵС��������趨�ĺϸ����������ֵ��
							rfask->msgSitePass[siteNum] = 1 + freqPointNum;
						}
					}

					//---������֮��
					else
					{
						currentEqualMinPointNum[siteNum] = 0;
						currentEqualMaxPointNum[siteNum] = 0;
					}
					//---��21����һ��Ҫ�ȵ�һ�����30uA
					if (currentPointNum[siteNum] >= 20)
					{
						currentPointNum[siteNum] = 0;
						//---���������ֵ
						//detaCurrentX10uA = (UINT16_T)(rfask->msgSiteCurrent[siteNum] - currentPointCurrent[siteNum]);
						detaCurrentX10uA = ABS_SUB(rfask->msgSiteCurrent[siteNum],currentPointCurrent[siteNum]);
						//---�жϲɼ���ϸ�����
						if ((detaCurrentX10uA <3)||(rfask->msgSiteCurrent[siteNum]<currentPointCurrent[siteNum]))
						{
							//---�жϲ��ϸ�ԭ���Ǹõ�ĵ���֮ǰ�ļ�����С���߲�ֵ���趨�ϸ�������СֵС��������趨�ĺϸ����������ֵ��
							rfask->msgSitePass[siteNum] = 1 + freqPointNum;
						}
					}
				}
			}
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSiteCurrent[siteNum] >> 8));
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSiteCurrent[siteNum]));
		}
		//---ι�������ⳤʱ��ģ��Ӷ����¿��Ź���λ
		WDT_RESET();
	}
	//---���Ͳ�����ɵĽ��
	for (siteNum = 0; siteNum < FREQ_CURRENT_MAX_SITE; siteNum++)
	{
		USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSitePass[siteNum] >> 8));
		USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSitePass[siteNum]));
	}
	//---�ر�ʱ�����
	CLK_FREQ_OFF;
	//---�رյ�Դ
	DPS_POWER_OFF;
	//---����Ƶ�ʹ����ڲ������ĵ�,Ĭ����20KHz
	//RFASKTask_SetClockFreq(rfask, WM8510x, FREQ_YSEL_X100MHz);
	//---��λʱ��оƬWM8510����Ҫ����һ���Ǹ��Ƚϵ��ʺϵ�ǰģʽ
	WM8510Task_I2C_Reset(WM8510x);
	//---Ƶ�ʵ���ɨ������ĵڶ����汾������֧��ʵʱ����
	#if (LNW_FT_ASK_MBOARD_VERSION==2)
		//---��������
		DecodeTask_START();
	#endif  	
	//---����ֵ
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡ�豸�Ļ�������
//////////////////////////////////////////////////////////////////////////////
//UINT8_T RFASKTask_FreqCurrentHandlerTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask)
UINT8_T RFASKTask_FreqCurrentHandlerTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;
	//---ִ����������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex])
	{
		//---��ȡ�豸����
		case CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_TYPE_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 4);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---�����豸����
			USARTTask_RealTime_AddByte(USARTx, rfask->msgDeviceType);
			break;
			//---��ȡ��������
		case CMD_RFASK_CMD1_FREQ_CURRENT_SAMPLE_RES_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 5);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���ز�������Ĵ�С
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSampleX100Res >> 8));
			//---���ز�������Ĵ�С
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSampleX100Res));
			break;
			//---��ȡ�Ŵ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_AMP_TIMES_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 5);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---���طŴ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgAmpTimes >> 8));
			//---���طŴ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgAmpTimes));
			break;
			//---�����豸����
		case CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_TYPE_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---���������豸������
			rfask->msgDeviceType = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_TYPE_ADDR_X1, rfask->msgDeviceType, 1);
			break;
			//---���ò�������
		case CMD_RFASK_CMD1_FREQ_CURRENT_SAMPLE_RES_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---�������ò�������Ĵ�С
			rfask->msgSampleX100Res = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			rfask->msgSampleX100Res = (rfask->msgSampleX100Res << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_SAMPLE_RES_ADDR_X1, rfask->msgSampleX100Res, 2);
			break;
			//---���÷Ŵ���
		case CMD_RFASK_CMD1_FREQ_CURRENT_AMP_TIMES_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			
			//---�������÷Ŵ���
			rfask->msgAmpTimes = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			rfask->msgAmpTimes = (rfask->msgSampleX100Res << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_AMP_TIMES_ADDR_X1, rfask->msgAmpTimes, 2);
			break;
			//---��ȡ�豸��Ϣ
		case CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_GET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 8);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);
			//---�����豸����
			USARTTask_RealTime_AddByte(USARTx, rfask->msgDeviceType);
			//---���ز�������Ĵ�С
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSampleX100Res >> 8));
			//---���ز�������Ĵ�С
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgSampleX100Res));
			//---���طŴ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgAmpTimes >> 8));
			//---���طŴ���
			USARTTask_RealTime_AddByte(USARTx, (UINT8_T)(rfask->msgAmpTimes));
			break;
			//---�����豸��Ϣ
		case CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_SET:
			//---���ݷ��ͱ�ͷ
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
			//---�������ݴ�С
			USARTTask_RealTime_AddSize(USARTx, 3);
			//---���ص�һ������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
			//--�õ����ؽ��
			USARTTask_RealTime_AddByte(USARTx, 0);
			//---���صĶ�������
			USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex]);

			//---���������豸������
			rfask->msgDeviceType = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_TYPE_ADDR_X1, rfask->msgDeviceType, 1);

			//---�������ò�������Ĵ�С
			rfask->msgSampleX100Res = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 1];
			rfask->msgSampleX100Res = (rfask->msgSampleX100Res << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 2];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_SAMPLE_RES_ADDR_X1, rfask->msgSampleX100Res, 2);

			//---�������÷Ŵ���
			rfask->msgAmpTimes = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 3];
			rfask->msgAmpTimes = (rfask->msgAmpTimes << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + 4];
			//---�������ò���
			RFASK_EEPROMWrite(AT24CXXx, RFASK_AMP_TIMES_ADDR_X1, rfask->msgAmpTimes, 2);
			break;
		default:
			_return = 1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡ��ǰ�����������ں�ʱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASKTask_VersionTask(USART_HandlerType*USARTx)
{
	UINT8_T i = 0;
	//---���ݷ��ͱ�ͷ
	USARTTask_RealTime_AddByte(USARTx, USARTx->msgTxID);
	//---�������ݴ�С
	USARTTask_RealTime_AddSize(USARTx, (3 + VERSION_DATE_SIZE + VERSION_TIME_SIZE));
	//---���ص�һ������
	USARTTask_RealTime_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
	//--�õ����ؽ��
	USARTTask_RealTime_AddByte(USARTx, 0);
	//---���صĶ�������
	USARTTask_RealTime_AddByte(USARTx, 0xFF);
	//---�汾����
	for (i = 0; i < VERSION_DATE_SIZE; i++)
	{
		USARTTask_RealTime_AddByte(USARTx, g_VersionDate[i]);
	}
	//---�汾ʱ��
	for (i = 0; i < VERSION_TIME_SIZE; i++)
	{
		USARTTask_RealTime_AddByte(USARTx, g_VersionTime[i]);
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
//UINT8_T RFASKTask_HandlerTask(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x)
UINT8_T RFASKTask_HandlerTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x,AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;
	//---�������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex])
	{
		case CMD_RFASK_CMD1_VERSIOM:
			break;
			//---WM8510ʱ�ӵĿ���
		case CMD_RFASK_CMD1_FREQ_WM8510:
			_return = RFASKTask_WM8510Task(USARTx, WM8510x,AT24CXXx);
			break;
			//---Ĭ��Ԥ��Ƶ�ʵ�Ŀ���
		case CMD_RFASK_CMD1_YSEL_FREQ:
			_return = RFASKTask_YSELTask(USARTx, rfask, WM8510x, AT24CXXx);
			break;
			//---Ƶ�ʵ���ɨ��Ĳ���
		case CMD_RFASK_CMD1_FREQ_CURRENT:
			RFASKTask_FreqCurrentHandlerTask(USARTx, rfask, AT24CXXx);
			break;
			//---��һ����ѹ���Ƶ�ʵ���ɨ��
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_ONE:
			//---Ƶ�ʵ���ɨ��
			_return = RFASKTask_FreqCurrentPointOneTask(USARTx, rfask, WM8510x, AT24CXXx);
			break;
			//---�ڶ�����ѹ���Ƶ�ʵ���ɨ��
		case CMD_RFASK_CMD1_FREQ_CURRENT_POINT_TWO:
			//---Ƶ�ʵ���ɨ��
			_return = RFASKTask_FreqCurrentPointTwoTask(USARTx, rfask, WM8510x, AT24CXXx);
			break;
		default:
			_return = ERROR_1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		��������������ͨ�������·�����
//////////////////////////////////////////////////////////////////////////////
//UINT8_T RFASKTask_Task(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x)
UINT8_T RFASKTask_Task(USART_HandlerType* USARTx, RFASK_HandlerType* rfask, WM8510_HandlerType* WM8510x,AT24CXX_HandlerType* AT24CXXx)
{
	//---�жϽ����Ƿ����
	if (USARTTask_GetReadState(USARTx) == 1)
	{
		//---CRC��У����豸IDУ��
		if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
		{
			//---�����������
			if (RFASKTask_HandlerTask(USARTx, rfask, WM8510x,AT24CXXx) == OK_0)
			{
				//---�ж��Ƿ���CRC
				USARTTask_RealTime_AddCRC(USARTx);
			}
		}
		else
		{
			//---����CRCУ�����
			USART_Printf(USARTx, "=>>����%d:����CRCУ�����<<=\r\n", (USARTx->msgIndex - 1));
		}
		return USARTTask_Read_Init(USARTx);
	}
	return USARTTask_TimeOVFTask(USARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_ScanYSEL(void)
{
	return RFASKLib_ScanYSEL();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_EOTSTART(RFASK_HandlerType *rfask)
{
	KeyTask_EOTSTART();
	//---��ʼ���ϸ�/ʧЧ�жϽ������---��ʼ��Ϊ�ϸ�ģʽ
	memset(rfask->msgSitePass, 0, FREQ_CURRENT_MAX_SITE);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_EOTSTOP(void)
{
	KeyTask_EOTSTOP();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  RFASKTask_BINPass(RFASK_HandlerType *rfask)
{
	UINT8_T i = 0;
	for (i = 0; i < FREQ_CURRENT_MAX_SITE; i++)
	{
		switch (i)
		{
			case 0:
				KeyTask_BINAPass(rfask->msgSitePass[i]);
				break;
			case 1:
				KeyTask_BINBPass(rfask->msgSitePass[i]);
				break;
			case 2:
				KeyTask_BINCPass(rfask->msgSitePass[i]);
				break;
			case 3:
				KeyTask_BINDPass(rfask->msgSitePass[i]);
				break;
			default:
				//---SITE�����ϸ�
				KeyTask_BINAPass(1);
				KeyTask_BINBPass(1);
				KeyTask_BINCPass(1);
				KeyTask_BINDPass(1);
				break;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		��������ɨ������
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASKTask_KeyTask(USART_HandlerType*USARTx, RFASK_HandlerType *rfask, WM8510_HandlerType *WM8510x, UINT8_T activateSites)
{
	//---��ȡYSEL��ֵ
	UINT8_T _return = RFASKTask_ScanYSEL();
	//---�ж�YSEL�Ƿ���Ч
	if (_return == 0xFF)
	{
		//---û�н����YSEL��Ϣ������2
		return ERROR_2;
	}

	//---������е�״̬��־λ
	else if (_return == RFASK_TASK_CLEAR)
	{
		//---����ʱ�Ӳ����
		CLK_FREQ_OFF;
		//---��λʱ��оƬWM8510
		WM8510Task_I2C_Reset(WM8510x);
		//---SOT�����
		EOT_CTR_OUT_1;
		BIN_CTR_OUT_1;
		//---��������
		DecodeTask_START();
	}
	else
	{
		//---�ж��Ƿ���SITE������������
		if (activateSites == 0)
		{
			//---û��SITE���
			return ERROR_3;
		}
		
		//---�رս���
		DecodeTask_STOP();
		
		//---SOT�����,���״̬��־λ�������´ν����ʱ��״̬����������һ״̬
		EOT_CTR_OUT_1;
		BIN_CTR_OUT_1;
		//---��ȡ�����SITE��Ϣ
		RFASKTask_ActivateSites(rfask, activateSites);
		//---��ʼ��EOT
		RFASKTask_EOTSTART(rfask);
		//---�������
		switch (_return)
		{
			case RFASK_TASK_YSEL1:
				//---����Ĭ��Ƶ��1
				RFASKTask_SetClockFreq(rfask, WM8510x, rfask->msgFreqX100MHzYSel1);
				//---ʹ��Ƶ�����
				CLK_FREQ_ON;
				break;
			case RFASK_TASK_YSEL2:
				//---����Ĭ��Ƶ��2
				RFASKTask_SetClockFreq(rfask, WM8510x, rfask->msgFreqX100MHzYSel2);
				//---ʹ��Ƶ�����
				CLK_FREQ_ON;
				break;
			case RFASK_TASK_YSEL3:
				//---����Ĭ��Ƶ��3
				RFASKTask_SetClockFreq(rfask, WM8510x, rfask->msgFreqX100MHzYSel3);
				//---ʹ��Ƶ�����
				CLK_FREQ_ON;
				break;
			case RFASK_TASK_YSEL4:
				//---����Ĭ��Ƶ��4
				RFASKTask_SetClockFreq(rfask, WM8510x, rfask->msgFreqX100MHzYSel4);
				//---ʹ��Ƶ�����
				CLK_FREQ_ON;
				break;
			case RFASK_TASK_POINT_ONE:
				//---ִ��Ƶ�ʵ���ɨ���һ����
				RFASKTask_FreqCurrentScan(USARTx, rfask, &rfask->msgFreqCurrentPointOne, WM8510x);
				//---��ʹ��Ƶ�����
				CLK_FREQ_OFF;
				//---��Դ����
				DPS_POWER_HZ;
				break;
			case RFASK_TASK_POINT_TWO:
				//---ִ��Ƶ�ʵ���ɨ��ڶ�����
				RFASKTask_FreqCurrentScan(USARTx, rfask, &rfask->msgFreqCurrentPointTwo, WM8510x);
				//---��ʹ��Ƶ�����
				CLK_FREQ_OFF;
				//---��Դ����
				DPS_POWER_HZ;
				break;
			default:
				CLK_FREQ_OFF;
				_return = 0xFF;
				break;
		}

		//---ִ�н��
		RFASKTask_BINPass(rfask);
		//---���EOT�ź�
		RFASKTask_EOTSTOP();

		//if((_return!=RFASK_TASK_POINT_ONE)&&(_return!=RFASK_TASK_POINT_TWO))
		//{
		//		DelayTask_ms(20);
		//		//---��������
		//		DecodeTask_START();
		//}
	}
	if (_return != 0xFF)
	{
		_return = 0;
	}
	return _return;
}
