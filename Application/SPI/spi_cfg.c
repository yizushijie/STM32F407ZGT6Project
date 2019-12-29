#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� SPI������ģʽ�Ĳ�ѯ��ʽ��ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(SPIx->msgSPIx);

	//---ʹ��SPI��ʱ����
	SPI_Clock(SPIx, 1);

	//---SPI��ʼ��
	LL_SPI_Init(SPIx->msgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1
		//---SPI1�ı�׼Э���֧��
		LL_SPI_SetStandard(SPIx->msgSPIx, SPIx->msgStandard);
	#endif
	//---ʹ��SPI
	LL_SPI_Enable(SPIx->msgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����Ǹ�λ����ǰ���ǵ�λ��ǰ
//////////////////////////////////////////////////////////////////////////////
void SPI_MHW_SetTransferBitOrder(SPI_HandlerType *SPIx, UINT32_T BitOrder)
{
	LL_SPI_SetTransferBitOrder(SPIx->msgSPIx, BitOrder);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �˿ڳ�ʼ��
//////�������:
//////�������:
//////˵		���� Ӳ��SPI��Դʱ��GPIO�˿ڳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };	
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;//LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	if (SPIx->msgCS.msgGPIOPort!=NULL)	
	{
		GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
		//---SS---����Ϊ���
		GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
		LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	}
	
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = SPIx->msgGPIOAlternate;
	#endif

	//---SCK---����Ϊ���
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);

	//---MOSI---����Ϊ���
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	if (SPIx->msgCS.msgGPIOPort!=NULL)
	{
		GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
		//---SS---����Ϊ���
		GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
		LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	}
	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);	
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *SPIx,UINT8_T isInitSS)
{
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
#endif
	if ((isInitSS!=0)&&(SPIx->msgCS.msgGPIOPort!=NULL))
	{
		//---SS---����Ϊ����
		GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
		LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	}
	//---SCK---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	//---MOSI---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);	
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandlerType *SPIx, UINT8_T isInitSS)
{
	if (SPIx->msgSPIx != NULL)
	{
		//---�ָ���ǰ����Ϊ��ʼֵ
		LL_SPI_DeInit(SPIx->msgSPIx);
		//---��ʹ��SPI��ʱ����
		SPI_Clock(SPIx, 0);
	}
	return SPI_GPIO_DeInit(SPIx, isInitSS);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_Clock(SPI_HandlerType *SPIx, UINT8_T isEnable)
{
	//---ѡ��SPI�ӿ�
	if (SPIx->msgSPIx == SPI1)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
	}
	else if (SPIx->msgSPIx == SPI2)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
	}
	else if (SPIx->msgSPIx == SPI3)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
	}
#ifdef SPI4
	else if (SPIx->msgSPIx == SPI4)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
	}
#endif
#ifdef SPI5
	else if (SPIx->msgSPIx == SPI5)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
	}
