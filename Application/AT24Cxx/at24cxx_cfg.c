#include "at24cxx_cfg.h"

//===ȫ�ֱ�������
AT24CXX_HandlerType		g_AT24cxxDevice0={0};
pAT24CXX_HandlerType	pAT24cxxDevice0 = &g_AT24cxxDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_Init(AT24CXX_HandlerType *AT24CXXx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---ָ���豸�ĳ�ʼ��
	if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_ONE))
	{
		AT24CXX_I2C_Device0_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_TWO))
	{
		AT24CXX_I2C_Device1_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_THREE))
	{
		AT24CXX_I2C_Device2_Init(AT24CXXx);
	}
	else
	{
		return ERROR_1;
	}

	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(AT24CXXx->msgI2C));
		AT24CXXx->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(AT24CXXx->msgI2C), pFuncDelayus);

		//---ע��д����
		AT24CXXx->msgI2C.msgModelIsHW = 0;
	}
	//---������ʱ������ע��
	if (pFuncDelayms != NULL)
	{
		AT24CXXx->msgDelayms = pFuncDelayms;
	}
	else
	{
		AT24CXXx->msgDelayms = DelayTask_ms;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� AT24Cxx������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_DeviceType(AT24CXX_HandlerType *AT24CXXx)
{
	//---����ҳ�����ֽ�����
	if (AT24CXXx->msgAT24CXXType == AT24C01)		//at24c01
	{
		AT24CXXx->msgAT24CXXPageNum = 16;
		AT24CXXx->msgAT24CXXPageByte = 8;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C02)	//at24c02
	{
		AT24CXXx->msgAT24CXXPageNum = 32;
		AT24CXXx->msgAT24CXXPageByte = 8;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C04)	//at24c04
	{
		AT24CXXx->msgAT24CXXPageNum = 32;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C08)	//at24c08
	{
		AT24CXXx->msgAT24CXXPageNum = 64;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C16)	//at24c16
	{
		AT24CXXx->msgAT24CXXPageNum = 128;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C32)	//at24c32
	{
		AT24CXXx->msgAT24CXXPageNum = 128;
		AT24CXXx->msgAT24CXXPageByte = 32;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C64)	//at24c64
	{
		AT24CXXx->msgAT24CXXPageNum = 256;
		AT24CXXx->msgAT24CXXPageByte = 32;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C128)	//at24c128
	{
		AT24CXXx->msgAT24CXXPageNum = 256;
		AT24CXXx->msgAT24CXXPageByte = 64;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C256)	//at24c256
	{
		AT24CXXx->msgAT24CXXPageNum = 512;
		AT24CXXx->msgAT24CXXPageByte = 64;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C512)	//at24c512
	{
		AT24CXXx->msgAT24CXXPageNum = 512;
		AT24CXXx->msgAT24CXXPageByte = 128;
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
 UINT8_T AT24CXX_I2C_Device0_Init(AT24CXX_HandlerType *AT24CXXx)
{
	AT24CXXx->msgAT24CXXType = AT24C08;

	//---д�����˿ڵ�����
#ifdef AT24CXX_I2C_USE_HWWP
	AT24CXXx->msgWP.msgGPIOPort = GPIOC;
	AT24CXXx->msgWP.msgGPIOBit = LL_GPIO_PIN_4;

	//---��ʼ��д����
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		GPIOTask_Clock(AT24CXXx->msgWP.msgGPIOPort, 1);
	}
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
#ifdef AT24CXX_I2C_USE_HWWP
	GPIO_InitStruct.Pin =AT24CXXx->msgWP.msgGPIOBit;
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		LL_GPIO_Init(AT24CXXx->msgWP.msgGPIOPort, &GPIO_InitStruct);
		//---ʹ��д����
		GPIO_OUT_1(AT24CXXx->msgWP.msgGPIOPort, AT24CXXx->msgWP.msgGPIOBit);
	}
#endif

	AT24CXXx->msgI2C.msgI2Cx = NULL;
	AT24CXXx->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	AT24CXXx->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	AT24CXXx->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	AT24CXXx->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	AT24CXXx->msgI2C.msgModelIsHW = 0;
	AT24CXXx->msgI2C.msgPluseWidth = 0;
	AT24CXXx->msgI2C.msgDelayus = NULL;
	AT24CXXx->msgI2C.msgAddr = 0xA0;  // PCF8563_WRITE_ADDR;
	AT24CXXx->msgI2C.msgClockSpeed = 0;

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
UINT8_T AT24CXX_I2C_Device1_Init(AT24CXX_HandlerType *AT24CXXx)
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
UINT8_T AT24CXX_I2C_Device2_Init(AT24CXX_HandlerType *AT24CXXx)
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
UINT8_T AT24CXX_I2C_DeInit(AT24CXX_HandlerType *AT24CXXx)
{
	//---ע��I2C�豸
	if (AT24CXXx->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(AT24CXXx->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---����д����
	#ifdef AT24CXX_I2C_USE_HWWP
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgGPIOPort, AT24CXXx->msgWP.msgGPIOBit);
	}
	#endif

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
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

	//---ʹ��д����
	#ifdef AT24CXX_I2C_USE_HWWP
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgGPIOPort, AT24CXXx->msgWP.msgGPIOBit);
	}
	#endif
	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return==OK_0)
	{
		//---�Ա��ʱ����5ms
		if (AT24CXXx->msgDelayms != NULL)
		{
			AT24CXXx->msgDelayms(5);
		}

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
UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---����д����
	#ifdef AT24CXX_I2C_USE_HWWP
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgGPIOPort, AT24CXXx->msgWP.msgGPIOBit);
	}
	#endif
	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
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

	GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));

	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---������ȷ��������ʱ�ȴ���̽���
	if (_return == OK_0)
	{
		//---�Ա��ʱ����5ms
		if (AT24CXXx->msgDelayms != NULL)
		{
			AT24CXXx->msgDelayms(5);
		}

	}
	#ifdef AT24CXX_I2C_USE_HWWP
	//---ʹ��д����
	if (AT24CXXx->msgWP.msgGPIOPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgGPIOPort, AT24CXXx->msgWP.msgGPIOBit);
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
UINT8_T AT24CXX_SWI2C_WriteData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---Ҫд��ҳ��
	UINT16_T pageNum = 0;
	//---����ҳҪд����ֽ���
	UINT16_T byteNum = 0;
	//---ҳ��ַ������ʼҳ������
	UINT16_T pageIndexAddr = addr / (AT24CXXx->msgAT24CXXPageByte);
	//---����һҳ������
	UINT16_T byteIndexAddr = addr % (AT24CXXx->msgAT24CXXPageByte);
	//---����һҳ������Ҫд����ֽ���
	UINT16_T pageByteNum = AT24CXXx->msgAT24CXXPageByte - byteIndexAddr;
	//---
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	//---������д���д�������Ϊ��
	if ((length==0)||(pVal==NULL))
	{
		return ERROR_6;
	}
	//---���ݳ��ȵĴ�С
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---��Ҫд������ݲ�����2�ֽڵ�ʱ�򣬰�ҳд��Ͱ��ֽ�д�����ĵ�ʱ�������ͬ
	if (length<3)
	{
		//---���ֽ�д��
		for (i=0;i<length;i++)
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
			UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgAT24CXXPageByte);
			//---�жϻ���ռ������Ƿ�ɹ�
			if (pAT24CxxPageByteBuffer == NULL)
			{
				_return = ERROR_8;
				goto GoToExit;
			}
		#endif
		//---�ȵ�һҳд����д����ֽ�����С��3���ֽ�
		if (pageByteNum != AT24CXXx->msgAT24CXXPageByte)
		{
			//---��ȡһҳ������
			#ifndef USE_GOBAL_RAM
				_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), pAT24CxxPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
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
				if (length==0)
				{
					//---�˳����ݵ����
					break;
				}
			}
			//---���㵱ǰҳ�е��ֽ�ƫ�Ƶ�ַ
			byteIndexAddr = 0;
			//---��ҳд������
			#ifndef USE_GOBAL_RAM
				_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), pAT24CxxPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
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
		pageNum = length / AT24CXXx->msgAT24CXXPageByte;
		//---�������һҳҪд����ֽ���
		byteNum = length % AT24CXXx->msgAT24CXXPageByte;
		//---�ж��Ƿ���Ҫҳд��
		if (pageNum != 0)
		{
			for (i = 0; i < pageNum; i++)
			{
				_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, AT24CXXx->msgAT24CXXPageByte);
				//---��ַƫ�ƣ�ƫ�Ƶ��´�Ҫд������ݵ�ҳ���׵�ַ
				addr += AT24CXXx->msgAT24CXXPageByte;
				//---����ƫ��
				pVal += AT24CXXx->msgAT24CXXPageByte;
				//---���ݳ���ƫ��
				length -= AT24CXXx->msgAT24CXXPageByte;
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
				_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
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
					pAT24CxxPageByteBuffer[i+byteIndexAddr] = *pVal;
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
				_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
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
UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal,UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
	else
	{
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
UINT8_T AT24CXX_I2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
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
UINT8_T AT24CXX_I2C_WriteData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_WriteData(AT24CXXx, addr, pVal, length);
	}
	else
	{
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
UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
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
UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
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
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), _return);
	}
	_return = OK_0;
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
UINT8_T AT24CXX_SWI2C_ReadData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
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
		if (i == ( length - 1 ))
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&( AT24CXXx->msgI2C ), _return);
	}
	_return = OK_0;
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
UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
	else
	{
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
UINT8_T AT24CXX_I2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
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
UINT8_T AT24CXX_I2C_ReadData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_ReadData(AT24CXXx, addr, pVal, length);
	}
	else
	{
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
UINT8_T AT24CXX_I2C_EraseChip(AT24CXX_HandlerType *AT24CXXx)
{
	UINT8_T _return =OK_0;
	UINT16_T i = 0;
	UINT16_T addr = 0;
	//---�����ڴ�
	#ifndef USE_GOBAL_RAM
		//---�����ڴ�
		UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgAT24CXXPageByte);
		//---�жϻ���ռ������Ƿ�ɹ�
		if (pAT24CxxPageByteBuffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
	#endif
	//---��仺����
	for (i=0;i<AT24CXXx->msgAT24CXXPageByte;i++)
	{
		#ifndef USE_GOBAL_RAM
			*pAT24CxxPageByteBuffer = 0xFF;
			pAT24CxxPageByteBuffer++;
		#else
			AT24CXXx->msgPageByteBuffer[i] = 0xFF;
		#endif
	}
	#ifndef USE_GOBAL_RAM
		pAT24CxxPageByteBuffer-=AT24CXXx->msgAT24CXXPageByte;
	#endif
	//---��������
	for (i=0;i<AT24CXXx->msgAT24CXXPageNum;i++)
	{
		//---��ҳд������
		#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
		#else
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
		#endif
		//---��ַ����
		addr += AT24CXXx->msgAT24CXXPageByte;
		//---�ж�д���Ƿ�ɹ�
		if (_return!=OK_0)
		{
			_return = ERROR_7;
			goto GoToExit;
		}
	}
	GoToExit:
	#ifndef USE_GOBAL_RAM
		//---�ͷ��ڴ�
		MyFree(pAT24CxxPageByteBuffer);
	#endif
	return _return;
}