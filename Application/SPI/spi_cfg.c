#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� SPI������ģʽ�Ĳ�ѯ��ʽ��ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandleType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(SPIx->pMsgSPIx);
	//---ʹ��SPI��ʱ����
	SPI_Clock(SPIx, 1);
	//---SPI��ʼ��
	LL_SPI_Init(SPIx->pMsgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1
		//---SPI1�ı�׼Э���֧��
		LL_SPI_SetStandard(SPIx->pMsgSPIx, SPIx->msgStandard);
	#endif
	//---ʹ��SPI
	LL_SPI_Enable(SPIx->pMsgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����Ǹ�λ����ǰ���ǵ�λ��ǰ
//////////////////////////////////////////////////////////////////////////////
void SPI_MHW_SetTransferBitOrder(SPI_HandleType *SPIx, UINT32_T BitOrder)
{
	LL_SPI_SetTransferBitOrder(SPIx->pMsgSPIx, BitOrder);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �˿ڳ�ʼ��
//////�������:
//////�������:
//////˵		���� Ӳ��SPI��Դʱ��GPIO�˿ڳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandleType *SPIx)
{
	//---ע����ǰ����������
	SPI_DeInit(SPIx, 1);
	//---�˿�ʱ�ӵ�����
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(SPIx->msgSCK.msgPort,  PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(SPIx->msgMOSI.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(SPIx->msgMISO.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };	
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;//LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	if (SPIx->msgCS.msgPort!=NULL)	
	{
		#ifndef  USE_FULL_GPIO
		GPIOTask_Clock(SPIx->msgCS.msgPort, PERIPHERAL_CLOCK_ENABLE);
		#endif
		//---SS---����Ϊ���
		GPIO_InitStruct.Pin = SPIx->msgCS.msgBit;
		LL_GPIO_Init(SPIx->msgCS.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgPort, SPIx->msgCS.msgBit);
	}
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = SPIx->msgGPIOAlternate;
	#endif
	//---SCK---����Ϊ���
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgBit;
	LL_GPIO_Init(SPIx->msgSCK.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);

	//---MOSI---����Ϊ���
	//GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgBit;
	LL_GPIO_Init(SPIx->msgMISO.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit);
	//---Ӳ��ģʽ
	SPIx->msgHwMode = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandleType *SPIx)
{
	//---ע����ǰ����������
	SPI_DeInit(SPIx, 1);
	//---�˿�ʱ�ӵ�����
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(SPIx->msgSCK.msgPort,  PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(SPIx->msgMOSI.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(SPIx->msgMISO.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	#ifndef USE_MCU_STM32F1
		GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	if (SPIx->msgCS.msgPort!=NULL)
	{
		#ifndef  USE_FULL_GPIO
		GPIOTask_Clock(SPIx->msgCS.msgPort, PERIPHERAL_CLOCK_ENABLE);
		#endif
		//---SS---����Ϊ���
		GPIO_InitStruct.Pin = SPIx->msgCS.msgBit;
		LL_GPIO_Init(SPIx->msgCS.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgPort, SPIx->msgCS.msgBit);
	}
	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgBit;
	LL_GPIO_Init(SPIx->msgSCK.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(SPIx->msgMISO.msgPort, &GPIO_InitStruct);	
	GPIO_OUT_1(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit);
	//---���ģ��ģʽ
	SPIx->msgHwMode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandleType *SPIx,UINT8_T isInitSS)
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
	if ((isInitSS!=0)&&(SPIx->msgCS.msgPort!=NULL))
	{
		//---SS---����Ϊ����
		GPIO_InitStruct.Pin = SPIx->msgCS.msgBit;
		LL_GPIO_Init(SPIx->msgCS.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(SPIx->msgCS.msgPort, SPIx->msgCS.msgBit);
	}
	//---SCK---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgBit;
	LL_GPIO_Init(SPIx->msgSCK.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
	//---MOSI---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgBit;
	LL_GPIO_Init(SPIx->msgMISO.msgPort, &GPIO_InitStruct);	
	GPIO_OUT_1(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandleType *SPIx, UINT8_T isInitSS)
{
	if (SPIx->pMsgSPIx != NULL)
	{
		//---�ָ���ǰ����Ϊ��ʼֵ
		LL_SPI_DeInit(SPIx->pMsgSPIx);
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
UINT8_T SPI_Clock(SPI_HandleType *SPIx, UINT8_T isEnable)
{
	#ifdef SPI1
	//---ѡ��SPI�ӿ�
	if (SPIx->pMsgSPIx == SPI1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);			
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef SPI2
	if (SPIx->pMsgSPIx == SPI2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef SPI3
	if (SPIx->pMsgSPIx == SPI3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
#ifdef SPI4
	if (SPIx->msgSPIx == SPI4)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
#ifdef SPI5
	if (SPIx->msgSPIx == SPI5)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
#ifdef SPI6
	if (SPIx->msgSPIx == SPI6)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������: 0---�ɹ���!=0---ʧ��
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteAndReadByte(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---�շ���ɱ�־λ
	UINT8_T _return = 2;
	//---��ȡ��ǰʱ�����
	oldTime = ((SPIx->pMsgTimeTick != NULL)?SPIx->pMsgTimeTick():0);
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�����շ�
	while (1)
	{
		//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
		if ((_return==2)&&(LL_SPI_IsActiveFlag_TXE(SPIx->pMsgSPIx)))
		{
			//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
			LL_SPI_TransmitData8(SPIx->pMsgSPIx, wVal);
			//---1
			_return = 1;
		}
		//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
		if (LL_SPI_IsActiveFlag_RXNE(SPIx->pMsgSPIx))
		{
			//---��ȡ���ݼĴ�������ȡ���ջ���������
			_return = LL_SPI_ReceiveData8(SPIx->pMsgSPIx);
			//---�ж����ݻ������Ƿ�Ϊ��
			if (pRVal!=NULL)
			{
				*pRVal = _return;
			}
			//---0
			_return =0;
		}
		//---��ʱ�ж�
		if (SPIx->pMsgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = SPIx->pMsgTimeTick();
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
UINT8_T SPI_MHW_PollMode_WriteAndReadData(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
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
	oldTime = ((SPIx->pMsgTimeTick != NULL) ? SPIx->pMsgTimeTick() : 0);
	nowTime = 0;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState=1;
	//---�����շ�
	while (1)
	{
		//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
		if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->pMsgSPIx)))
		{
			//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
			LL_SPI_TransmitData8(SPIx->pMsgSPIx, pWVal[i]);
			//---����
			txAllowed = 0;
		}
		//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
		if ((txAllowed==0)&&(LL_SPI_IsActiveFlag_RXNE(SPIx->pMsgSPIx)))
		{
			//---��ȡ���ݼĴ�������ȡ���ջ���������
			_return = LL_SPI_ReceiveData8(SPIx->pMsgSPIx);
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
		if (SPIx->pMsgTimeTick != NULL)
		{
			//---��ǰʱ��
			nowTime = SPIx->pMsgTimeTick();
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
UINT8_T SPI_MSW_WriteBitMSB(SPI_HandleType *SPIx, UINT8_T wVal)
{
	//---����1bit������
	((wVal & 0x80) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit) : GPIO_OUT_0(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� ��λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_ReadBitMSB(SPI_HandleType *SPIx,UINT8_T *pRVal)
{
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit) != 0) ? 1 : 0);
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
UINT8_T SPI_MSW_BitMSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	((wVal & 0x80) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit) : GPIO_OUT_0(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		*pRVal |=((GPIO_GET_STATE(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit) != 0)?1:0);
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
UINT8_T SPI_MSW_WriteAndReadBitMSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---00---11
	if (((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 0)) || ((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 1)))
	{
		GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitMSB(SPIx, wVal, pRVal);
		GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
	}
	//---10---01
	//if (((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 0))|| ((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 1)))
	else
	{
		GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitMSB(SPIx, wVal, pRVal);
		GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
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
UINT8_T SPI_MSW_WriteBitLSB(SPI_HandleType *SPIx, UINT8_T wVal)
{
	//---����1bit������
	((wVal & 0x01) != 0x00) ? GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit) : GPIO_OUT_0(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_ReadBitLSB(SPI_HandleType *SPIx,UINT8_T *pRVal)
{
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit) != 0) ? 0x80 : 0);
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
UINT8_T SPI_MSW_BitLSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	((wVal&0x01)!=0x00)? GPIO_OUT_1(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit): GPIO_OUT_0(SPIx->msgMOSI.msgPort, SPIx->msgMOSI.msgBit);
	//---��ȡ1bit������
	if (pRVal != NULL)
	{
		*pRVal |= ((GPIO_GET_STATE(SPIx->msgMISO.msgPort, SPIx->msgMISO.msgBit) != 0) ? 0x80 : 0);
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
UINT8_T SPI_MSW_WriteAndReadBitLSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---00---11
	if (((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 0)) || ((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 1)))
	{
		GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitLSB(SPIx, wVal, pRVal);
		GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
	}
	//---10---01
	//if (((SPIx->msgCPOL == 1) && (SPIx->msgCPOH == 0))|| ((SPIx->msgCPOL == 0) && (SPIx->msgCPOH == 1)))
	else
	{
		GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
		DELAY_NOP_COUNT(4);
		SPI_MSW_BitLSB(SPIx, wVal, pRVal);
		GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
		SPIx->pMsgDelayus(SPIx->msgPluseWidth);
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
UINT8_T SPI_MSW_SetClock(SPI_HandleType *SPIx, UINT32_T clock)
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
UINT8_T SPI_MHW_SetClock(SPI_HandleType *SPIx, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(SPIx->pMsgSPIx, clock);
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadByteMSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
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
	(SPIx->msgCPOL == 0) ? GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit) : GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadByteLSB(SPI_HandleType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
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
	(SPIx->msgCPOL == 0)? GPIO_OUT_0(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit): GPIO_OUT_1(SPIx->msgSCK.msgPort, SPIx->msgSCK.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteAndReadDataMSB(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
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
UINT8_T SPI_MSW_WriteAndReadBDataLSB(SPI_HandleType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
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
void  SPI_IRQ8BitTask(SPI_HandleType* SPIx)
{
	static UINT16_T i = 0;
	//---�շ���ɱ�־λ
	static UINT8_T txAllowed = 1;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->pMsgSPIx))&&(LL_SPI_IsEnabledIT_TXE(SPIx->pMsgSPIx)))
	{
		//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
		LL_SPI_TransmitData8(SPIx->pMsgSPIx, SPIx->pMsg8BitTxVal[i]);
		//---�л�Ϊ����
		txAllowed = 0;
	}
	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	if ((txAllowed == 0) && (LL_SPI_IsActiveFlag_RXNE(SPIx->pMsgSPIx)) && (LL_SPI_IsEnabledIT_RXNE(SPIx->pMsgSPIx)))
	{
		//---��ȡ���ݼĴ�������ȡ���ջ���������
		SPIx->pMsg8BitRxVal[i] = LL_SPI_ReceiveData8(SPIx->pMsgSPIx);
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
void  SPI_IRQ16BitTask(SPI_HandleType* SPIx)
{
	static UINT16_T i = 0;
	//---�շ���ɱ�־λ
	static UINT8_T txAllowed = 1;
	//---�л�����״̬Ϊ����ģʽ
	SPIx->msgState = 1;
	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	if ((txAllowed == 1) && (LL_SPI_IsActiveFlag_TXE(SPIx->pMsgSPIx)) && (LL_SPI_IsEnabledIT_TXE(SPIx->pMsgSPIx)))
	{
		//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
		LL_SPI_TransmitData16(SPIx->pMsgSPIx, SPIx->pMsg16BitTxVal[i]);
		//---�л�Ϊ����
		txAllowed = 0;
	}
	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	if ((txAllowed == 0) && (LL_SPI_IsActiveFlag_RXNE(SPIx->pMsgSPIx)) && (LL_SPI_IsEnabledIT_RXNE(SPIx->pMsgSPIx)))
	{
		//---��ȡ���ݼĴ�������ȡ���ջ���������
		SPIx->pMsg16BitRxVal[i] = LL_SPI_ReceiveData16(SPIx->pMsgSPIx);
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
void  SPI_IRQTask(SPI_HandleType* SPIx, UINT8_T is16Bit)
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