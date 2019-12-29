#ifndef	PID_CFG_H_
#define	PID_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ṹ��
	typedef struct _PID_HandlerType			PID_HandlerType;

	//===����ָ��ṹ��
	typedef struct _PID_HandlerType			*pPID_HandlerType;

	//===����ṹ��
	struct _PID_HandlerType
	{
		float kP;			//---����ϵ��
		float kI;			//---����ϵ��
		float kD;			//---΢��ϵ��
		float uMax;			//---���ֵ
		float uMin;			//---��Сֵ
		float err;			//---����ƫ��
		float err1;			//---��һ��ƫ��
		float err2;			//---�ڶ���ƫ��
		float errMax;		//---ƫ�����ֵ
		float errMin;		//---ƫ�����Сֵ
		float errDelta;		//---ƫ������ϵ��
		float iDelta;		//---����ֵ
		float setVal;		//---�趨ֵ
		float actVal;		//---ʵ��ֵ
		float calcVal;		//---����ֵ
		float calcDelta;	//---����������ƫ��ֵ
	};

	//===�����������
	#define	PID_TASK_ONE			pPID0
	#define	PID_TASK_TWO			0
	#define	PID_TASK_THREE			0
	
	//===�ⲿ���ýӿ�
	extern PID_HandlerType			g_PID0;
	extern pPID_HandlerType			pPID0;

	//===��������
	UINT8_T  PID_Init(PID_HandlerType *PIDx, PID_HandlerType pidx);
	float  PID_PosCalc(PID_HandlerType *PIDx, float setVal);
	float  PID_IncCalc(PID_HandlerType *PIDx, float setVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*PID_CFG_H_ */
