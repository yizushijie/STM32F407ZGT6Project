#include "pid_cfg.h"

//===����ȫ�ֱ���
PID_HandlerType			g_PID0 = { 0 };
pPID_HandlerType		pPID0 = &g_PID0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��һ��PID�����ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PID_Task0_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
	g_PID0 = pidx;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �ڶ���PID�����ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PID_Task1_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ������PID�����ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PID_Task2_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� PID��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  PID_Init(PID_HandlerType *PIDx, PID_HandlerType pidx)
{
	//---ָ���豸�ĳ�ʼ��
	if ((PIDx != NULL) && (PIDx == PID_TASK_ONE))
	{
		PID_Task0_Init(PIDx, pidx);
	}
	else if ((PIDx != NULL) && (PIDx == PID_TASK_TWO))
	{
		PID_Task1_Init(PIDx, pidx);
	}
	else if ((PIDx != NULL) && (PIDx == PID_TASK_THREE))
	{
		PID_Task2_Init(PIDx, pidx);
	}
	else
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� PIDλ��ʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float  PID_PosCalc(PID_HandlerType *PIDx, float setVal)
{
	float index = 0;

	//---�趨ֵ
	PIDx->setVal = setVal;

	//---���㵱ǰƫ��
	PIDx->err = PIDx->setVal - PIDx->actVal;

	//---���ͻ���
	if (PIDx->actVal > PIDx->uMax)
	{
		//===���ַ������
		//---��ǰƫ��ľ���ֵ
		if (ABS(PIDx->err) > PIDx->errMax)
		{
			//---���ַ���
			index = 0;
		}
		else if (ABS(PIDx->err) < PIDx->errMin)
		{
			index = 1;
			if (PIDx->err < 0)
			{
				//---��������ϵ��
				PIDx->iDelta += PIDx->err;
			}
		}
		else
		{
			index = (PIDx->errMax - ABS(PIDx->err)) / (PIDx->errDelta);
			if (PIDx->err < 0)
			{
				//---��������ϵ��
				PIDx->iDelta += PIDx->err;
			}
		}
	}
	else if (PIDx->actVal < PIDx->uMin)
	{
		//===���ַ������
		//---��ǰƫ��ľ���ֵ
		if (ABS(PIDx->err) > PIDx->errMax)
		{
			//---���ַ���
			index = 0;
		}
		else if (ABS(PIDx->err) < PIDx->errMin)
		{
			index = 1;
			if (PIDx->err > 0)
			{
				//---��������ϵ��
				PIDx->iDelta += PIDx->err;
			}
		}
		else
		{
			index = (PIDx->errMax - ABS(PIDx->err)) / (PIDx->errDelta);
			if (PIDx->err > 0)
			{
				//---��������ϵ��
				PIDx->iDelta += PIDx->err;
			}
		}
	}
	else
	{
		//---��ǰƫ��ľ���ֵ
		if (ABS(PIDx->err) > PIDx->errMax)
		{
			//---���ַ���
			index = 0;
		}
		else if (ABS(PIDx->err) < PIDx->errMin)
		{
			index = 1;

			//---��������ϵ��
			PIDx->iDelta += PIDx->err;
		}
		else
		{
			index = (PIDx->errMax - ABS(PIDx->err)) / (PIDx->errDelta);

			//---��������ϵ��
			PIDx->iDelta += PIDx->err;
		}
	}

	//---����ֵ
	PIDx->calcVal = (PIDx->kP)*(PIDx->err) + index * (PIDx->kI)*(PIDx->iDelta) + (PIDx->kD)*(PIDx->err - PIDx->err1);

	//---������ǰ����
	PIDx->err1 = PIDx->err;

	//---��ǰʵ��ֵ
	PIDx->actVal = PIDx->calcVal*PIDx->calcDelta;
	return  PIDx->actVal;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� PID����ʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float PID_IncCalc(PID_HandlerType *PIDx, float setVal)
{
	float ep, ei, ed;

	//---�趨ֵ
	PIDx->setVal = setVal;

	//---���㵱ǰƫ��
	PIDx->err = PIDx->setVal - PIDx->actVal;

	//---�����������
	ep = PIDx->err - PIDx->err1;

	//---�������
	ei = PIDx->err;

	//---΢���������
	ed = PIDx->err - 2 * (PIDx->err1) + (PIDx->err2);

	//---����ֵ
	PIDx->calcVal = (PIDx->kP)*(ep)+(PIDx->kI)*(ei)+(PIDx->kD)*(ed);

	//---��Χ�ڵ���Сֵ
	PIDx->calcVal = RANGE(PIDx->calcVal, -PIDx->uMax, PIDx->uMax);

	//---������һ�����
	PIDx->err2 = PIDx->err1;

	//---������ǰ���
	PIDx->err1 = PIDx->err;

	//---��ǰʵ��ֵ
	PIDx->actVal = PIDx->calcVal*PIDx->calcDelta;
	return  PIDx->actVal;
}