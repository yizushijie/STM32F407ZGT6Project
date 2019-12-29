#ifndef AD5593_CFG_H_
#define AD5593_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===�궨��
	#define AD5593_A0								1
	#if (AD5593_A0>0)
		#define	AD5593_WADDR						0x22
		#define AD5593_RADDR						0x23
	#else
		#define	AD5593_WADDR						0x20
		#define AD5593_RADDR						0z21
	#endif
	
	//===Pointer Byte Configuration
	#define AD5593_CONF_MODE						0x00		//����ģʽ
	#define AD5593_DAC_WRITE						0x10		//DACд����
	#define AD5593_ADC_READBACK						0x40		//ADC������
	#define AD5593_DAC_READBACK						0x50		//DAC������
	#define AD5593_GPIO_READBACK					0x60		//GPIO������
	#define AD5593_REG_READBACK						0x70		//�Ĵ���������
	
	//===Control Registers
	#define AD5593_REG_NOP							0x00		//[0000]
	#define AD5593_REG_ADC_SEQ						0x02		//[0000]
	#define AD5593_REG_GEN_PUR						0x03		//[0000]
	#define AD5593_REG_ADC_PIN_CONF					0x04		//[0000]
	#define AD5593_REG_DAC_PIN_CONF					0x05		//[0000]
	#define AD5593_REG_PULL_DOWN_CONF				0x06		//[0000]---DataSheet�д���
	#define AD5593_REG_LDAC_MODE					0x07		//[0000]
	#define AD5593_REG_GPIO_WRITE_CONF				0x08		//[0000]
	#define AD5593_REG_GPIO_WRITE_DATA				0x09		//[0000]
	#define AD5593_REG_GPIO_READ_CONF				0x0A		//[0000]
	#define AD5593_REG_POWER_DOWN_REF				0x0B		//[0000]
	#define AD5593_REG_OPEN_DRAIN_CONF				0x0C		//[0000]
	#define AD5593_REG_THREE_STATE_PIN				0x0D		//[0000]
	#define AD5593_REG_NULL							0x0E		//[0000]
	#define AD5593_REG_SOFT_RESET					0x0F		//[0000]
	
	//===LDAC Mode Register
	#define AD5593_LDAC_MODE_LOAD_UPDATE			0x00		//���ز���������
	#define AD5593_LDAC_MODE_LOAD					0x01		//���ز���������
	#define AD5593_LDAC_MODE_UPDATE					0x02		//����
	#define AD5593_LDAC_MODE_NULL					0x03		//����
	
	//===I/O������,��������ָ��IOΪADC��DAC��GPIOģʽ
	#define AD5593_IO_CHANNEL_0						0x01		//IOͨ��0
	#define AD5593_IO_CHANNEL_1						0x02		//IOͨ��1
	#define AD5593_IO_CHANNEL_2						0x04		//IOͨ��2
	#define AD5593_IO_CHANNEL_3						0x08		//IOͨ��3
	#define AD5593_IO_CHANNEL_4						0x10		//IOͨ��4
	#define AD5593_IO_CHANNEL_5						0x20		//IOͨ��5
	#define AD5593_IO_CHANNEL_6						0x40		//IOͨ��6
	#define AD5593_IO_CHANNEL_7						0x80		//IOͨ��7
	
	//===DACͨ����
	#define AD5593_DAC_CHANNEL_0					0			//DACͨ��0
	#define AD5593_DAC_CHANNEL_1					1			//DACͨ��1
	#define AD5593_DAC_CHANNEL_2					2			//DACͨ��2
	#define AD5593_DAC_CHANNEL_3					3			//DACͨ��3
	#define AD5593_DAC_CHANNEL_4					4			//DACͨ��4
	#define AD5593_DAC_CHANNEL_5					5			//DACͨ��5
	#define AD5593_DAC_CHANNEL_6					6			//DACͨ��6
	#define AD5593_DAC_CHANNEL_7					7			//DACͨ��7
	
	//===ADCͨ����
	#define AD5593_ADC_CHANNEL_0					0x01
	#define AD5593_ADC_CHANNEL_1					0x02
	#define AD5593_ADC_CHANNEL_2					0x04
	#define AD5593_ADC_CHANNEL_3					0x08
	#define AD5593_ADC_CHANNEL_4					0x10
	#define AD5593_ADC_CHANNEL_5					0x20
	#define AD5593_ADC_CHANNEL_6					0x40
	#define AD5593_ADC_CHANNEL_7					0x80
	
	//===�ṹ�嶨��
	typedef struct _AD5593_HandlerType				AD5593_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _AD5593_HandlerType				*pAD5593_HandlerType;

	//===AD5593�����ݽṹ��
	struct _AD5593_HandlerType
	{
		I2C_HandlerType msgI2C;  //---ʹ�õ�I2C
	};
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*AD5593_CFG_H_ */