#include "kalman_filter.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：卡尔曼滤波器初始化
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void KalmanOneFilter_Init(KalmanOneFilter_HandlerType* KalmanFilterX, float initMeasureX, float initMeasureP)
{
	//---待测量的初始值
	KalmanFilterX->x = initMeasureX;
	//----后验状态估计值误差的方差的初始值（不要为0问题不大）
	KalmanFilterX->p = initMeasureP;
	KalmanFilterX->A = 1;
	KalmanFilterX->H = 1;
	//---预测（过程）噪声方差 影响收敛速率，可以根据实际需求给出
	KalmanFilterX->q = 2e2;//10e-6;  
	//---测量（观测）噪声方差 可以通过实验手段获得
	KalmanFilterX->r = 5e2;//10e-5; 
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：卡尔曼滤波器
//////输入参数： 测量值
//////输出参数:  滤波后的值
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float KalmanOneFilter_Filter(KalmanOneFilter_HandlerType* KalmanFilterX, float newMeasure)
{
	//---预测
	//---x的先验估计由上一个时间点的后验估计值和输入信息给出
	KalmanFilterX->x = KalmanFilterX->A * KalmanFilterX->x;
	//---计算先验均方差 p(n | n - 1) = A ^ 2 * p(n - 1 | n - 1) + q
	KalmanFilterX->p = KalmanFilterX->A * KalmanFilterX->A * KalmanFilterX->p + KalmanFilterX->q; 

	//---计算
	KalmanFilterX->gain = KalmanFilterX->p * KalmanFilterX->H / (KalmanFilterX->p * KalmanFilterX->H * KalmanFilterX->H + KalmanFilterX->r);
	//---利用残余的信息改善对x(t)的估计，给出后验估计，这个值也就是输出
	KalmanFilterX->x = KalmanFilterX->x + KalmanFilterX->gain * (newMeasure - KalmanFilterX->H * KalmanFilterX->x);
	//---计算后验均方差
	KalmanFilterX->p = (1 - KalmanFilterX->gain * KalmanFilterX->H) * KalmanFilterX->p;

	return (KalmanFilterX->x+0.5);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数：
//////输出参数:
//////说		明：
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