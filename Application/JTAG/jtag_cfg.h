#ifndef JTAG_CFG_H_
#define JTAG_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "spi_task.h"
	#include "systick_task.h"
	#include "delay_task.h"
	#include "my_malloc.h"
	#include "hw_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����JTAG״̬���ֵ�ʱ��״̬
	#define JTAG_STATE_TIME_OUT_MS				500
	//===�����Ƿ�ʹ�õ�ƽת��оƬ����OE���ƶ˵�
	#define JTAG_USE_lEVEL_SHIFT 	
	//===����ʹ���˸�ѹHVSETģʽ
	#define JTAG_USE_HV_RESET

	//===JTAG��GPIO�Ĳ�������
	#define	JTAG_GPIO_STATE(tp)					GPIO_GET_STATE(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_OUT_1(tp)					GPIO_OUT_1(tp.msgGPIOPort,tp.msgGPIOBit)
	#define	JTAG_GPIO_OUT_0(tp)					GPIO_OUT_0(tp.msgGPIOPort,tp.msgGPIOBit)
	//===TCK��������
	#define JTAG_TCK_PULSE(tck)					(	JTAG_GPIO_OUT_1(tck->msgTCK),\
													DELAY_NOP_COUNT(4),\
													tck->msgDelayus(tck->msgPluseWidth),\
													JTAG_GPIO_OUT_0(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth)\
												)
	//===TMS���1�仯һ��
	#define JTAG_TMS_OUT_1(tck)					(	JTAG_GPIO_OUT_1(tck->msgTMS),\
													JTAG_GPIO_OUT_1(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth),\
													JTAG_GPIO_OUT_0(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth)\
												)
	//===TMS���0�仯һ��
	#define JTAG_TMS_OUT_0(tck)					(	JTAG_GPIO_OUT_0(tck->msgTMS),\
													JTAG_GPIO_OUT_1(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth),\
													JTAG_GPIO_OUT_0(tck->msgTCK),\
													tck->msgDelayus(tck->msgPluseWidth)\
												)

	//===TAP������״̬
	typedef enum
	{
		TEST_LOGIC_RESET	= 0,
		RUN_TEST_IDLE		= 1,

		SELECT_DR_SCAN		= 2,
		CAPTURE_DR			= 3,
		SHIFT_DR			= 4,
		EXIT1_DR			= 5,
		PAUSE_DR			= 6,
		EXIT2_DR			= 7,
		UPDATE_DR			= 8,

		SELECT_IR_SCAN		= 12,
		CAPTURE_IR			= 13,
		SHIFT_IR			= 14,
		EXIT1_IR			= 15,
		PAUSE_IR			= 16,
		EXIT2_IR			= 17,
		UPDATE_IR			= 18,
	}TAP_STATE;

	//===JTAG��Դָ��
	typedef enum
	{
		EXTEST				= 0x00,
		IDCODE				= 0x01,
		SAMPLE				= 0x02,
		AVR_RESET			= 0x0C,
		BYPASS				= 0x0F,
		PROG_ENABLE			= 0x04,
		PROG_COMMANDS		= 0x05,
		PROG_PAGELOAD		= 0x06,
		PROG_PAGEREAD		= 0x07,

		PRIVATEE0			= 0x08,																	//---ǿ�ƶϵ�
		PRIVATEE1			= 0x09,																	//---����
		PRIVATEE2			= 0x0A,																	//---ָ��ִ��
		PRIVATEE3			= 0x0B,																	//---����OCD�Ĵ���
	}TAP_CMD;

	//===����ṹ��
	typedef struct _JTAG_HandlerType			JTAG_HandlerType;
	//===����ָ��ṹ��
	typedef struct _JTAG_HandlerType			* pJTAG_HandlerType;
	//===�ṹ�����
	struct _JTAG_HandlerType
	{
		TAP_STATE			msgTapState;															//---��ǰjtag��״̬
		UINT8_T				msgWaitms;																//---���֮�����ʱ��������λ��ms
		GPIO_HandlerType	msgTDI;																	//---TDIʹ�õĶ˿�
		GPIO_HandlerType	msgTDO;																	//---TDOʹ�õĶ˿�
		GPIO_HandlerType	msgTCK;																	//---TCKʹ�õĶ˿�
		GPIO_HandlerType	msgTMS;																	//---TMSʹ�õĶ˿�
#ifdef JTAG_USE_HV_RESET
		void (*msgPortRst)(UINT8_T rstState);														//---��ѹģʽ����RST�˿ڵĺ���
#else
		GPIO_HandlerType	msgRST;																	//---RSTʹ�õĶ˿�,Ӳ����λ�˿�
#endif
		
	#ifdef JTAG_USE_lEVEL_SHIFT
		GPIO_HandlerType	msgOE;																	//---OEʹ�õĶ˿ڣ����ڿ��Ƶ�ƽװ���Ŀ���
	#endif
		UINT8_T				msgJtagCmd;																//---�Ƿ����JTAGָ��PROG_COMMANDS��0---λʹ�ã�1---ʹ��
		UINT8_T				msgState;																//---���״̬��0---����״̬��1---���״̬
		UINT8_T				msgInit;																//---�ж��Ƿ��ʼ������ 0---δ��ʼ����1---��ʼ��
		UINT8_T				msgEepromIsPageMode;													//---eeprom�Ƿ�֧��ҳ���ģʽ��0---��֧�֣�1---֧��
		UINT16_T			msgFlashPerPageWordSize;												//---Flash��ÿҳ����
		UINT16_T			msgEerpomPerPageByteSize;												//---Eeprom��ÿҳ�ֽ���
		UINT16_T			msgPageWordIndex;														//---�����������
		UINT16_T			msgPluseWidth;															//---�Ǳ��״̬��TCK��������
		UINT16_T			msgIntervalTime;														//---��ѯʱ����,��λ��ms
		UINT32_T			msgRecordTime;															//---��¼��ʱ�����
		void(*msgDelayus)(UINT32_T delay);															//---us��ʱ����
		void(*msgDelayms)(UINT32_T delay);															//---ms��ʱ����
		UINT32_T(*msgTimeTick)(void);															//---���ڳ�ʱ����
		//SPI_HandlerType msgSPI;																	//---ʹ�õ�SPIģʽ
	};

	//===����״̬
	#define	JTAG_PROG_NONE						0													//---�ޱ������
	#define JTAG_PROG_PREPARE					1													//---���׼����
	#define JTAG_PROG_CMD						2													//---ʹ�ܱ������
	#define JTAG_PROG_PAGELOAD					3													//---��Ч���Flashģʽ
	#define JTAG_PROG_PAGEREAD					4													//---��Ч��ȡFlashģʽ
	#define JTAG_PROG_READ_EEPROM				5													//---��ȡEeprom����
	#define JTAG_PROG_READ_FLASH				6													//---��ȡFlash����
	#define JTAG_PROG_READ_ROM					7													//---��ȡROM��Ϣ
	#define JTAG_PROG_WRITE_EEPROM				8													//---���Eeprom����
	#define JTAG_PROG_WRITE_FLASH				9													//---���Flash����


	//===����RST��״̬
	#define JTAG_RST_TO_HZ						0													//---RST���ڸ���״̬
	#define JTAG_RST_TO_GND						1													//---RST���ڽӵ�
	#define JTAG_RST_TO_VCC						2													//---RST�ӹ�����ѹ

	//===������
	#define JTAG_TASK_ONE						pJtagDevice0										//---����1
	#define JTAG_TASK_TWO						0													//---����2
	#define JTAG_TASK_THREE						0													//---����3

	//===�ⲿ���ýӿ�
	extern JTAG_HandlerType						g_JtagDevice0;
	extern pJTAG_HandlerType					pJtagDevice0;

	//===��������
	UINT8_T JTAG_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));	
	UINT8_T JTAG_EnterProg(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_ExitProg(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_RemoveWatch(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_RefreshWatch(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_AddWatch(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_SetIntervalTime(JTAG_HandlerType* JTAGx, UINT16_T intervalTime);
	UINT16_T JTAG_GetIntervalTime(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_EraseChip(JTAG_HandlerType* JTAGx);
	UINT8_T JTAG_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal);
	UINT8_T JTAG_ReadChipID(JTAG_HandlerType* JTAGx, UINT8_T* pVal);
	UINT8_T JTAG_ReadChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal);
	UINT8_T JTAG_ReadChipCalibration(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T length);
	UINT8_T JTAG_ReadChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse);
	UINT8_T JTAG_ReadChipLock(JTAG_HandlerType* JTAGx, UINT8_T* pVal);
	UINT8_T JTAG_ReadChipRom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T addr, UINT16_T length);
	UINT8_T JTAG_WriteChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse);
	UINT8_T JTAG_WriteChipLock(JTAG_HandlerType* JTAGx, UINT8_T lockVal);
	UINT8_T JTAG_ReadChipEepromAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T JTAG_ReadChipEepromLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT16_T addr, UINT16_T length);
	UINT8_T JTAG_WriteChipEeprom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum);
	UINT8_T JTAG_ReadChipFlashAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T JTAG_ReadChipFlashLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT32_T addr, UINT16_T length);
	UINT8_T JTAG_WriteChipFlashPage(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T JTAG_CheckChipFlashEmpty(JTAG_HandlerType* JTAGx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL);
	UINT8_T JTAG_CheckChipFlashEmptyLong(JTAG_HandlerType* JTAGx, UINT16_T pageByteSize, UINT16_T pageNum);
	UINT8_T JTAG_CheckChipEepromEmpty(JTAG_HandlerType* JTAGx, UINT8_T byteSize, UINT8_T num);
	UINT8_T JTAG_SetConfigInfo(JTAG_HandlerType* JTAGx, UINT8_T* pVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*JTAG_CFG_H_ */