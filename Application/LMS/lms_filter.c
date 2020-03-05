#include "lms_filter.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：LMS具体算法
//////输入参数:     * xn--------输入的信号序列（列向量）
//////              itr------ - 迭代次数，标量，默认为xn的长度，M < itr < sizeof(xn)
//////              * en--------误差序列（itr * 1）列向量
//////              * dn--------所期望的响应序列（列向量）
//////               * M-------- - 滤波器的阶数（标量）
//////              * mu--------收敛因子（步长）标量
//////               * W-------- - 滤波器权值矩阵，大小为M * itr
//////              * yn--------实际输出序列（列向量） * /
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float* LMS_Filter(int itr, const float* xn, const float* dn, double mu, int length)
{
    static int i = 0;
    static int k = 0;
    static float y = 0.0;
    static float en[LMS_COUNT];
    static float W[LMS_M][LMS_COUNT];
    static float x[LMS_M];
    static float yn[LMS_COUNT];
    //---创建一个en全零矩阵，en(k)表示第k次迭代时预期输出与实际输入的误差
    for (i = 0; i < itr; i++)
    {
        en[i] = 0;
    }
    //---创建一个W全零矩阵，每一行代表一个加权参量，每一列代表一次迭代
    for (i = 0; i < LMS_M; i++)
    {
        for (k = 0; k < itr; k++)
        {
            W[i][k] = 0;
        }		
    }
    //---创建一个x全零矩阵
    for (i = 0; i < LMS_M; i++)
    {
        x[i] = 0;
    }
    /*迭代计算*/
    for (k = LMS_M; k <= itr; k++)
    {
        //--- 滤波器M个抽头的输入：从xn第k-1个值倒序取出M个样点的值放入x
        //--- y为滤波器输出：W的第K-2列与x的积的和
        for (i = 0; i < LMS_M; i++)
        {
            x[i] = xn[k - i - 1];
            y += W[i][k - 2] * x[i];
        }
        //---第k次迭代的误差
        en[k - 1] = dn[k - 1] - y;  
        //---滤波器权值计算的迭代式
        for (i = 0; i < LMS_M; i++)
        {
            W[i][k - 1] = W[i][k - 2] + 2 * mu * en[k - 1] * x[i];
        }
        y = 0.0;
    }
    //---创建一个yn全无穷大矩阵，维数与xn一样
    for (i = 0; i < itr; i++)
    {
        yn[i] = 0.0;
    }
    //---求最优时滤波器的输出序列
    for (k = LMS_M; k <= length; k++)
    {
        for (i = 0; i < LMS_M; i++)
        {
            x[i] = xn[k - i - 1];
            y += W[i][itr - 1] * x[i];
        }
        yn[k - 1] = y;
        y = 0.0;
    }
    return yn;
}