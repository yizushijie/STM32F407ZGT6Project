#ifndef COMPLIER_CFG_H_
#define COMPLIER_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ʹ�õ�ͷ�ļ�
	#include "stdbool.h"
	#include "stddef.h"
	#include "stdlib.h"
	#include "stdio.h"
	#include "string.h"
	#include "math.h"
	#include "stdarg.h"
	#include "stdint.h"
	
	//===�޷��ŵ�8λ����
	#ifndef UINT8_T
		typedef	unsigned char					UINT8_T;
	#endif
	#ifndef U8
		typedef	unsigned char					U8;
	#endif
#	ifndef u8
		typedef	unsigned char					u8;
	#endif
	#ifndef uchar
		typedef	unsigned char					uchar;
	#endif

	//===volatile�޷��ŵ�8λ����
	#ifndef VLTUINT8_T
		typedef	volatile unsigned char			VLTUINT8_T;
	#endif
	#ifndef vltuint8_t
		typedef	volatile unsigned char			vltuint8_t;
	#endif
	#ifndef VLTU8
		typedef	volatile unsigned char			VLTU8;
	#endif
	#ifndef vltu8
		typedef	volatile unsigned char			vltu8;
	#endif
	#ifndef vltuchar
		typedef	volatile unsigned char			vltuchar;
	#endif

	//===�з��ŵ�8λ����
	#ifndef INT8_T
		typedef	 char							INT8_T;
	#endif
	#ifndef S8
		typedef	 char							S8;
	#endif
	#ifndef s8
		typedef	 char							s8;
	#endif

	//===volatile�޷��ŵ�8λ����
	#ifndef VLTINT8_T
		typedef	volatile  char					VLTINT8_T;
	#endif
	#ifndef vltint8_t
		typedef	volatile  char					vltint8_t;
	#endif

	//===���ݲ�ͬλ���ĵ�Ƭ��
	#if (SIZE_MAX==0xFFFF)
	
		//===�޷��ŵ�16λ����
		#ifndef UINT16_T
				typedef	unsigned  int					UINT16_T;
		#endif
		#ifndef U16
				typedef	unsigned  int					U16;
		#endif
		#ifndef u16
				typedef	unsigned  int					u16;
		#endif
		
		#ifndef VLTUINT16_T
				typedef	volatile unsigned  int			VLTUINT16_T;
		#endif
		#ifndef vltuint16_t
				typedef	volatile unsigned  int			vltuint16_t;
		#endif
		#ifndef VLTU16
				typedef	volatile unsigned  int			VLTU16;
		#endif
		#ifndef vltu16
				typedef	volatile unsigned  int			vltu16;
		#endif
	
		//===�з��ŵ�16λ����
		#ifndef INT16_T
				typedef	signed  int						INT16_T;
		#endif
		#ifndef S16
				typedef	signed  int						S16;
		#endif
		#ifndef s16
				typedef	signed  int						s16;
		#endif
		
		#ifndef VLTINT16_T
				typedef	volatile signed  int			VLTINT16_T;
		#endif
		#ifndef vltint16_t
				typedef	volatile signed  int			vltint16_t;
		#endif
		#ifndef VLTS16
				typedef	volatile signed  int			VLTS16;
		#endif
		#ifndef vlts16
				typedef	volatile signed  int			vlts16;
		#endif
	
	#else

		#ifndef UINT16_T
				typedef	unsigned short int				UINT16_T;
		#endif
		#ifndef U16
				typedef	unsigned short int				U16;
		#endif
		#ifndef u16
				typedef	unsigned short int				u16;
		#endif
		
		#ifndef VLTUINT16_T
				typedef	volatile unsigned short int		VLTUINT16_T;
		#endif
		#ifndef vltuint16_t
				typedef	volatile unsigned short int		vltuint16_t;
		#endif
		#ifndef VLTU16
				typedef	volatile unsigned short int		VLTU16;
		#endif
		#ifndef vltu16
				typedef	volatile unsigned short int		vltu16;
		#endif
	
		//===�з��ŵ�16λ����
		#ifndef INT16_T
				typedef	signed short int				INT16_T;
		#endif
		#ifndef S16
				typedef	signed short int				S16;
		#endif
		#ifndef s16
				typedef	signed short int				s16;
		#endif
		
		#ifndef VLTINT16_T
				typedef	volatile signed short int		VLTINT16_T;
		#endif
		#ifndef vltint16_t
				typedef	volatile signed short int		vltint16_t;
		#endif
		#ifndef VLTS16
				typedef	volatile signed short int		VLTS16;
		#endif
		#ifndef vlts16
				typedef	volatile signed short int		vlts16;
		#endif
	
	#endif
	
		//===���ݲ�ͬλ���ĵ�Ƭ��
	#if (SIZE_MAX==0xFFFF)
	
		//---�޷��ŵ�32λ����
		#ifndef UINT32_T
				typedef	unsigned long int				UINT32_T;
		#endif
		#ifndef U32
				typedef	unsigned long int				U32;
		#endif
		#ifndef u32
				typedef	unsigned long int				u32;
		#endif
		
		#ifndef VLTUINT32_T
				typedef	volatile unsigned long int		VLTUINT32_T;
		#endif
		#ifndef vltuint32_t
				typedef	volatile unsigned long int		vltuint32_t;
		#endif
		#ifndef VLTU32
				typedef	volatile unsigned long int		VLTU32;
		#endif
		#ifndef vltu32
				typedef	volatile unsigned long	int		vltu32;
		#endif
	
		//===�з��ŵ�32λ����
		#ifndef INT32_T
				typedef	signed	long int				INT32_T;
		#endif
		#ifndef S32
				typedef	signed	long int				S32;
		#endif
		#ifndef s32
				typedef	signed	long int				s32;
		#endif
		
		#ifndef VLTINT32_T
				typedef	volatile signed	long int		VLTINT32_T;
		#endif
		#ifndef vltint32_t
				typedef	volatile signed	long int		vltint32_t;
		#endif
		#ifndef VLTS32
				typedef	volatile signed	long int		VLTS32;
		#endif
		#ifndef vlts32
				typedef	volatile signed	long int		vlts32;
		#endif
	
	#else
	
		//===�޷��ŵ�32λ����
		#ifndef UINT32_T
				typedef	unsigned  int					UINT32_T;
		#endif
		#ifndef U32
				typedef	unsigned  int					U32;
		#endif
		#ifndef u32
				typedef	unsigned  int					u32;
		#endif
		
		#ifndef VLTUINT32_T
				typedef	volatile unsigned  int			VLTUINT32_T;
		#endif
		#ifndef vltuint32_t
				typedef	volatile unsigned  int			vltuint32_t;
		#endif
		#ifndef VLTU32
				typedef	volatile unsigned  int			VLTU32;
		#endif
		#ifndef vltu32
				typedef	volatile unsigned  int			vltu32;
		#endif
		
		//===�з��ŵ�32λ����
		#ifndef INT32_T
				typedef	signed int						INT32_T;
		#endif
		#ifndef S32
				typedef	signed int						S32;
		#endif
		#ifndef s32
				typedef	signed int						s32;
		#endif
		
		#ifndef VLTINT32_T
				typedef	volatile signed	int				VLTINT32_T;
		#endif
		#ifndef vltint32_t
				typedef	volatile signed	int				vltint32_t;
		#endif
		#ifndef VLTS32
				typedef	volatile signed	int				VLTS32;
		#endif
		#ifndef vlts32
				typedef	volatile signed	int				vlts32;
		#endif
	
	#endif

	//===�޷��ŵ�64λ����
	#ifndef UINT64_T
		typedef	unsigned long long int				UINT64_T;
	#endif
	#ifndef U64
		typedef	unsigned long long int				U64;
	#endif
	#ifndef u64
		typedef	unsigned long long int				u64;
	#endif
	
	#ifndef VLTUINT64_T
		typedef	volatile unsigned long long int		VLTUINT64_T;
	#endif
	#ifndef vltuint64_t
		typedef	volatile unsigned long long int		vltuint64_t;
	#endif
	#ifndef VLTU64
		typedef	volatile unsigned long long int		VLTU64;
	#endif
	#ifndef vltu64
		typedef	volatile unsigned long long int		vltu64;
	#endif

	//===�з��ŵ�64λ����
	#ifndef INT64_T
		typedef	signed long long int				INT64_T;
	#endif
	#ifndef S64
		typedef	signed long long int				S64;
	#endif
	#ifndef s64
		typedef signed long long int				s64;
	#endif
	
	#ifndef VLTINT64_T
		typedef	volatile signed long long int		VLTINT64_T;
	#endif
	#ifndef vltint64_t
		typedef	volatile signed long long int		vltint64_t;
	#endif
	#ifndef VLTS64
		typedef	volatile signed long long int		VLTS64;
	#endif
	#ifndef vlts64
		typedef	volatile signed long long int		vlts64;
	#endif

	//===8bit�޷��ŵ�������
	typedef union
	{
		struct
		{
			UINT8_T b0 : 1;
			UINT8_T b1 : 1;
			UINT8_T b2 : 1;
			UINT8_T b3 : 1;
			UINT8_T b4 : 1;
			UINT8_T b5 : 1;
			UINT8_T b6 : 1;
			UINT8_T b7 : 1;
		};
		UINT8_T bit;
	}UNION_UINT8_T;

	//===8bit�з��ŵ�������
	typedef union
	{
		struct
		{
			INT8_T b0 : 1;
			INT8_T b1 : 1;
			INT8_T b2 : 1;
			INT8_T b3 : 1;
			INT8_T b4 : 1;
			INT8_T b5 : 1;
			INT8_T b6 : 1;
			INT8_T b7 : 1;
		};
		INT8_T bit;
	}UNION_INT8_T;

	//===16bit�޷��ŵ�������
	typedef union
	{
		struct
		{
			UINT8_T b0 : 1;
			UINT8_T b1 : 1;
			UINT8_T b2 : 1;
			UINT8_T b3 : 1;
			UINT8_T b4 : 1;
			UINT8_T b5 : 1;
			UINT8_T b6 : 1;
			UINT8_T b7 : 1;
			UINT8_T b8 : 1;
			UINT8_T b9 : 1;
			UINT8_T b10 : 1;
			UINT8_T b11 : 1;
			UINT8_T b12 : 1;
			UINT8_T b13 : 1;
			UINT8_T b14 : 1;
			UINT8_T b15 : 1;
		};
		UINT8_T  bit[2];
		UINT16_T wBit;
	}UNION_UINT16_T;

	//===16bit�з��ŵ�������
	typedef union
	{
		struct
		{
			INT8_T b0 : 1;
			INT8_T b1 : 1;
			INT8_T b2 : 1;
			INT8_T b3 : 1;
			INT8_T b4 : 1;
			INT8_T b5 : 1;
			INT8_T b6 : 1;
			INT8_T b7 : 1;
			INT8_T b8 : 1;
			INT8_T b9 : 1;
			INT8_T b10 : 1;
			INT8_T b11 : 1;
			INT8_T b12 : 1;
			INT8_T b13 : 1;
			INT8_T b14 : 1;
			INT8_T b15 : 1;
		};
		INT8_T  bit[2];
		INT16_T wBit;
	}UNION_INT16_T;

	//===32bit�޷��ŵ�������
	typedef union
	{
		struct
		{
			UINT8_T b0 : 1;
			UINT8_T b1 : 1;
			UINT8_T b2 : 1;
			UINT8_T b3 : 1;
			UINT8_T b4 : 1;
			UINT8_T b5 : 1;
			UINT8_T b6 : 1;
			UINT8_T b7 : 1;
			UINT8_T b8 : 1;
			UINT8_T b9 : 1;
			UINT8_T b10 : 1;
			UINT8_T b11 : 1;
			UINT8_T b12 : 1;
			UINT8_T b13 : 1;
			UINT8_T b14 : 1;
			UINT8_T b15 : 1;
			UINT8_T b16 : 1;
			UINT8_T b17 : 1;
			UINT8_T b18 : 1;
			UINT8_T b19 : 1;
			UINT8_T b20 : 1;
			UINT8_T b21 : 1;
			UINT8_T b22 : 1;
			UINT8_T b23 : 1;
			UINT8_T b24 : 1;
			UINT8_T b25 : 1;
			UINT8_T b26 : 1;
			UINT8_T b27 : 1;
			UINT8_T b28 : 1;
			UINT8_T b29 : 1;
			UINT8_T b30 : 1;
			UINT8_T b31 : 1;
		};
		UINT8_T  bit[4];
		UINT16_T wBit[2];
		UINT32_T dWBit;
	}UNION_UINT32_T;

	//===32bit�з��ŵ�������
	typedef union
	{
		struct
		{
			INT8_T b0 : 1;
			INT8_T b1 : 1;
			INT8_T b2 : 1;
			INT8_T b3 : 1;
			INT8_T b4 : 1;
			INT8_T b5 : 1;
			INT8_T b6 : 1;
			INT8_T b7 : 1;
			INT8_T b8 : 1;
			INT8_T b9 : 1;
			INT8_T b10 : 1;
			INT8_T b11 : 1;
			INT8_T b12 : 1;
			INT8_T b13 : 1;
			INT8_T b14 : 1;
			INT8_T b15 : 1;
			INT8_T b16 : 1;
			INT8_T b17 : 1;
			INT8_T b18 : 1;
			INT8_T b19 : 1;
			INT8_T b20 : 1;
			INT8_T b21 : 1;
			INT8_T b22 : 1;
			INT8_T b23 : 1;
			INT8_T b24 : 1;
			INT8_T b25 : 1;
			INT8_T b26 : 1;
			INT8_T b27 : 1;
			INT8_T b28 : 1;
			INT8_T b29 : 1;
			INT8_T b30 : 1;
			INT8_T b31 : 1;
		};
		INT8_T  bit[4];
		INT16_T wBit[2];
		INT32_T dWBit;
	}UNION_INT32_T;

	//===���ô���ö��
	typedef enum
	{
		OK_0 = 0,
		ERROR_1 = 1,
		ERROR_2 = 2,
		ERROR_3 = 3,
		ERROR_4 = 4,
		ERROR_5 = 5,
		ERROR_6 = 6,
		ERROR_7 = 7,
		ERROR_8 = 8,
		ERROR_9 = 9,
		ERROR_10 = 10,
		ERROR_11 = 11,
		ERROR_12 = 12,
		ERROR_13 = 13,
		ERROR_14 = 14,
		ERROR_15 = 15,
		ERROR_16 = 16,
		ERROR_17 = 17,
		ERROR_18 = 18,
		ERROR_19 = 19,
		ERROR_20 = 20,
		ERROR_21 = 21,
		ERROR_22 = 22,
		ERROR_23 = 23,
		ERROR_24 = 24,
		ERROR_25 = 25,
		ERROR_26 = 26,
		ERROR_27 = 27,
		ERROR_28 = 28,
		ERROR_29 = 29,
		ERROR_30 = 30,
		ERROR_31 = 31,
		ERROR_32 = 32,
		ERROR_33 = 33,
		ERROR_34 = 34,
		ERROR_35 = 35,
		ERROR_36 = 36,
		ERROR_37 = 37,
		ERROR_38 = 38,
		ERROR_39 = 39,
		ERROR_40 = 40,
		ERROR_41 = 41,
		ERROR_42 = 42,
		ERROR_43 = 43,
		ERROR_44 = 44,
		ERROR_45 = 45,
		ERROR_46 = 46,
		ERROR_47 = 47,
		ERROR_48 = 48,
		ERROR_49 = 49,
		ERROR_50 = 50,
	}FuncSTATE;

	//===�ṹ�嶨��
	typedef struct _RTC_HandlerType					RTC_HandleType;
	//===����ָ��ṹ��
	typedef struct _RTC_HandlerType					*pRTC_HandlerType;
	//===ʱ�ӽṹ��Ķ���
	struct _RTC_HandlerType
	{
		UINT8_T second;																																								//---��
		UINT8_T minute;																																								//---��
		UINT8_T hour;																																								//---ʱ
		UINT8_T day;																																								//---��
		UINT8_T week;																																								//---����
		UINT8_T month;																																								//---��
		UINT8_T year;																																								//---��
		UINT8_T century;																																							//---����
		UINT8_T time24H;																																							//---24H��ʽ��0---12Сʱ��1---24Сʱ
		UINT32_T secondTick;																																						//---��仯�ļ�¼
	};

	//===���ú궨��
	typedef enum
	{
		IDLE = 0,
		BUSY = 1,
	}WorkSTATE;

	//===����bool����
	#if !defined(bool)
		#define false	0
		#define true	1
			typedef enum
			{
				false=0,
				true,
			}bool;
	#endif
	
	//===���ݻ�������
	#define MAX(a,b)								( (a) > (b) ? (a) : (b) )																										//---ȡ���ֵ
	#define MIN(a,b)								( (a) < (b) ? (a) : (b) )																										//---ȡ��Сֵ
	#define ODD(x)									((x&0x01)==1?1:0)																												//---У���ǲ�������
	#define EVEN(x)									((x&0x01)!=1?1:0)																												//---У���ǲ���ż��
	#define ABS(a)									( (a)>=0?(a):-(a) )																												//---���ľ���ֵ
	#define RANGE(x, a, b)							( MIN( MAX( x, a ), b ) )																										//---ȡ�������е���Сֵ
	#define ABS_SUB(a,b)							( (a)>(b)?((a)-(b)):((b)-(a)) )																									//---�������ľ���ֵ��
	#define	VERSION_DATE_SIZE						12																																//---����__DATE__��ȡ��ǰ���ڣ�ռ��12���ֽڣ������ַ���������
	#define VERSION_TIME_SIZE						9																																//---����__TIME__��ȡ��ǰʱ�䣬ռ��9���ֽڣ������ַ���������	
	#define YEAR_TYPE(a)							( ((a%100!=0)&&(a%4==0))||(a%400==0) )																							//---�ж��Ƿ�������
	
	//////////////////////////////////////////////////////////////////////////
	//===����MCU���ͺŲ�ͬ��ѡ��ͬ��ͷ�ļ�����ʱ֧��STM32��AVR
	//#define USE_MCU_AVR																																							//---ѡ��AVR�ͺ�
	#define USE_MCU_STM32																																							//---ѡ��STM32�ͺ�
	//////////////////////////////////////////////////////////////////////////
	//===����MCU�ͺţ�������ͬ��ͷ�ļ�
	#if defined(USE_MCU_STM32)
		#include "stm32_cfg.h"
	#elif defined(USE_MCU_AVR)
		#include "avr_cfg.h"
	#else
		#error "��֧���ͺŵ�MCU."
	#endif 
	
	//===ͨ������ʱ�䣬����ʵ�ְ汾����
	#define USE_COMPLIER_VERSION																																					//---ʹ�ñ�����ʵ�ֵİ汾
	//===�����ʱ���������Ϣ
	#ifdef USE_COMPLIER_VERSION
		//===�ⲿ���ýӿ�
		extern const UINT8_T  g_VersionDate[VERSION_DATE_SIZE];
		extern const UINT8_T  g_VersionTime[VERSION_TIME_SIZE];
	#endif
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* COMPLIER_CFG_H */