#endif
#ifdef SPI6
	else if (SPIx->msgSPIx == SPI6)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������: 0---�ɹ���!=0---ʧ��
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteAndReadByte(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---�շ���ɱ�־λ
	UINT8_T _return = 2;
	//---��ȡ��ǰʱ�����
	if (SPIx->msgTimeTick != NULL)
	{
		oldTime = SPIx->msgTimeTick();
	}
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�����շ�
	while (1)
	{
		//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
		if ((_return==2)&&(LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx)))
		{
			//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
			LL_SPI_TransmitData8(SPIx->msgSPIx, wVal);
			//---1
			_return = 1;
		}
		//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
		if (LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx))
		{
			//---��ȡ���ݼĴ�������ȡ���ջ���������
			_return = LL_SPI_ReceiveData8(SPIx->msgSPIx);
			//---�ж����ݻ������Ƿ�Ϊ��
			if (pRVal!=NULL)
			{
				*pRVal = _return;
			}
			//---0
			_return =0;
		}
		//---��ʱ�ж�
		if (SPIx->msgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = SPIx->msgTimeTick();
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
				_return = 3;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				_return = 4;
			}
		}
		//---�˳�ѭ��
		if ((_return==0)||(_return>2))
		{
			break;
		}
	}
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteAndReadData(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---�շ���ɱ�־λ
	UINT8_T txAllowed = 1;
	//---��ȡ��ǰʱ�����
	if (SPIx->msgTimeTick != NULL)
	{
		oldTime = SPIx->msgTimeTick();
	}
	nowTime = 0;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState=1;
	//---�����շ�
	while (1)
	{
		//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
		if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx)))
		{
			//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
			LL_SPI_TransmitData8(SPIx->msgSPIx, pWVal[i]);
			//---����
			txAllowed = 0;
		}
		//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
		if ((txAllowed==0)&&(LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx)))
		{
			//---��ȡ���ݼĴ�������ȡ���ջ���������
			_return = LL_SPI_ReceiveData8(SPIx->msgSPIx);
			//---�ж����ݻ������Ƿ�Ϊ��
			if (pRVal != NULL)
			{
				pRVal[i] = _return;
			}
			_return=0;
			//---����
			txAllowed = 1;
			//---��һ������
			i++;
		}
		//---��ʱ�ж�
		if (SPIx->msgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = SPIx->msgTimeTick();
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
				_return = 0x80+i;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				_return = 0x40+i;
			}
		}
		//---�˳�ѭ��
		if ((_return != 0)||(i==length))
		{
			break;
		}
	}
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal)
{
	//---����1bit������
	/*if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}*/
	((wVal & 0x80) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit) : GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_ReadBitMSB(SPI_HandlerType *SPIx,UINT8_T *pRVal)
{
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		/*if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
		{
			*pRVal |= 1;
		}*/
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0) ? 1 : 0);
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
UINT8_T SPI_MSW_BitMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	/*if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}*/
	((wVal & 0x80) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit) : GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		/*if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
		{
			*pRVal |= 1;
		}*/
		*pRVal |=((GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)?1:0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��д1Bit�����ݣ���λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---00---11
	if (((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 0)) || ((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 1)))
	{
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitMSB(SPIx, wVal, pRVal);
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
	}
	//---10---01
	//if (((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 0))|| ((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 1)))
	else
	{
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitMSB(SPIx, wVal, pRVal);
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal)
{
	//---����1bit������
	/*if ((wVal & 0x01) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}*/
	((wVal & 0x01) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit) : GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_ReadBitLSB(SPI_HandlerType *SPIx,UINT8_T *pRVal)
{
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
	/*	if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
		{
			*pRVal |= 0x80;
		}*/
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0) ? 0x80 : 0);
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
UINT8_T SPI_MSW_BitLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	/*if ((wVal & 0x01) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}*/
	((wVal&0x01)!=0x00)? GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit): GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		/*if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
		{
			*pRVal |= 0x80;
		}*/
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0) ? 0x80 : 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��д1Bit������,��λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---00---11
	if (((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 0)) || ((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 1)))
	{
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitLSB(SPIx, wVal, pRVal);
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
	}
	//---10---01
	//if (((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 0))|| ((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 1)))
	else
	{
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitLSB(SPIx, wVal, pRVal);
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		SPIx->msgDelayus(SPIx->msgPluseWidth);
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
UINT8_T SPI_MSW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	SPIx->msgPluseWidth = clock;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(SPIx->msgSPIx, clock);
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadByteMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;

	if (pRVal != NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal!=NULL)
		{
			*pRVal <<= 1;
		}
		SPI_MSW_WriteAndReadBitMSB(SPIx, wVal, pRVal);
		wVal <<= 1;
	}
	//---ʱ���ߵļ���
	(SPIx->msgCPOL == 0) ? GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit) : GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadByteLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	if (pRVal != NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal != NULL)
		{
			*pRVal >>= 1;
		}
		SPI_MSW_WriteAndReadBitLSB(SPIx, wVal, pRVal);
		wVal >>= 1;
	}
	//---ʱ���ߵļ���
	(SPIx->msgCPOL == 0)? GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit): GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadDataMSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	UINT8_T readVal = 0;
	for (i = 0; i < length; i++)
	{
		_return = SPI_MSW_WriteAndReadByteMSB(SPIx, pWVal[i], &readVal);
		//---�ж������Ƿ���Ч
		if (pRVal != NULL)
		{
			pRVal[i] = readVal;
		}
		//---�ж϶�ȡ��ȷ��
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadBDataLSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	UINT8_T readVal = 0;
	for (i = 0; i < length; i++)
	{
		_return = SPI_MSW_WriteAndReadByteLSB(SPIx, pWVal[i], &readVal);
		//---�ж������Ƿ���Ч
		if (pRVal != NULL)
		{
			pRVal[i] = readVal;
		}
		//---�ж϶�ȡ��ȷ��
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�8Bit�����жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  SPI_IRQ8BitTask(SPI_HandlerType* SPIx)
{
	static UINT16_T i = 0;
	//---�շ���ɱ�־λ
	static UINT8_T txAllowed = 1;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx))&&(LL_SPI_IsEnabledIT_TXE(SPIx->msgSPIx)))
	{
		//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
		LL_SPI_TransmitData8(SPIx->msgSPIx, SPIx->msg8BitTxPtr[i]);
		//---�л�Ϊ����
		txAllowed = 0;
	}
	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	if ((txAllowed == 0) && (LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx)) && (LL_SPI_IsEnabledIT_RXNE(SPIx->msgSPIx)))
	{
		//---��ȡ���ݼĴ�������ȡ���ջ���������
		SPIx->msg8BitRxPtr[i] = LL_SPI_ReceiveData8(SPIx->msgSPIx);
		//---�л�Ϊ����
		txAllowed = 1;
		//---��һ������
		i++;
	}
	//---�ж������Ƿ��շ����
	if (i==SPIx->msgDataCount)
	{
		i=0;
		txAllowed=0;
		//---�л�����״̬Ϊ����ģʽ
		SPIx->msgState = 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�8Bit�����жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  SPI_IRQ16BitTask(SPI_HandlerType* SPIx)
{
	static UINT16_T i = 0;
	//---�շ���ɱ�־λ
	static UINT8_T txAllowed = 1;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx)) && (LL_SPI_IsEnabledIT_TXE(SPIx->msgSPIx)))
	{
		//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
		LL_SPI_TransmitData16(SPIx->msgSPIx, SPIx->msg16BitTxPtr[i]);
		//---�л�Ϊ����
		txAllowed = 0;
	}
	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	if ((txAllowed == 0) && (LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx)) && (LL_SPI_IsEnabledIT_RXNE(SPIx->msgSPIx)))
	{
		//---��ȡ���ݼĴ�������ȡ���ջ���������
		SPIx->msg16BitRxPtr[i] = LL_SPI_ReceiveData16(SPIx->msgSPIx);
		//---�л�Ϊ����
		txAllowed = 1;
		//---��һ������
		i++;
	}
	//---�ж������Ƿ��շ����
	if (i == SPIx->msgDataCount)
	{
		i = 0;
		txAllowed = 0;
		//---�л�����״̬Ϊ����ģʽ
		SPIx->msgState = 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void  SPI_IRQTask(SPI_HandlerType* SPIx, UINT8_T is16Bit)
{
	if (is16Bit==0)
	{
		SPI_IRQ8BitTask(SPIx);
	}
	else
	{
		SPI_IRQ16BitTask(SPIx);
	}
}