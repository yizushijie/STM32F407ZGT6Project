#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===卡尔曼滤波器算法
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===定义结构体
	typedef struct _KalmanOneFilter_HandlerType			KalmanOneFilter_HandlerType;
	//===定义指针结构体
	typedef	struct _KalmanOneFilter_HandlerType			*pKalmanOneFilter_HandlerType;
	//===一阶卡尔曼滤波
	 struct _KalmanOneFilter_HandlerType
	{
		float x;		//---状态值
		float A;		//---状态转移矩阵 (A)---x(n)=A*x(n-1)+u(n),u(n)~N(0,q)
		float H;		//---测量矩阵 H---z(n)=H*x(n)+w(n),w(n)~N(0,r)
		float q;		//---系统误差 Q---预测过程噪声协方差
		float r;		//---测量误差 R---测量过程噪声协方差
		float p;		//---最小均方误差p---估计误差协方差
		float gain;		//---卡尔曼增益
	} ;

	 //===定义结构体
	 typedef struct _KalmanTwoFilter_HandlerType			KalmanTwoFilter_HandlerType;
	 //===定义指针结构体
	 typedef	struct _KalmanTwoFilter_HandlerType			*pKalmanTwoFilter_HandlerType;
	 //===二阶卡尔曼滤波
	 struct _KalmanTwoFilter_HandlerType
	 {
		 float x[2];     /* state: [0]-angle [1]-diffrence of angle, 2x1 */
		 float A[2][2];  /* X(n)=A*X(n-1)+U(n),U(n)~N(0,q), 2x2 */
		 float H[2];     /* Z(n)=H*X(n)+W(n),W(n)~N(0,r), 1x2   */
		 float q[2];     /* process(predict) noise convariance,2x1 [q0,0; 0,q1] */
		 float r;        /* measure noise convariance */
		 float p[2][2];  /* estimated error convariance,2x2 [p0 p1; p2 p3] */
		 float gain[2];  /* 2x1 */
	 };

	//===函数定义
	void KalmanOneFilter_Init(KalmanOneFilter_HandlerType* KalmanFilterX, float initMeasureX, float initMeasureP);
	float KalmanOneFilter_Filter(KalmanOneFilter_HandlerType* KalmanFilterX, float newMeasure);
	void KalmanTwoFilter_Init(KalmanTwoFilter_HandlerType* KalmanFilterX, float* initMeasureX, float(*initMeasureP)[2]);
	float KalmanTwoFilter_Filter(KalmanTwoFilter_HandlerType* KalmanFilterX, float newMeasure);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*KALMAN_FILTER_H_ */