#include "at24cxx_cfg.h"

//===ȫ�ֱ�������
AT24CXX_HandleType		g_AT24cxxDevice0={0};
pAT24CXX_HandleType		pAT24cxxDevice0 = &g_AT24cxxDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� AT24Cxx������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_DeviceType(AT24CXX_HandleType *AT24CXXx)
{
	#ifdef USE_QUERY_WAIT_IDLE
	AT24CXXx->msgIntervalTime = 0;
	AT24CXXx->msgRecordTick = 0;
	#endif
	//---����ҳ�����ֽ�����
	if (AT24CXXx->msgType == AT24C01)		//at24c01
	{
		AT24CXXx->msgPageNum = 16;
		AT24CXXx->msgPageByte = 8;
	}
	else if (AT24CXXx->msgType == AT24C02)	//at24c02
	{
		AT24CXXx->msgPageNum = 32;
		AT24CXXx->msgPageByte = 8;
	}
	else if (AT24CXXx->msgType == AT24C04)	//at24c04
	{
		AT24CXXx->msgPageNum = 32;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C08)	//at24c08
	{
		AT24CXXx->msgPageNum = 64;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C16)	//at24c16
	{
		AT24CXXx->msgPageNum = 128;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C32)	//at24c32
	{
		AT24CXXx->msgPageNum = 128;
		AT24CXXx->msgPageByte = 32;
	}
	else if (AT24CXXx->msgType == AT24C64)	//at24c64
	{
		AT24CXXx->msgPageNum = 256;
		AT24CXXx->msgPageByte = 32;
	}
	else if (AT24CXXx->msgType == AT24C128)	//at24c128
	{
		AT24CXXx->msgPageNum = 256;
		AT24CXXx->msgPageByte = 64;
	}
	else if (AT24CXXx->msgType == AT24C256)	//at24c256
	{
		AT24CXXx->msgPageNum = 512;
		AT24CXXx->msgPageByte = 64;
	}
	else if (AT24CXXx->msgType == AT24C512)	//at24c512
	{
		AT24CXXx->msgPageNum = 512;
		AT24CXXx->msgPageByte = 128;
	}
	else
	{
		return ERROR_1;
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
UINT8_T AT24CXX_I2C_Device0_Init(AT24CXX_HandleType* AT24CXXx)
{
	AT24CXXx->msgType = AT24C08;
	//---д�����˿ڵ�����
	#ifdef USE_HW_WP
	AT24CXXx->msgWP.msgPort = GPIOC;
	AT24CXXx->msgWP.msgBit = LL_GPIO_PIN_4;
	//---��ʼ��д����
	#ifndef  USE_FULL_GPIO
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIOTask_Clock(AT24CXXx->msgWP.msgPort, PERIPHERAL_CLOCK_ENABLE);
	}
	#endif
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
	//---WP�˿ڵĳ�ʼ��
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = AT24CXXx->msgWP.msgBit;
		LL_GPIO_Init(AT24CXXx->msgWP.msgPort, &GPIO_InitStruct);
		//---ʹ��д����
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	AT24CXXx->msgI2C.pMsgI2Cx = NULL;
	AT24CXXx->msgI2C.msgSCL.msgPort = GPIOB;
	AT24CXXx->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	AT24CXXx->msgI2C.msgSDA.msgPort = GPIOB;
	AT24CXXx->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	AT24CXXx->msgI2C.msgHwMode = 0;
	AT24CXXx->msgI2C.msgPluseWidth = 0;
	AT24CXXx->msgI2C.pMsgDelayus = NULL;
	AT24CXXx->msgI2C.msgAddr = AT24CXX_WADDR;
	AT24CXXx->msgI2C.msgClockSpeed = 200000;
	//---����ҳ�����ֽ�����
	return AT24CXX_I2C_DeviceType(AT24CXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_Device1_Init(AT24CXX_HandleType* AT24CXXx)
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
UINT8_T AT24CXX_I2C_Device2_Init(AT24CXX_HandleType* AT24CXXx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_Init(AT24CXX_HandleType *AT24CXXx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_ONE))
	{
		_return = AT24CXX_I2C_Device0_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_TWO))
	{
		_return = AT24CXX_I2C_Device1_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_THREE))
	{
		_return = AT24CXX_I2C_Device2_Init(AT24CXXx);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(AT24CXXx->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(AT24CXXx->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---������ʱ������ע��
	(pFuncDelayms != NULL) ? (AT24CXXx->pMsgDelayms = pFuncDelayms) : (AT24CXXx->pMsgDelayms = DelayTask_ms);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�	ע��I2C������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_DeInit(AT24CXX_HandleType *AT24CXXx)
{
	return I2CTask_Master_DeInit(&(AT24CXXx->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����AT24Cxxд��������ʱʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_IntervalTime(AT24CXX_HandleType* AT24CXXx,UINT16_T intervalTime)
{
	#ifdef USE_QUERY_WAIT_IDLE
	AT24CXXx->msgIntervalTime = intervalTime;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ�AT24Cxxд��������ʱʱ�䵽��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WaitIdle(AT24CXX_HandleType* AT24CXXx)
{
	#ifdef USE_QUERY_WAIT_IDLE
	//---��ȡ��ǰʱ��
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (AT24CXXx->msgIntervalTime != 0)
	{
		while (1)
		{
			nowTime = AT24CXXx->msgI2C.pMsgTimeTick();
			//---�����Ѿ���ȥ��ʱ��
			if (nowTime < AT24CXXx->msgRecordTick)
			{
				cnt = (0xFFFFFFFF - AT24CXXx->msgRecordTick + nowTime);
			}
			else
			{
				cnt = nowTime - AT24CXXx->msgRecordTick;
			}
			//---�ж�ʱ���Ƿ񵽴�
			if (cnt > AT24CXXx->msgIntervalTime)
			{
				///---��ѵʱ����㴦��
				AT24CXXx->msgIntervalTime = 0;
				//---�˳�ѭ��
				break;
			}
			WDT_RESET();
		}
	}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---����д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---��ѯ��ʽ���ȴ�����
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---���ò�ѯʱ��
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---�Ա��ʱ����5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}	//---ʹ��д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---��ѯ��ʽ���ȴ�����
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8));
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	for (i = 0; i < length; i++)
	{
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		//---�ж���ȷ��
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---���ò�ѯʱ��
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---�Ա��ʱ����5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	#ifdef USE_HW_WP
	//---ʹ��д����
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---Ҫд��ҳ��
	UINT16_T pageNum = 0;
	//---����ҳҪд����ֽ���
	UINT16_T byteNum = 0;
	//---ҳ��ַ������ʼҳ������
	UINT16_T pageIndexAddr = addr / (AT24CXXx->msgPageByte);
	//---����һҳ������
	UINT16_T byteIndexAddr = addr % (AT24CXXx->msgPageByte);
	//---����һҳ������Ҫд����ֽ���
	UINT16_T pageByteNum = AT24CXXx->msgPageByte - byteIndexAddr;
	//---
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	//---������д���д�������Ϊ��
	if ((length == 0) || (pVal == NULL))
	{
		return ERROR_6;
	}
	//---���ݳ��ȵĴ�С
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---��Ҫд������ݲ�����2�ֽڵ�ʱ�򣬰�ҳд��Ͱ��ֽ�д�����ĵ�ʱ�������ͬ
	if (length < 3)
	{
		//---���ֽ�д��
		for (i = 0; i < length; i++)
		{
			_return = AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, *pVal);
			addr++;
			pVal++;
			//---�ж��ǲ���д��ɹ�
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---��ҳд��
		#ifndef USE_GOBAL_RAM
		//---�����ڴ�
		UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
		//---�жϻ���ռ������Ƿ�ɹ�
		if (pAT24CxxPageByteBuffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
		#endif
		//---�ȵ�һҳд����д����ֽ�����С��3���ֽ�
		if (pageByteNum != AT24CXXx->msgPageByte)
		{
			//---��ȡһҳ������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---��ַƫ�ƣ�ʹ��ַƫ�Ƶ�ҳ���׵�ַ
				addr++;
				//---����ƫ��
				pVal++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---���㵱ǰҳ�е��ֽ�ƫ�Ƶ�ַ
			byteIndexAddr = 0;
			//---��ҳд������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---д��ҳ����
		//---����Ҫд���ҳ��
		pageNum = length / AT24CXXx->msgPageByte;
		//---�������һҳҪд����ֽ���
		byteNum = length % AT24CXXx->msgPageByte;
		//---�ж��Ƿ���Ҫҳд��
		if (pageNum != 0)
		{
			for (i = 0; i < pageNum; i++)
			{
				_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, AT24CXXx->msgPageByte);
				//---��ַƫ�ƣ�ƫ�Ƶ��´�Ҫд������ݵ�ҳ���׵�ַ
				addr += AT24CXXx->msgPageByte;
				//---����ƫ��
				pVal += AT24CXXx->msgPageByte;
				//---���ݳ���ƫ��
				length -= AT24CXXx->msgPageByte;
				//---�ж��ǲ���д��ɹ�
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
			}
		}
		//---�ж��ǲ��ǲ���ҳ�Ĳ���
		if (byteNum != 0)
		{
			//---��ȡһҳ������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---��ַƫ�ƣ���ʱ�Ѿ���ҳ���׵�ַ�ˣ�����ֵ����ƫ����
				//addr++;
				//---����ƫ��
				pVal++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---��ҳд������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
		#ifndef USE_GOBAL_RAM
		//---�˳��������
		GoToExit :
		//---�ͷ��ڴ�
		MyFree(pAT24CxxPageByteBuffer);
		#endif
	}
	#ifdef USE_GOBAL_RAM
	GoToExit :
	#endif
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---����д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---��ѯ��ʽ���ȴ�����
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8), 0);
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF), 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	
	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---���ò�ѯʱ��
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---�Ա��ʱ����5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	//---ʹ��д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal,UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����д����
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---��ѯ��ʽ���ȴ�����
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8), 0);
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF), 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���ݷ���
	for (i = 0; i < length; i++)
	{
		//---�������ݣ��ڲ��Ĵ�������
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---���ò�ѯʱ��
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---�Ա��ʱ����5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	#ifdef USE_HW_WP
	//---ʹ��д����
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---Ҫд��ҳ��
	UINT16_T pageNum = 0;
	//---����ҳҪд����ֽ���
	UINT16_T byteNum = 0;
	//---ҳ��ַ������ʼҳ������
	UINT16_T pageIndexAddr = addr / (AT24CXXx->msgPageByte);
	//---����һҳ������
	UINT16_T byteIndexAddr = addr % (AT24CXXx->msgPageByte);
	//---����һҳ������Ҫд����ֽ���
	UINT16_T pageByteNum = AT24CXXx->msgPageByte - byteIndexAddr;
	//---
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	//---������д���д�������Ϊ��
	if ((length == 0) || (pVal == NULL))
	{
		return ERROR_6;
	}
	//---���ݳ��ȵĴ�С
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---��Ҫд������ݲ�����2�ֽڵ�ʱ�򣬰�ҳд��Ͱ��ֽ�д�����ĵ�ʱ�������ͬ
	if (length < 3)
	{
		//---���ֽ�д��
		for (i = 0; i < length; i++)
		{
			_return = AT24CXX_HWI2C_WriteOneByte(AT24CXXx, addr, *pVal);
			addr++;
			pVal++;
			//---�ж��ǲ���д��ɹ�
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---��ҳд��
		#ifndef USE_GOBAL_RAM
		//---�����ڴ�
		UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
		//---�жϻ���ռ������Ƿ�ɹ�
		if (pAT24CxxPageByteBuffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
		#endif
		//---�ȵ�һҳд����д����ֽ�����С��3���ֽ�
		if (pageByteNum != AT24CXXx->msgPageByte)
		{
			//---��ȡһҳ������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---��ַƫ�ƣ�ʹ��ַƫ�Ƶ�ҳ���׵�ַ
				addr++;
				//---����ƫ��
				pVal++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---���㵱ǰҳ�е��ֽ�ƫ�Ƶ�ַ
			byteIndexAddr = 0;
			//---��ҳд������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---д��ҳ����
		//---����Ҫд���ҳ��
		pageNum = length / AT24CXXx->msgPageByte;
		//---�������һҳҪд����ֽ���
		byteNum = length % AT24CXXx->msgPageByte;
		//---�ж��Ƿ���Ҫҳд��
		if (pageNum != 0)
		{
			for (i = 0; i < pageNum; i++)
			{
				_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pVal, AT24CXXx->msgPageByte);
				//---��ַƫ�ƣ�ƫ�Ƶ��´�Ҫд������ݵ�ҳ���׵�ַ
				addr += AT24CXXx->msgPageByte;
				//---����ƫ��
				pVal += AT24CXXx->msgPageByte;
				//---���ݳ���ƫ��
				length -= AT24CXXx->msgPageByte;
				//---�ж��ǲ���д��ɹ�
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
			}
		}
		//---�ж��ǲ��ǲ���ҳ�Ĳ���
		if (byteNum != 0)
		{
			//---��ȡһҳ������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---��ȡ�ж�
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---�������
			for (i = 0; i < pageByteNum; i++)
			{
				//---������ݵ�������
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---��ַƫ�ƣ���ʱ�Ѿ���ҳ���׵�ַ�ˣ�����ֵ����ƫ����
				//addr++;
				//---����ƫ��
				pVal++;
				//---���ݳ���ƫ��
				length--;
				//---����������
				if (length == 0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---��ҳд������
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---д���ж�
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
		#ifndef USE_GOBAL_RAM
		//---�˳��������
		GoToExit :
		//---�ͷ��ڴ�
		MyFree(pAT24CxxPageByteBuffer);
		#endif
	}
	#ifdef USE_GOBAL_RAM
	GoToExit :
	#endif
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WriteData(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_WriteData(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
	//---���Ͳ�Ӧ���ź�
	I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), 1);
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&( AT24CXXx->msgI2C ), ( UINT8_T )( addr >> 8 ));
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&( AT24CXXx->msgI2C ));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += ( ( ( addr >> 8 ) << 1 ) & 0x0F );
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&( AT24CXXx->msgI2C ), ( UINT8_T )( addr & 0xFF ));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&( AT24CXXx->msgI2C ));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&( AT24CXXx->msgI2C ));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&( AT24CXXx->msgI2C ), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---�˳����������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&( AT24CXXx->msgI2C ));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), 1);
	//---��ȡ����
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	}
	_return = OK_0;
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����豸����
	if (AT24CXXx->msgType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
		//---���ͼĴ�����ַ,�ߵ�ַ
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---����IIC������������ַ��д����
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---���ͼĴ�����ַ,��λ��ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	}
	_return = OK_0;
	//---�˳����������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadData(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---Ӳ��I2C
		return AT24CXX_HWI2C_ReadData(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ȫоƬ��������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_EraseChip(AT24CXX_HandleType *AT24CXXx)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	UINT16_T addr = 0;
	//---�����ڴ�
	#ifndef USE_GOBAL_RAM
	//---�����ڴ�
	UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
	//---�жϻ���ռ������Ƿ�ɹ�
	if (pAT24CxxPageByteBuffer == NULL)
	{
		_return = ERROR_8;
		goto GoToExit;
	}
	#endif
	//---��仺����
	for (i = 0; i < AT24CXXx->msgPageByte; i++)
	{
		#ifndef USE_GOBAL_RAM
		* pAT24CxxPageByteBuffer = 0xFF;
		pAT24CxxPageByteBuffer++;
		#else
		AT24CXXx->msgPageByteBuffer[i] = 0xFF;
		#endif
	}
	#ifndef USE_GOBAL_RAM
	pAT24CxxPageByteBuffer -= AT24CXXx->msgPageByte;
	#endif
	//---��������
	for (i = 0; i < AT24CXXx->msgPageNum; i++)
	{
		//---��ҳд������
		#ifndef USE_GOBAL_RAM
		_return = AT24CXX_I2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
		#else
		_return = AT24CXX_I2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
		#endif
		//---��ַ����
		addr += AT24CXXx->msgPageByte;
		//---�ж�д���Ƿ�ɹ�
		if (_return != OK_0)
		{
			_return = ERROR_7;
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	#ifndef USE_GOBAL_RAM
	//---�ͷ��ڴ�
	MyFree(pAT24CxxPageByteBuffer);
	#endif
	return _return;
}