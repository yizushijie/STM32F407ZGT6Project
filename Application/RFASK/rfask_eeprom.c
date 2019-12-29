#include"rfask_eeprom.h"

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ����eeprom�е���������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void RFASK_EEPROMInit(RFASK_HandlerType* rfask, AT24CXX_HandlerType* AT24CXXx)
{
	UINT8_T _return = OK_0;
	UINT8_T tempAddrX1[16] = { 0 };
	UINT8_T tempAddrX2[16] = { 0 };

	//---��ȡ������Ϣ
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_TYPE_ADDR_X1, tempAddrX1, 5);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_TYPE_ADDR_X2, tempAddrX2, 5);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 5) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0,  RFASK_TYPE_ADDR_X3, tempAddrX1, 5);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_TYPE_ADDR_X1, tempAddrX1, 5);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_TYPE_ADDR_X2, tempAddrX1, 5);
		_return = ERROR_1;
	}
	if (tempAddrX1[0]!=0xFF)
	{
		rfask->msgDeviceType = tempAddrX1[0];

		rfask->msgSampleX100Res = tempAddrX1[1];
		rfask->msgSampleX100Res =(rfask->msgSampleX100Res<<8)+ tempAddrX1[2];

		rfask->msgAmpTimes= tempAddrX1[3];
		rfask->msgAmpTimes = (rfask->msgAmpTimes << 8) + tempAddrX1[4];
	}
	//---�豸�����Ͳ���ʹ0
	if (tempAddrX1[0] == 0x00)
	{
		_return = ERROR_1;
	}
	//---�������
	memset(tempAddrX1, 0, 16);
	memset(tempAddrX2, 0, 16);

	//---��ȡĬ��Ƶ�ʵ�
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_FREQ_YSEL1_ADDR_X1, tempAddrX1, 16);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_FREQ_YSEL1_ADDR_X2, tempAddrX2, 16);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 16) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_FREQ_YSEL1_ADDR_X3,  tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_FREQ_YSEL1_ADDR_X1, tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_FREQ_YSEL1_ADDR_X1, tempAddrX1, 16);
		_return = ERROR_2;
	}
	if (tempAddrX1[0] != 0xFF)
	{
		rfask->msgFreqX100MHzYSel1 = tempAddrX1[0];
		rfask->msgFreqX100MHzYSel1 = (rfask->msgFreqX100MHzYSel1 << 8) + tempAddrX1[1];
		rfask->msgFreqX100MHzYSel1 = (rfask->msgFreqX100MHzYSel1 << 8) + tempAddrX1[2];
		rfask->msgFreqX100MHzYSel1 = (rfask->msgFreqX100MHzYSel1 << 8) + tempAddrX1[3];

		rfask->msgFreqX100MHzYSel2 = tempAddrX1[4];
		rfask->msgFreqX100MHzYSel2 = (rfask->msgFreqX100MHzYSel2 << 8) + tempAddrX1[5];
		rfask->msgFreqX100MHzYSel2 = (rfask->msgFreqX100MHzYSel2 << 8) + tempAddrX1[6];
		rfask->msgFreqX100MHzYSel2 = (rfask->msgFreqX100MHzYSel2 << 8) + tempAddrX1[7];

		rfask->msgFreqX100MHzYSel3 = tempAddrX1[8];
		rfask->msgFreqX100MHzYSel3 = (rfask->msgFreqX100MHzYSel3 << 8) + tempAddrX1[9];
		rfask->msgFreqX100MHzYSel3 = (rfask->msgFreqX100MHzYSel3 << 8) + tempAddrX1[10];
		rfask->msgFreqX100MHzYSel3 = (rfask->msgFreqX100MHzYSel3 << 8) + tempAddrX1[11];

		rfask->msgFreqX100MHzYSel4 = tempAddrX1[12];
		rfask->msgFreqX100MHzYSel4 = (rfask->msgFreqX100MHzYSel4 << 8) + tempAddrX1[13];
		rfask->msgFreqX100MHzYSel4 = (rfask->msgFreqX100MHzYSel4 << 8) + tempAddrX1[14];
		rfask->msgFreqX100MHzYSel4 = (rfask->msgFreqX100MHzYSel4 << 8) + tempAddrX1[15];
	}

	//---�������
	memset(tempAddrX1, 0, 16);
	memset(tempAddrX2, 0, 16);

	//---��ȡ��һ��Ƶ��ɨ���Ƶ�����ò���
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X1, tempAddrX1, 16);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X2, tempAddrX2, 16);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 16) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X3, tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X1, tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTONE_START_MAX_CURRENT_ADDR_X2, tempAddrX1, 16);
		_return = ERROR_3;
	}
	if (tempAddrX1[0] != 0xFF)
	{
		rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA = tempAddrX1[0];
		rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStartMaxCurrentX100mA << 8) + tempAddrX1[1];
		
		rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA = tempAddrX1[2];
		rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStartMinCurrentX100mA << 8) + tempAddrX1[3];

		rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA = tempAddrX1[4];
		rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStopMaxCurrentX100mA << 8) + tempAddrX1[5];

		rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA = tempAddrX1[6];
		rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA = (rfask->msgFreqCurrentPointOne.msgStopMinCurrentX100mA << 8) + tempAddrX1[7];

		rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = tempAddrX1[8];
		rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + tempAddrX1[9];
		rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + tempAddrX1[10];
		rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz << 8) + tempAddrX1[11];

		rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz = tempAddrX1[12];
		rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz = (rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz << 8) + tempAddrX1[13];

		rfask->msgFreqCurrentPointOne.msgFreqPointNum = tempAddrX1[14];
		rfask->msgFreqCurrentPointOne.msgFreqPointNum = (rfask->msgFreqCurrentPointOne.msgFreqPointNum << 8) + tempAddrX1[15];

		//---�����ֹƵ��
		rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz = rfask->msgFreqCurrentPointOne.msgFreqPointNum;
		rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz *= rfask->msgFreqCurrentPointOne.msgStepFreqX100MHz;
		rfask->msgFreqCurrentPointOne.msgStopFreqX100MHz += rfask->msgFreqCurrentPointOne.msgStartFreqX100MHz;

	}

	//---�������
	memset(tempAddrX1, 0, 16);
	memset(tempAddrX2, 0, 16);

	//---��ȡ��һ��Ƶ��ɨ���ADC���ò���
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_FREQ_CURRENT_POWER_ADDR_X1, tempAddrX1, 8);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_FREQ_CURRENT_POWER_ADDR_X2, tempAddrX2, 8);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 8) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTONE_FREQ_CURRENT_POWER_ADDR_X3, tempAddrX1,  8);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTONE_FREQ_CURRENT_POWER_ADDR_X1, tempAddrX1, 8);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTONE_FREQ_CURRENT_POWER_ADDR_X2, tempAddrX1, 8);
		_return = ERROR_4;
	}
	if (tempAddrX1[0] != 0xFF)
	{
		rfask->msgFreqCurrentPointOne.msgADCPointNum = tempAddrX1[2];
		rfask->msgFreqCurrentPointOne.msgADCPointNum = (rfask->msgFreqCurrentPointOne.msgADCPointNum << 8) + tempAddrX1[3];

		rfask->msgFreqCurrentPointOne.msgADCPassMax = tempAddrX1[4];
		rfask->msgFreqCurrentPointOne.msgADCPassMax = (rfask->msgFreqCurrentPointOne.msgADCPassMax << 8) + tempAddrX1[5];

		rfask->msgFreqCurrentPointOne.msgADCPassMin = tempAddrX1[6];
		rfask->msgFreqCurrentPointOne.msgADCPassMin = (rfask->msgFreqCurrentPointOne.msgADCPassMin << 8) + tempAddrX1[7];
	}

	//---�������
	memset(tempAddrX1, 0, 16);
	memset(tempAddrX2, 0, 16);

	//---��ȡ�ڶ���Ƶ��ɨ���Ƶ�����ò���
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X1, tempAddrX1, 16);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X2, tempAddrX2, 16);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 16) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0,  RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X3, tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X1, tempAddrX1, 16);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTTWO_START_MAX_CURRENT_ADDR_X2, tempAddrX1, 16);
		_return = ERROR_5;
	}
	if (tempAddrX1[0] != 0xFF)
	{
		rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA = tempAddrX1[0];
		rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStartMaxCurrentX100mA << 8) + tempAddrX1[1];

		rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA = tempAddrX1[2];
		rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStartMinCurrentX100mA << 8) + tempAddrX1[3];

		rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA = tempAddrX1[4];
		rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStopMaxCurrentX100mA << 8) + tempAddrX1[5];

		rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA = tempAddrX1[6];
		rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA = (rfask->msgFreqCurrentPointTwo.msgStopMinCurrentX100mA << 8) + tempAddrX1[7];

		rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = tempAddrX1[8];
		rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + tempAddrX1[9];
		rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + tempAddrX1[10];
		rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz << 8) + tempAddrX1[11];

		rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz = tempAddrX1[12];
		rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz = (rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz << 8) + tempAddrX1[13];

		rfask->msgFreqCurrentPointTwo.msgFreqPointNum = tempAddrX1[14];
		rfask->msgFreqCurrentPointTwo.msgFreqPointNum = (rfask->msgFreqCurrentPointTwo.msgFreqPointNum << 8) + tempAddrX1[15];

		rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz = rfask->msgFreqCurrentPointTwo.msgFreqPointNum;
		rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz *= rfask->msgFreqCurrentPointTwo.msgStepFreqX100MHz;
		rfask->msgFreqCurrentPointTwo.msgStopFreqX100MHz += rfask->msgFreqCurrentPointTwo.msgStartFreqX100MHz;
	}

	//---�������
	memset(tempAddrX1, 0, 16);
	memset(tempAddrX2, 0, 16);

	//---��ȡ�ڶ���Ƶ��ɨ���ADC���ò���
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTTWO_FREQ_CURRENT_POWER_ADDR_X1, tempAddrX1, 8);
	AT24CXXTask_I2C_ReadData(pAT24cxxDevice0, RFASK_POINTTWO_FREQ_CURRENT_POWER_ADDR_X2, tempAddrX2, 8);
	//---����ƥ��
	if (CompareByteToByte(tempAddrX1, tempAddrX2, 8) != 0)
	{
		AT24CXXTask_I2C_ReadData(pAT24cxxDevice0,  RFASK_POINTTWO_FREQ_CURRENT_POWER_ADDR_X3, tempAddrX1, 8);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTTWO_FREQ_CURRENT_POWER_ADDR_X1, tempAddrX1, 8);
		AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, RFASK_POINTTWO_FREQ_CURRENT_POWER_ADDR_X2, tempAddrX1, 8);
		_return = ERROR_6;
	}
	if (tempAddrX1[0] != 0xFF)
	{
		rfask->msgFreqCurrentPointTwo.msgADCPointNum = tempAddrX1[2];
		rfask->msgFreqCurrentPointTwo.msgADCPointNum = (rfask->msgFreqCurrentPointTwo.msgADCPointNum << 8) + tempAddrX1[3];

		rfask->msgFreqCurrentPointTwo.msgADCPassMax = tempAddrX1[4];
		rfask->msgFreqCurrentPointTwo.msgADCPassMax = (rfask->msgFreqCurrentPointTwo.msgADCPassMax << 8) + tempAddrX1[5];

		rfask->msgFreqCurrentPointTwo.msgADCPassMin = tempAddrX1[6];
		rfask->msgFreqCurrentPointTwo.msgADCPassMin = (rfask->msgFreqCurrentPointTwo.msgADCPassMin << 8) + tempAddrX1[7];
	}

	//---���eeprom�е����ݴ������¼���Ĭ��������Ϣ
	if (_return!=OK_0)
	{
		RFASK_StructInit(rfask);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ������д��eeprom�в��������ص�ַ������֤
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T RFASK_EEPROMWrite(AT24CXX_HandlerType* AT24CXXx, UINT16_T addr, UINT32_T cfgVal, UINT8_T cout)
{
	UINT8_T _return = OK_0;
	UINT8_T temp[4] = { 0 };
	temp[0] = (UINT8_T)(cfgVal >> 24);
	temp[1] = (UINT8_T)(cfgVal >> 16);
	temp[2] = (UINT8_T)(cfgVal >> 8);
	temp[3] = (UINT8_T)(cfgVal);
	
	//---У��д��������Ƿ�Ϸ�
	if ((cout==0)||(cout>4)||(AT24CXXx==NULL))
	{
		_return = ERROR_1;
	}
	else
	{
		//---��һ�α���Ĳ�����λ��
		_return = AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, addr, &temp[4 - cout], cout);
		if (_return != 0)
		{
			_return += 2;
		}
		//---�ڶ��α��������λ��
		_return = AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, addr + 0x50, &temp[4 - cout], cout);
		if (_return != 0)
		{
			_return += 3;
		}
		//---�����α��������λ��
		_return = AT24CXXTask_I2C_WriteData(pAT24cxxDevice0, addr + 0xA0, &temp[4 - cout], cout);
		if (_return != 0)
		{
			_return += 4;
		}
	}
	return _return;
}