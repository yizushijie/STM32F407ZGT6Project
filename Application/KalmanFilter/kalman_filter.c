#include "kalman_filter.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������˲�����ʼ��
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KalmanOneFilter_Init(KalmanOneFilter_HandlerType* KalmanFilterX, float initMeasureX, float initMeasureP)
{
	//---�������ĳ�ʼֵ
	KalmanFilterX->x = initMeasureX;
	//----����״̬����ֵ���ķ���ĳ�ʼֵ����ҪΪ0���ⲻ��
	KalmanFilterX->p = initMeasureP;
	KalmanFilterX->A = 1;
	KalmanFilterX->H = 1;
	//---Ԥ�⣨���̣��������� Ӱ���������ʣ����Ը���ʵ���������
	KalmanFilterX->q = 2e2;//10e-6;  
	//---�������۲⣩�������� ����ͨ��ʵ���ֶλ��
	KalmanFilterX->r = 5e2;//10e-5; 
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������˲���
//////��������� ����ֵ
//////�������:  �˲����ֵ
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float KalmanOneFilter_Filter(KalmanOneFilter_HandlerType* KalmanFilterX, float newMeasure)
{
	//---Ԥ��
	//---x�������������һ��ʱ���ĺ������ֵ��������Ϣ����
	KalmanFilterX->x = KalmanFilterX->A * KalmanFilterX->x;
	//---������������� p(n | n - 1) = A ^ 2 * p(n - 1 | n - 1) + q
	KalmanFilterX->p = KalmanFilterX->A * KalmanFilterX->A * KalmanFilterX->p + KalmanFilterX->q; 

	//---����
	KalmanFilterX->gain = KalmanFilterX->p * KalmanFilterX->H / (KalmanFilterX->p * KalmanFilterX->H * KalmanFilterX->H + KalmanFilterX->r);
	//---���ò������Ϣ���ƶ�x(t)�Ĺ��ƣ�����������ƣ����ֵҲ�������
	KalmanFilterX->x = KalmanFilterX->x + KalmanFilterX->gain * (newMeasure - KalmanFilterX->H * KalmanFilterX->x);
	//---������������
	KalmanFilterX->p = (1 - KalmanFilterX->gain * KalmanFilterX->H) * KalmanFilterX->p;

	return (KalmanFilterX->x+0.5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void KalmanTwoFilter_Init(KalmanTwoFilter_HandlerType* KalmanFilterX, float* initMeasureX, float(*initMeasureP)[2])
{
	KalmanFilterX->x[0] = initMeasureX[0];
	KalmanFilterX->x[1] = initMeasureX[1];
	KalmanFilterX->p[0][0] = initMeasureP[0][0];
	KalmanFilterX->p[0][1] = initMeasureP[0][1];
	KalmanFilterX->p[1][0] = initMeasureP[1][0];
	KalmanFilterX->p[1][1] = initMeasureP[1][1];
	//state->A       = {{1, 0.1}, {0, 1}};
	KalmanFilterX->A[0][0] = 1;
	KalmanFilterX->A[0][1] = 0.1;
	KalmanFilterX->A[1][0] = 0;
	KalmanFilterX->A[1][1] = 1;
	//state->H       = {1,0};
	KalmanFilterX->H[0] = 1;
	KalmanFilterX->H[1] = 0;
	//state->q       = {{10e-6,0}, {0,10e-6}};  /* measure noise convariance */
	KalmanFilterX->q[0] = 10e-7;
	KalmanFilterX->q[1] = 10e-7;
	KalmanFilterX->r = 10e-7;  /* estimated error convariance */
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////���������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float KalmanTwoFilter_Filter(KalmanTwoFilter_HandlerType* KalmanFilterX, float newMeasure)
{
	float temp0 = 0.0f;
	float temp1 = 0.0f;
	float temp = 0.0f;

	/* Step1: Predict */
	KalmanFilterX->x[0] = KalmanFilterX->A[0][0] * KalmanFilterX->x[0] + KalmanFilterX->A[0][1] * KalmanFilterX->x[1];
	KalmanFilterX->x[1] = KalmanFilterX->A[1][0] * KalmanFilterX->x[0] + KalmanFilterX->A[1][1] * KalmanFilterX->x[1];
	/* p(n|n-1)=A^2*p(n-1|n-1)+q */
	KalmanFilterX->p[0][0] = KalmanFilterX->A[0][0] * KalmanFilterX->p[0][0] + KalmanFilterX->A[0][1] * KalmanFilterX->p[1][0] + KalmanFilterX->q[0];
	KalmanFilterX->p[0][1] = KalmanFilterX->A[0][0] * KalmanFilterX->p[0][1] + KalmanFilterX->A[1][1] * KalmanFilterX->p[1][1];
	KalmanFilterX->p[1][0] = KalmanFilterX->A[1][0] * KalmanFilterX->p[0][0] + KalmanFilterX->A[0][1] * KalmanFilterX->p[1][0];
	KalmanFilterX->p[1][1] = KalmanFilterX->A[1][0] * KalmanFilterX->p[0][1] + KalmanFilterX->A[1][1] * KalmanFilterX->p[1][1] + KalmanFilterX->q[1];

	/* Step2: Measurement */
	/* gain = p * H^T * [r + H * p * H^T]^(-1), H^T means transpose. */
	temp0 = KalmanFilterX->p[0][0] * KalmanFilterX->H[0] + KalmanFilterX->p[0][1] * KalmanFilterX->H[1];
	temp1 = KalmanFilterX->p[1][0] * KalmanFilterX->H[0] + KalmanFilterX->p[1][1] * KalmanFilterX->H[1];
	temp = KalmanFilterX->r + KalmanFilterX->H[0] * temp0 + KalmanFilterX->H[1] * temp1;
	KalmanFilterX->gain[0] = temp0 / temp;
	KalmanFilterX->gain[1] = temp1 / temp;
	/* x(n|n) = x(n|n-1) + gain(n) * [z_measure - H(n)*x(n|n-1)]*/
	temp = KalmanFilterX->H[0] * KalmanFilterX->x[0] + KalmanFilterX->H[1] * KalmanFilterX->x[1];
	KalmanFilterX->x[0] = KalmanFilterX->x[0] + KalmanFilterX->gain[0] * (newMeasure - temp);
	KalmanFilterX->x[1] = KalmanFilterX->x[1] + KalmanFilterX->gain[1] * (newMeasure - temp);

	/* Update @p: p(n|n) = [I - gain * H] * p(n|n-1) */
	KalmanFilterX->p[0][0] = (1 - KalmanFilterX->gain[0] * KalmanFilterX->H[0]) * KalmanFilterX->p[0][0];
	KalmanFilterX->p[0][1] = (1 - KalmanFilterX->gain[0] * KalmanFilterX->H[1]) * KalmanFilterX->p[0][1];
	KalmanFilterX->p[1][0] = (1 - KalmanFilterX->gain[1] * KalmanFilterX->H[0]) * KalmanFilterX->p[1][0];
	KalmanFilterX->p[1][1] = (1 - KalmanFilterX->gain[1] * KalmanFilterX->H[1]) * KalmanFilterX->p[1][1];

	return (KalmanFilterX->x[0]+0.5);
}