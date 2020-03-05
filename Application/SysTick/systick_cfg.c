#include "systick_cfg.h"

//---��������
SysTick_HandleType		g_SysTick = { 0 };
pSysTick_HandleType	pSysTick = &g_SysTick;

#if defined (USE_HAL_DRIVER)
	//---�ⲿ���õ�Hal����ʱ����
	extern HAL_TickFreqTypeDef uwTickFreq;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Suspend(void)
{
	//---��ʹ��ϵͳ�δ�ʱ�����ж�
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Resume(void)
{
	//---ʹ��ϵͳ�δ�ʱ�����ж�
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� SysTickʹ�õĽṹ��ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_StructInit(SysTick_HandleType *sysTickx)
{
	UINT8_T i = 0;
	sysTickx->msgIncTick = 0;
	sysTickx->msgDecTick = 0;
	sysTickx->msgIncTickOVF = 0;
	//---������������
	for (i=0;i< SYSTICK_FUNC_TASK_MAX_NUM;i++)
	{
		sysTickx->msgTickTaskFlag[i] = 0;
		sysTickx->msgTickTaskValid[i] = 0;
		sysTickx->pMsgTickTask[i] = NULL;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���1ms�ĵδ�ʱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_msInit(void)
{
	//---��ʼ���ṹ��
	SysTick_StructInit(pSysTick);
	//---����δ�ʱ��
	SysTick_Suspend();
	//---����1ms��ʱ��δ���---�ó�ʼ������û��ע���ж�
	LL_InitTick(SystemCoreClock, 1000);
	//---�����ж���ռ����
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//---���õδ�ʱ���ж�---����Ϊ������ȼ�
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
	//---ʹ�ܵδ�ʱ���ж�---Ĭ����1ms
	SysTick_Resume();
#ifdef USE_HAL_DRIVER
	//---Hal��������ʱ����
	uwTickFreq = HAL_TICK_FREQ_DEFAULT;
	//---ע��Hal��ʹ�õĵδ�ʱ����
	SysTick_CreateTickTask(HAL_IncTick);
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
UINT8_T SysTick_DeInit(void)
{
	SysTick_Suspend();
	SysTick_StructInit(pSysTick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������δ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_CreateTickTask(void(*pFuncTick)(void))
{
	UINT8_T _return = ERROR_1;
	UINT32_T val = 0;
	if (pFuncTick!=NULL)
	{
		for (_return = 0; _return < SYSTICK_FUNC_TASK_MAX_NUM; _return++)
		{
			//---����¼��Ƿ��Ѿ�ע�����,�����ظ�ע��
			if ((pSysTick->pMsgTickTask[_return]!=NULL)&&(pSysTick->pMsgTickTask[_return] == pFuncTick))
			{
				pSysTick->msgTickTaskFlag[_return] = 1;
				//---�¼��Ѿ�ע������˳�ѭ��
				break;
			}
			//---����ĸ��¼�Ϊ��
			if (pSysTick->msgTickTaskFlag[_return]==0)
			{
				//---�ȴ��ִ�δ�ʱ������,�������������࣬�����������ݲ�����
				((SysTick->VAL)>100)?(pSysTick->msgTickTaskValid[_return]=1): (pSysTick->msgTickTaskValid[_return] = 0);
				//---ע��δ�������
				pSysTick->pMsgTickTask[_return] = pFuncTick;
				pSysTick->msgTickTaskFlag[_return] = 1;
				//---�δ����������
				if (pSysTick->msgTickTaskCount<0xFF)
				{
					pSysTick->msgTickTaskCount += 1;
				}
				//---�ҵ������¼����˳�����
				break;
			}
		}
		//---���ؽ��
		_return = (_return < SYSTICK_FUNC_TASK_MAX_NUM) ? OK_0 : ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_DeleteTickTask(void(*pFuncTick)(void))
{
	UINT8_T _return = ERROR_1;
	if (pFuncTick != NULL)
	{
		for (_return =0; _return < SYSTICK_FUNC_TASK_MAX_NUM; _return++)
		{
			//---���Ҫע�����¼��Ƿ����
			if ((pSysTick->pMsgTickTask[_return] != NULL)&&(pSysTick->pMsgTickTask[_return] == pFuncTick))
			{
				pSysTick->pMsgTickTask[_return] = NULL;
				pSysTick->msgTickTaskFlag[_return] = 0;
				//---�δ�����ļ���
				if (pSysTick->msgTickTaskCount>0)
				{
					pSysTick->msgTickTaskCount -= 1;
				}
				//---�ҵ�Ҫע�����¼����˳�����
				break;
			}
		}
		//---���ؽ��
		_return = (_return < SYSTICK_FUNC_TASK_MAX_NUM) ? OK_0 : ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ѯ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SysTick_PollTickTask(void)
{
	UINT8_T index = 0;
	for (index= 0; index< SYSTICK_FUNC_TASK_MAX_NUM; index++)
	{
		if (pSysTick->msgTickTaskFlag[index] !=0)
		{
			if (pSysTick->pMsgTickTask[index] != NULL)
			{
				//---��һ�β����㣬������Ч��ʶ����
				if (pSysTick->msgTickTaskValid[index]==1)
				{
					//---������Ч��ʶ����
					pSysTick->msgTickTaskValid[index]++;
				}
				//---������Ч��ʾ����1������ʱ���Ѿ������ˣ���ʼִ�н�������ͬʱ������Ч��ʶ
				else if (pSysTick->msgTickTaskValid[index] > 1)
				{
					//---���������ʶ��Ч
					pSysTick->msgTickTaskValid[index]=0;
					//---����ִ��
					pSysTick->pMsgTickTask[index]();
				}
				//---�����ʶ��Ч����ʼ����ִ��
				else
				{
					pSysTick->pMsgTickTask[index]();
				}
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡָ����ŵĵδ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void *SysTick_GetTickTask(UINT8_T index)
{
	if (index>= SYSTICK_FUNC_TASK_MAX_NUM)
	{
		return NULL;
	}
	return (void *)pSysTick->pMsgTickTask[index];
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ���ʱ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQDecTick(UINT32_T waitDecTick)
{
	//---�жϵ�ǰ��ֵ
	UINT32_T load = SysTick->LOAD + 1;
	UINT32_T val = SysTick->VAL;
	load >>= 1;
	//---����������ʱ
	if (val < load)
	{
		waitDecTick += 1;
	}
	//---��ʱ����
	pSysTick->msgDecTick = waitDecTick;
	//---�ȴ�ʱ�䵽��
	while (pSysTick->msgDecTick != 0)
	{
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ���ʱ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_DecTick(UINT32_T waitDecTick)
{
	//---����Ҫ�δ��ʱ��
	UINT32_T ticks = SysTick->VAL;
	//---����Ҫ��ʱ��usʱ��
	UINT32_T usDelayTicks = (ticks / SYS_CLOCK_MHZ);
	//---���ʱ����1us������ڣ�����
	if (usDelayTicks > 1)
	{
		//---��ǰ����������ֵ�ļ���
		SysTick_WaitusTick(usDelayTicks);
		//---ms�жϼ�����С
		waitDecTick -= 1;
		//---ʣ�µ���ʱʱ�䣬ǿ��װ��������Ϊ����
		ticks = (UINT32_T)(1000 - usDelayTicks - 20);
	}
	//---Ҫ��ʱ��ʱ��
	pSysTick->msgDecTick = waitDecTick;
	//---�ȴ�ʱ�䵽��
	while (pSysTick->msgDecTick != 0)
	{
		WDT_RESET();
	}
	//---���ʱ����1us������ڣ�����
	if ((ticks > 1)&&(ticks<1000))
	{
		//---��ɲ��1ms֮��Ҫ��ɵļ���ֵ
		SysTick_WaitusTick(ticks);
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
UINT32_T SysTick_GetTick(void)
{
	return pSysTick->msgIncTick;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQTask(void)
{
	//--->>>�ݼӼ���������Ҫ���ڽ���---��ʼ
	//---�ݼӼ���
	pSysTick->msgIncTick++;
	//---�ж��Ƿ����
	if (pSysTick->msgIncTick == 0)
	{
		pSysTick->msgIncTickOVF++;
	}
	//---<<<�ݼӼ���������Ҫ���ڽ���---����
	//--->>>�ݼ�����������Ҫ����ms��ʱ---��ʼ
	//---�ݼ�����
	if (pSysTick->msgDecTick != 0)
	{
		pSysTick->msgDecTick--;
	}
	//---<<<�ݼ�����������Ҫ����ms��ʱ---����
	//--->>>�δ�������ȣ���Ҫ���ڼ򵥵������л�---��ʼ
	//---��ѯִ��������
	SysTick_PollTickTask();
	//---<<<�δ�������ȣ���Ҫ���ڼ򵥵������л�---����
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_WaitTick(UINT32_T usTime)
{
	UINT32_T load = SysTick->LOAD;
	UINT32_T ctrl = SysTick->CTRL;
	UINT32_T val = SysTick->VAL;
	//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
	SysTick->CTRL = 0x00000004;
	//---����װ��ֵ
	SysTick->LOAD = usTime * SYS_CLOCK_MHZ - SYS_CLOCK_ADD;//150;//usTimer*SYS_CLOCK_MHZ - 1;
	//---���������
	SysTick->VAL = 0x00;
	//---ʹ�ܼ���������
	SysTick->CTRL |= 0x01;
	//---�ȴ�������0
	while (!(SysTick->CTRL & 0x00010000))
	{
		WDT_RESET();
	}
	//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
	SysTick->CTRL = 0x00000004;
	//---�ָ�װ��ֵ
	SysTick->LOAD = load;
	//---��������������
	SysTick->VAL = val;
	//---�ָ�����������
	SysTick->CTRL = ctrl;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ�us��ʱ�ĵ���
//////�������:
//////�������:
//////˵		�������������������ֵ��1000�����ֵ����1000�����������Զ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_WaitusTick(UINT32_T usTime)
{
	//---�������ֵ
	UINT32_T ticks = ((usTime * SYS_CLOCK_MHZ));
	//---����ֵ
	UINT32_T told = SysTick->VAL;
	UINT32_T tnow = 0;
	UINT32_T tcnt = 0;
	//---װ��ֵ
	UINT32_T tload = SysTick->LOAD;
	//---�ж��ǲ��ǳ�������
	if (usTime < 1001)
	{
		while (1)
		{
			tnow = SysTick->VAL;
			if (told != tnow)
			{
				//---������Ϊ�ݼ�������
				if (tnow < told)
				{
					tcnt += (told - tnow);
				}
				else
				{
					tcnt += (tload - tnow + told);
				}
				told = tnow;
				if (tcnt >= ticks)
				{
					break;
				}
			}
		}
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
UINT8_T SysTick_WaitSysTick(UINT32_T sysTickTime)
{
	//---�������ֵ
	UINT32_T ticks = sysTickTime;
	//---����ֵ
	UINT32_T told = SysTick->VAL;
	UINT32_T tnow = 0;
	UINT32_T tcnt = 0;
	//---װ��ֵ
	UINT32_T tload = SysTick->LOAD;
	while (1)
	{
		tnow = SysTick->VAL;
		if (told != tnow)
		{
			//---������Ϊ�ݼ�������
			if (tnow < told)
			{
				tcnt += (told - tnow);
			}
			else
			{
				tcnt += (tload - tnow + told);
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				break;
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����ж�ϵͳ�δ�ʱ���ǲ���1ms�Ķ�ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_1msIncTick(void)
{
	//---�ж�ʱ��Դ�Ƿ����8��Ƶ
	if ((SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk) != 0)
	{
		//===ʱ��Դû�н���8��Ƶ
		if (SysTick->LOAD != (SYS_CLOCK_KHZ - 1))
		{
			return ERROR_1;
		}
	}
	else
	{
		//===ʱ��Դ����8��Ƶ
		if (SysTick->LOAD != ((SYS_CLOCK_KHZ >> 3) - 1))
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ��������Ĵ�С
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTickOVF(void)
{
	return pSysTick->msgIncTickOVF;
}