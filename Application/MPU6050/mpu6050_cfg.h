#ifndef MPU6050_CFG_H_
#define MPU6050_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "gpio_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===I2C地址的配置
	#define MPU6050_ADDRESS_AD0_LOW						0x68	// address pin low (GND), 
	#define MPU6050_ADDRESS_AD0_HIGH					0x69	// address pin high (VCC)
	#define MPU6050_DEFAULT_ADDRESS						MPU6050_ADDRESS_AD0_LOW
	//===寄存器地址
	#define MPU6050_REG_ADDR_XG_OFFS_TC					0x00	//[7] PWR_MODE, [6:1] XG_O
	#define MPU6050_REG_ADDR_YG_OFFS_TC					0x01	//[7] PWR_MODE, [6:1] YG_O
	#define MPU6050_REG_ADDR_ZG_OFFS_TC					0x02	//[7] PWR_MODE, [6:1] ZG_O
	#define MPU6050_REG_ADDR_X_FINE_GAIN				0x03	//[7:0] X_FINE_GAIN
	#define MPU6050_REG_ADDR_Y_FINE_GAIN				0x04	//[7:0] Y_FINE_GAIN
	#define MPU6050_REG_ADDR_Z_FINE_GAIN				0x05	//[7:0] Z_FINE_GAIN
	#define MPU6050_REG_ADDR_XA_OFFS_H					0x06	//[15:0] XA_OFFS
	#define MPU6050_REG_ADDR_XA_OFFS_L_TC				0x07
	#define MPU6050_REG_ADDR_YA_OFFS_H					0x08	//[15:0] YA_OFFS
	#define MPU6050_REG_ADDR_YA_OFFS_L_TC				0x09
	#define MPU6050_REG_ADDR_ZA_OFFS_H					0x0A	//[15:0] ZA_OFFS
	#define MPU6050_REG_ADDR_ZA_OFFS_L_TC				0x0B				
	#define MPU6050_REG_ADDR_SELF_TEST_X				0x0D															//---X自检	
	#define MPU6050_REG_ADDR_SELF_TEST_Y				0x0E															//---Y自检	
	#define MPU6050_REG_ADDR_SELF_TEST_Z				0x0F															//---Z自检
	#define MPU6050_REG_ADDR_SELF_TEST_A				0x10															//---A自检
	#define MPU6050_REG_ADDR_XG_OFFS_USRH				0x13	//[15:0] XG_OFFS_USR
	#define MPU6050_REG_ADDR_XG_OFFS_USRL				0x14
	#define MPU6050_REG_ADDR_YG_OFFS_USRH				0x15	//[15:0] YG_OFFS_USR
	#define MPU6050_REG_ADDR_YG_OFFS_USRL				0x16
	#define MPU6050_REG_ADDR_ZG_OFFS_USRH				0x17	//[15:0] ZG_OFFS_USR
	#define MPU6050_REG_ADDR_ZG_OFFS_USRL				0x18	
	#define MPU6050_REG_ADDR_SMPLRT_DIV					0x19															//---采样平率分频器
	#define MPU6050_REG_ADDR_CONFIG						0x1A															//---配置寄存器
	#define MPU6050_REG_ADDR_GYRO_CONFIG				0x1B															//---陀螺仪配置
	#define MPU6050_REG_ADDR_ACCEL_CONFIG				0x1C															//---加速度配置
	#define MPU6050_REG_ADDR_FF_THR						0x1D
	#define MPU6050_REG_ADDR_FF_DUR						0x1E
	#define MPU6050_REG_ADDR_MOT_THR					0x1F															//---运动检测阈值
	#define MPU6050_REG_ADDR_MOT_DUR					0x20
	#define MPU6050_REG_ADDR_ZRMOT_THR					0x21
	#define MPU6050_REG_ADDR_ZRMOT_DUR					0x22
	#define MPU6050_REG_ADDR_FIFO_EN					0x23															//---FIFO使能
	#define MPU6050_REG_ADDR_I2C_MST_CTRL				0x24															//---主机控制
	#define MPU6050_REG_ADDR_I2C_SLV0_ADDR				0x25															//---从机0
	#define MPU6050_REG_ADDR_I2C_SLV0_REG				0x26
	#define MPU6050_REG_ADDR_I2C_SLV0_CTRL				0x27
	#define MPU6050_REG_ADDR_I2C_SLV1_ADDR				0x28															//---从机1
	#define MPU6050_REG_ADDR_I2C_SLV1_REG				0x29
	#define MPU6050_REG_ADDR_I2C_SLV1_CTRL				0x2A
	#define MPU6050_REG_ADDR_I2C_SLV2_ADDR				0x2B															//---从机2
	#define MPU6050_REG_ADDR_I2C_SLV2_REG				0x2C
	#define MPU6050_REG_ADDR_I2C_SLV2_CTRL				0x2D
	#define MPU6050_REG_ADDR_I2C_SLV3_ADDR				0x2E															//---从机3
	#define MPU6050_REG_ADDR_I2C_SLV3_REG				0x2F
	#define MPU6050_REG_ADDR_I2C_SLV3_CTRL				0x30
	#define MPU6050_REG_ADDR_I2C_SLV4_ADDR				0x31															//---从机4
	#define MPU6050_REG_ADDR_I2C_SLV4_REG				0x32
	#define MPU6050_REG_ADDR_I2C_SLV4_DO				0x33
	#define MPU6050_REG_ADDR_I2C_SLV4_CTRL				0x34
	#define MPU6050_REG_ADDR_I2C_SLV4_DI				0x35
	#define MPU6050_REG_ADDR_I2C_MST_STATUS				0x36															//---主机状态
	#define MPU6050_REG_ADDR_INT_PIN_CFG				0x37															//---中断引脚/旁路有效，使能配置
	#define MPU6050_REG_ADDR_INT_ENABLE					0x38															//---中断使能
	#define MPU6050_REG_ADDR_DMP_INT_STATUS				0x39															//---DMP中断状态
	#define MPU6050_REG_ADDR_INT_STATUS					0x3A															//---中断状态
	#define MPU6050_REG_ADDR_ACCEL_XOUT_H				0x3B															//---X轴加速度测量值
	#define MPU6050_REG_ADDR_ACCEL_XOUT_L				0x3C															
	#define MPU6050_REG_ADDR_ACCEL_YOUT_H				0x3D															//---Y轴加速度测量值
	#define MPU6050_REG_ADDR_ACCEL_YOUT_L				0x3E
	#define MPU6050_REG_ADDR_ACCEL_ZOUT_H				0x3F															//---Z轴加速度测量值
	#define MPU6050_REG_ADDR_ACCEL_ZOUT_L				0x40
	#define MPU6050_REG_ADDR_TEMP_OUT_H					0x41															//---温度测量值
	#define MPU6050_REG_ADDR_TEMP_OUT_L					0x42
	#define MPU6050_REG_ADDR_GYRO_XOUT_H				0x43															//---X轴陀螺仪测量值
	#define MPU6050_REG_ADDR_GYRO_XOUT_L				0x44
	#define MPU6050_REG_ADDR_GYRO_YOUT_H				0x45															//---Y轴陀螺仪测量值
	#define MPU6050_REG_ADDR_GYRO_YOUT_L				0x46
	#define MPU6050_REG_ADDR_GYRO_ZOUT_H				0x47															//---Z轴陀螺仪测量值
	#define MPU6050_REG_ADDR_GYRO_ZOUT_L				0x48
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_00			0x49															//---外部传感器数据0
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_01			0x4A															//---外部传感器数据1
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_02			0x4B															//---外部传感器数据2
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_03			0x4C															//---外部传感器数据3
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_04			0x4D															//---外部传感器数据4
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_05			0x4E															//---外部传感器数据5
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_06			0x4F															//---外部传感器数据6
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_07			0x50															//---外部传感器数据7
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_08			0x51															//---外部传感器数据8
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_09			0x52															//---外部传感器数据9
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_10			0x53															//---外部传感器数据10
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_11			0x54															//---外部传感器数据11
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_12			0x55															//---外部传感器数据12
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_13			0x56															//---外部传感器数据13
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_14			0x57															//---外部传感器数据14
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_15			0x58															//---外部传感器数据15
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_16			0x59															//---外部传感器数据16
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_17			0x5A															//---外部传感器数据17
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_18			0x5B															//---外部传感器数据18
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_19			0x5C															//---外部传感器数据19
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_20			0x5D															//---外部传感器数据20
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_21			0x5E															//---外部传感器数据21
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_22			0x5F															//---外部传感器数据22
	#define MPU6050_REG_ADDR_EXT_SENS_DATA_23			0x60															//---外部传感器数据23
	#define MPU6050_REG_ADDR_MOT_DETECT_STATUS			0x61															//---运动检测状态
	#define MPU6050_REG_ADDR_I2C_SLV0_DO				0x63															//---从机0数据输出
	#define MPU6050_REG_ADDR_I2C_SLV1_DO				0x64															//---从机1数据输出
	#define MPU6050_REG_ADDR_I2C_SLV2_DO				0x65															//---从机2数据输出
	#define MPU6050_REG_ADDR_I2C_SLV3_DO				0x66															//---从机3数据输出
	#define MPU6050_REG_ADDR_I2C_MST_DELAY_CTRL			0x67															//---主机延时管理
	#define MPU6050_REG_ADDR_SIGNAL_PATH_RESET			0x68															//---信号通道复位
	#define MPU6050_REG_ADDR_MOT_DETECT_CTRL			0x69															//---运动检测控制
	#define MPU6050_REG_ADDR_USER_CTRL					0x6A															//---用户配置
	#define MPU6050_REG_ADDR_PWR_MGMT_1					0x6B															//---电源管理1
	#define MPU6050_REG_ADDR_PWR_MGMT_2					0x6C															//---电源管理2
	#define MPU6050_REG_ADDR_BANK_SEL					0x6D															//---
	#define MPU6050_REG_ADDR_MEM_START_ADDR				0x6E
	#define MPU6050_REG_ADDR_MEM_R_W					0x6F
	#define MPU6050_REG_ADDR_DMP_CFG_1					0x70
	#define MPU6050_REG_ADDR_DMP_CFG_2					0x71
	#define MPU6050_REG_ADDR_FIFO_COUNTH				0x72															//---FIFO计数寄存器
	#define MPU6050_REG_ADDR_FIFO_COUNTL				0x73
	#define MPU6050_REG_ADDR_FIFO_R_W					0x74															//---FIFO读写
	#define MPU6050_REG_ADDR_WHO_AM_I					0x75															//---ID信息，默认值是0x68

	//===采样频率分频器
	#define MPU6050_SMPRT_DIV_1							0	
	#define MPU6050_SMPRT_DIV_2							1	
	#define MPU6050_SMPRT_DIV_3							2	
	#define MPU6050_SMPRT_DIV_4							3	
	#define MPU6050_SMPRT_DIV_5							4	
	#define MPU6050_SMPRT_DIV_6							5	
	#define MPU6050_SMPRT_DIV_7							6	
	#define MPU6050_SMPRT_DIV_8							7	
	#define MPU6050_SMPRT_DIV_9							8	
	#define MPU6050_SMPRT_DIV_10						9	
	#define MPU6050_SMPRT_DIV_11						10	
	#define MPU6050_SMPRT_DIV_12						11	
	#define MPU6050_SMPRT_DIV_13						12		
	#define MPU6050_SMPRT_DIV_14						13		
	#define MPU6050_SMPRT_DIV_15						14		
	#define MPU6050_SMPRT_DIV_16						15		
	#define MPU6050_SMPRT_DIV_17						16		
	#define MPU6050_SMPRT_DIV_18						17		
	#define MPU6050_SMPRT_DIV_19						18		
	#define MPU6050_SMPRT_DIV_20						19		
	#define MPU6050_SMPRT_DIV_21						20			
	#define MPU6050_SMPRT_DIV_22						21		
	#define MPU6050_SMPRT_DIV_23						22		
	#define MPU6050_SMPRT_DIV_24						23		
	#define MPU6050_SMPRT_DIV_25						24		
	#define MPU6050_SMPRT_DIV_26						25		
	#define MPU6050_SMPRT_DIV_27						26		
	#define MPU6050_SMPRT_DIV_28						27		
	#define MPU6050_SMPRT_DIV_29						28		
	#define MPU6050_SMPRT_DIV_30						29		
	#define MPU6050_SMPRT_DIV_31						30			
	#define MPU6050_SMPRT_DIV_32						31		
	#define MPU6050_SMPRT_DIV_33						32		
	#define MPU6050_SMPRT_DIV_34						33		
	#define MPU6050_SMPRT_DIV_35						34		
	#define MPU6050_SMPRT_DIV_36						35		
	#define MPU6050_SMPRT_DIV_37						36		
	#define MPU6050_SMPRT_DIV_38						37		
	#define MPU6050_SMPRT_DIV_39						38		
	#define MPU6050_SMPRT_DIV_40						39		
	#define MPU6050_SMPRT_DIV_41						40			
	#define MPU6050_SMPRT_DIV_42						41		
	#define MPU6050_SMPRT_DIV_43						42		
	#define MPU6050_SMPRT_DIV_44						43		
	#define MPU6050_SMPRT_DIV_45						44		
	#define MPU6050_SMPRT_DIV_46						45		
	#define MPU6050_SMPRT_DIV_47						46		
	#define MPU6050_SMPRT_DIV_48						47		
	#define MPU6050_SMPRT_DIV_49						48		
	#define MPU6050_SMPRT_DIV_50						49		
	#define MPU6050_SMPRT_DIV_51						50			
	#define MPU6050_SMPRT_DIV_52						51		
	#define MPU6050_SMPRT_DIV_53						52		
	#define MPU6050_SMPRT_DIV_54						53		
	#define MPU6050_SMPRT_DIV_55						54		
	#define MPU6050_SMPRT_DIV_56						55		
	#define MPU6050_SMPRT_DIV_57						56		
	#define MPU6050_SMPRT_DIV_58						57		
	#define MPU6050_SMPRT_DIV_59						58		
	#define MPU6050_SMPRT_DIV_60						59		
	#define MPU6050_SMPRT_DIV_61						60			
	#define MPU6050_SMPRT_DIV_62						61		
	#define MPU6050_SMPRT_DIV_63						62		
	#define MPU6050_SMPRT_DIV_64						63		
	#define MPU6050_SMPRT_DIV_65						64		
	#define MPU6050_SMPRT_DIV_66						65		
	#define MPU6050_SMPRT_DIV_67						66		
	#define MPU6050_SMPRT_DIV_68						67		
	#define MPU6050_SMPRT_DIV_69						68		
	#define MPU6050_SMPRT_DIV_70						69		
	#define MPU6050_SMPRT_DIV_71						70			
	#define MPU6050_SMPRT_DIV_72						71		
	#define MPU6050_SMPRT_DIV_73						72		
	#define MPU6050_SMPRT_DIV_74						73		
	#define MPU6050_SMPRT_DIV_75						74		
	#define MPU6050_SMPRT_DIV_76						75		
	#define MPU6050_SMPRT_DIV_77						76		
	#define MPU6050_SMPRT_DIV_78						77		
	#define MPU6050_SMPRT_DIV_79						78		
	#define MPU6050_SMPRT_DIV_80						79		
	#define MPU6050_SMPRT_DIV_81						80			
	#define MPU6050_SMPRT_DIV_82						81		
	#define MPU6050_SMPRT_DIV_83						82		
	#define MPU6050_SMPRT_DIV_84						83		
	#define MPU6050_SMPRT_DIV_85						84		
	#define MPU6050_SMPRT_DIV_86						85		
	#define MPU6050_SMPRT_DIV_87						86		
	#define MPU6050_SMPRT_DIV_88						87		
	#define MPU6050_SMPRT_DIV_89						88		
	#define MPU6050_SMPRT_DIV_90						89		
	#define MPU6050_SMPRT_DIV_91						90			
	#define MPU6050_SMPRT_DIV_92						91		
	#define MPU6050_SMPRT_DIV_93						92		
	#define MPU6050_SMPRT_DIV_94						93		
	#define MPU6050_SMPRT_DIV_95						94		
	#define MPU6050_SMPRT_DIV_96						95		
	#define MPU6050_SMPRT_DIV_97						96		
	#define MPU6050_SMPRT_DIV_98						97		
	#define MPU6050_SMPRT_DIV_99						98		
	#define MPU6050_SMPRT_DIV_100						99		
	#define MPU6050_SMPRT_DIV_101						100			
	#define MPU6050_SMPRT_DIV_102						101		
	#define MPU6050_SMPRT_DIV_103						102		
	#define MPU6050_SMPRT_DIV_104						103		
	#define MPU6050_SMPRT_DIV_105						104		
	#define MPU6050_SMPRT_DIV_106						105		
	#define MPU6050_SMPRT_DIV_107						106		
	#define MPU6050_SMPRT_DIV_108						107		
	#define MPU6050_SMPRT_DIV_109						108		
	#define MPU6050_SMPRT_DIV_110						109		
	#define MPU6050_SMPRT_DIV_111						110			
	#define MPU6050_SMPRT_DIV_112						111		
	#define MPU6050_SMPRT_DIV_113						112		
	#define MPU6050_SMPRT_DIV_114						113		
	#define MPU6050_SMPRT_DIV_115						114		
	#define MPU6050_SMPRT_DIV_116						115		
	#define MPU6050_SMPRT_DIV_117						116		
	#define MPU6050_SMPRT_DIV_118						117		
	#define MPU6050_SMPRT_DIV_119						118		
	#define MPU6050_SMPRT_DIV_120						119		
	#define MPU6050_SMPRT_DIV_121						120			
	#define MPU6050_SMPRT_DIV_122						121		
	#define MPU6050_SMPRT_DIV_123						122		
	#define MPU6050_SMPRT_DIV_124						123		
	#define MPU6050_SMPRT_DIV_125						124		
	#define MPU6050_SMPRT_DIV_126						125		
	#define MPU6050_SMPRT_DIV_127						126		
	#define MPU6050_SMPRT_DIV_128						127		
	#define MPU6050_SMPRT_DIV_129						128		
	#define MPU6050_SMPRT_DIV_130						129		
	#define MPU6050_SMPRT_DIV_131						130			
	#define MPU6050_SMPRT_DIV_132						131		
	#define MPU6050_SMPRT_DIV_133						132		
	#define MPU6050_SMPRT_DIV_134						133		
	#define MPU6050_SMPRT_DIV_135						134		
	#define MPU6050_SMPRT_DIV_136						135		
	#define MPU6050_SMPRT_DIV_137						136		
	#define MPU6050_SMPRT_DIV_138						137		
	#define MPU6050_SMPRT_DIV_139						138		
	#define MPU6050_SMPRT_DIV_140						139		
	#define MPU6050_SMPRT_DIV_141						140			
	#define MPU6050_SMPRT_DIV_142						141		
	#define MPU6050_SMPRT_DIV_143						142		
	#define MPU6050_SMPRT_DIV_144						143		
	#define MPU6050_SMPRT_DIV_145						144		
	#define MPU6050_SMPRT_DIV_146						145		
	#define MPU6050_SMPRT_DIV_147						146		
	#define MPU6050_SMPRT_DIV_148						147		
	#define MPU6050_SMPRT_DIV_149						148		
	#define MPU6050_SMPRT_DIV_150						149		
	#define MPU6050_SMPRT_DIV_151						150			
	#define MPU6050_SMPRT_DIV_152						151		
	#define MPU6050_SMPRT_DIV_153						152		
	#define MPU6050_SMPRT_DIV_154						153		
	#define MPU6050_SMPRT_DIV_155						154		
	#define MPU6050_SMPRT_DIV_156						155		
	#define MPU6050_SMPRT_DIV_157						156		
	#define MPU6050_SMPRT_DIV_158						157		
	#define MPU6050_SMPRT_DIV_159						158		
	#define MPU6050_SMPRT_DIV_160						159		
	#define MPU6050_SMPRT_DIV_161						160			
	#define MPU6050_SMPRT_DIV_162						161		
	#define MPU6050_SMPRT_DIV_163						162		
	#define MPU6050_SMPRT_DIV_164						163		
	#define MPU6050_SMPRT_DIV_165						164		
	#define MPU6050_SMPRT_DIV_166						165		
	#define MPU6050_SMPRT_DIV_167						166		
	#define MPU6050_SMPRT_DIV_168						167		
	#define MPU6050_SMPRT_DIV_169						168		
	#define MPU6050_SMPRT_DIV_170						169		
	#define MPU6050_SMPRT_DIV_171						170			
	#define MPU6050_SMPRT_DIV_172						171		
	#define MPU6050_SMPRT_DIV_173						172		
	#define MPU6050_SMPRT_DIV_174						173		
	#define MPU6050_SMPRT_DIV_175						174		
	#define MPU6050_SMPRT_DIV_176						175		
	#define MPU6050_SMPRT_DIV_177						176		
	#define MPU6050_SMPRT_DIV_178						177		
	#define MPU6050_SMPRT_DIV_179						178		
	#define MPU6050_SMPRT_DIV_180						179		
	#define MPU6050_SMPRT_DIV_181						180			
	#define MPU6050_SMPRT_DIV_182						181		
	#define MPU6050_SMPRT_DIV_183						182		
	#define MPU6050_SMPRT_DIV_184						183		
	#define MPU6050_SMPRT_DIV_185						184		
	#define MPU6050_SMPRT_DIV_186						185		
	#define MPU6050_SMPRT_DIV_187						186		
	#define MPU6050_SMPRT_DIV_188						187		
	#define MPU6050_SMPRT_DIV_189						188		
	#define MPU6050_SMPRT_DIV_190						189		
	#define MPU6050_SMPRT_DIV_191						190			
	#define MPU6050_SMPRT_DIV_192						191		
	#define MPU6050_SMPRT_DIV_193						192		
	#define MPU6050_SMPRT_DIV_194						193		
	#define MPU6050_SMPRT_DIV_195						194		
	#define MPU6050_SMPRT_DIV_196						195		
	#define MPU6050_SMPRT_DIV_197						196		
	#define MPU6050_SMPRT_DIV_198						197		
	#define MPU6050_SMPRT_DIV_199						198		
	#define MPU6050_SMPRT_DIV_200						199		
	#define MPU6050_SMPRT_DIV_201						200			
	#define MPU6050_SMPRT_DIV_202						201		
	#define MPU6050_SMPRT_DIV_203						202		
	#define MPU6050_SMPRT_DIV_204						203		
	#define MPU6050_SMPRT_DIV_205						204		
	#define MPU6050_SMPRT_DIV_206						205		
	#define MPU6050_SMPRT_DIV_207						206		
	#define MPU6050_SMPRT_DIV_208						207		
	#define MPU6050_SMPRT_DIV_209						208		
	#define MPU6050_SMPRT_DIV_210						209		
	#define MPU6050_SMPRT_DIV_211						210			
	#define MPU6050_SMPRT_DIV_212						211		
	#define MPU6050_SMPRT_DIV_213						212		
	#define MPU6050_SMPRT_DIV_214						213		
	#define MPU6050_SMPRT_DIV_215						214		
	#define MPU6050_SMPRT_DIV_216						215		
	#define MPU6050_SMPRT_DIV_217						216		
	#define MPU6050_SMPRT_DIV_218						217		
	#define MPU6050_SMPRT_DIV_219						218		
	#define MPU6050_SMPRT_DIV_220						219		
	#define MPU6050_SMPRT_DIV_221						220			
	#define MPU6050_SMPRT_DIV_222						221		
	#define MPU6050_SMPRT_DIV_223						222		
	#define MPU6050_SMPRT_DIV_224						223		
	#define MPU6050_SMPRT_DIV_225						224		
	#define MPU6050_SMPRT_DIV_226						225		
	#define MPU6050_SMPRT_DIV_227						226		
	#define MPU6050_SMPRT_DIV_228						227		
	#define MPU6050_SMPRT_DIV_229						228		
	#define MPU6050_SMPRT_DIV_230						229		
	#define MPU6050_SMPRT_DIV_231						230			
	#define MPU6050_SMPRT_DIV_232						231		
	#define MPU6050_SMPRT_DIV_233						232		
	#define MPU6050_SMPRT_DIV_234						233		
	#define MPU6050_SMPRT_DIV_235						234		
	#define MPU6050_SMPRT_DIV_236						235		
	#define MPU6050_SMPRT_DIV_237						236		
	#define MPU6050_SMPRT_DIV_238						237		
	#define MPU6050_SMPRT_DIV_239						238		
	#define MPU6050_SMPRT_DIV_240						239		
	#define MPU6050_SMPRT_DIV_241						240			
	#define MPU6050_SMPRT_DIV_242						241		
	#define MPU6050_SMPRT_DIV_243						242		
	#define MPU6050_SMPRT_DIV_244						243		
	#define MPU6050_SMPRT_DIV_245						244		
	#define MPU6050_SMPRT_DIV_246						245		
	#define MPU6050_SMPRT_DIV_247						246		
	#define MPU6050_SMPRT_DIV_248						247		
	#define MPU6050_SMPRT_DIV_249						248		
	#define MPU6050_SMPRT_DIV_250						249		
	#define MPU6050_SMPRT_DIV_251						250			
	#define MPU6050_SMPRT_DIV_252						251		
	#define MPU6050_SMPRT_DIV_253						252		
	#define MPU6050_SMPRT_DIV_254						253		
	#define MPU6050_SMPRT_DIV_255						254		
	#define MPU6050_SMPRT_DIV_256						255		

	#define MPU6050_TC_PWR_MODE_BIT						7
	#define MPU6050_TC_OFFSET_BIT						6
	#define MPU6050_TC_OFFSET_LENGTH					6
	#define MPU6050_TC_OTP_BNK_VLD_BIT					0
	
	#define MPU6050_VDDIO_LEVEL_VLOGIC					0
	#define MPU6050_VDDIO_LEVEL_VDD						1
	
	#define MPU6050_CFG_EXT_SYNC_SET_BIT				5
	#define MPU6050_CFG_EXT_SYNC_SET_LENGTH				3
	#define MPU6050_CFG_DLPF_CFG_BIT					2
	#define MPU6050_CFG_DLPF_CFG_LENGTH					3
	
	#define MPU6050_EXT_SYNC_DISABLED					0x0
	#define MPU6050_EXT_SYNC_TEMP_OUT_L					0x1
	#define MPU6050_EXT_SYNC_GYRO_XOUT_L				0x2
	#define MPU6050_EXT_SYNC_GYRO_YOUT_L				0x3
	#define MPU6050_EXT_SYNC_GYRO_ZOUT_L				0x4
	#define MPU6050_EXT_SYNC_ACCEL_XOUT_L				0x5
	#define MPU6050_EXT_SYNC_ACCEL_YOUT_L				0x6
	#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L				0x7
	
	//===数字低通滤波器配置，带宽
	#define MPU6050_DLPF_BW_256							0x00
	#define MPU6050_DLPF_BW_188							0x01
	#define MPU6050_DLPF_BW_98							0x02
	#define MPU6050_DLPF_BW_42							0x03
	#define MPU6050_DLPF_BW_20							0x04
	#define MPU6050_DLPF_BW_10							0x05
	#define MPU6050_DLPF_BW_5							0x06
	
	#define MPU6050_GYRO_XG_ST_ENABLE					(1<<7)		//---使能陀螺仪X轴自检
	#define MPU6050_GYRO_XG_ST_DISABLE					~(1<<7)		//---不使能陀螺仪X轴自检
	#define MPU6050_GYRO_YG_ST_ENABLE					(1<<6)		//---使能陀螺仪Y轴自检
	#define MPU6050_GYRO_YG_ST_DISABLE					~(1<<6)		//---不使能陀螺仪Y轴自检
	#define MPU6050_GYRO_ZG_ST_ENABLE					(1<<5)		//---使能陀螺仪Z轴自检
	#define MPU6050_GYRO_ZG_ST_DISABLE					~(1<<5)		//---不使能陀螺仪Z轴自检

	#define MPU6050_GYRO_FS_250							(0<<3)		//---陀螺仪量程+/-250
	#define MPU6050_GYRO_FS_500							(1<<3)		//---陀螺仪量程+/-500
	#define MPU6050_GYRO_FS_1000						(2<<3)		//---陀螺仪量程+/-1000
	#define MPU6050_GYRO_FS_2000						(3<<3)		//---陀螺仪量程+/-2000
	#define MPU6050_GYRO_FS_MASK						(3<<3)		//---陀螺仪量程+/-2000
	
	#define MPU6050_ACCEL_XA_ST_ENABLE					(1<<7)		//---使能加速度X轴自检
	#define MPU6050_ACCEL_XA_ST_DISABLE					~(1<<7)		//---不使能加速度X轴自检
	#define MPU6050_ACCEL_YA_ST_ENABLE					(1<<6)		//---使能加速度Y轴自检
	#define MPU6050_ACCEL_YA_ST_DISABLE					~(1<<6)		//---不使能加速度Y轴自检
	#define MPU6050_ACCEL_ZA_ST_ENABLE					(1<<5)		//---使能加速度Z轴自检
	#define MPU6050_ACCEL_ZA_ST_DISABLE					~(1<<5)		//---不使能加速度Z轴自检
	
	#define MPU6050_ACCEL_FS_2							(0<<3)		//---加速度量程+/-2G
	#define MPU6050_ACCEL_FS_4							(1<<3)		//---加速度量程+/-4G
	#define MPU6050_ACCEL_FS_8							(2<<3)		//---加速度量程+/-8G
	#define MPU6050_ACCEL_FS_16							(3<<3)		//---加速度量程+/-16G
	#define MPU6050_ACCEL_FS_MASK						(3<<3)		//---加速度量程+/-16G
	
	#define MPU6050_DHPF_RESET							0x00
	#define MPU6050_DHPF_5								0x01
	#define MPU6050_DHPF_2P5							0x02
	#define MPU6050_DHPF_1P25							0x03
	#define MPU6050_DHPF_0P63							0x04
	#define MPU6050_DHPF_HOLD							0x07
	
	//===FIFO使能配置
	#define MPU6050_TEMP_FIFO_ENABLE					(1<<7)		//---使能温度FIFO功能
	#define MPU6050_TEMP_FIFO_DISABLE					~(1<<7)		//---不使能温度的FIFO功能
	#define MPU6050_XG_FIFO_ENABLE						(1<<6)		//---使能X轴陀螺仪的FIFO功能
	#define MPU6050_XG_FIFO_DISABLE						~(1<<6)		//---不使能X轴陀螺仪的FIFO功能
	#define MPU6050_YG_FIFO_ENABLE						(1<<5)		//---使能Y轴陀螺仪的FIFO功能
	#define MPU6050_YG_FIFO_DISABLE						~(1<<5)		//---不使能Y轴陀螺仪的FIFO功能5
	#define MPU6050_ZG_FIFO_ENABLE						(1<<4)		//---使能Z轴陀螺仪的FIFO功能
	#define MPU6050_ZG_FIFO_DISABLE						~(1<<4)		//---不使能Z轴陀螺仪的FIFO功能
	#define MPU6050_ACCEL_FIFO_ENABLE					(1<<3)		//---使能加速度的FIFO功能
	#define MPU6050_ACCEL_FIFO_DISABLE					~(1<<3)		//---不使能加速度的FIFO功能
	#define MPU6050_SLV2_FIFO_ENABLE					(1<<2)		//---使能从机2的FIFO功能
	#define MPU6050_SLV2_FIFO_DISABLE					~(1<<2)		//---不使能从机2的FIFO功能
	#define MPU6050_SLV1_FIFO_ENABLE					(1<<1)		//---使能从机1的FIFO功能
	#define MPU6050_SLV1_FIFO_DISABLE					~(1<<1)		//---不使能从机1的FIFO功能
	#define MPU6050_SLV0_FIFO_ENABLE					(1<<0)		//---使能从机0的FIFO功能	
	#define MPU6050_SLV0_FIFO_DISABLE					~(1<<0)		//---不使能从机0的FIFO功能

	//===配置I2C主机时钟频率
	#define MPU6050_MST_CLK_DIV_348KHZ					0x0
	#define MPU6050_MST_CLK_DIV_333KHZ					0x1
	#define MPU6050_MST_CLK_DIV_320KHZ					0x2
	#define MPU6050_MST_CLK_DIV_308KHZ					0x3
	#define MPU6050_MST_CLK_DIV_296KHZ					0x4
	#define MPU6050_MST_CLK_DIV_286KHZ					0x5
	#define MPU6050_MST_CLK_DIV_276KHZ					0x6
	#define MPU6050_MST_CLK_DIV_267KHZ					0x7
	#define MPU6050_MST_CLK_DIV_258KHZ					0x8
	#define MPU6050_MST_CLK_DIV_500KHZ					0x9
	#define MPU6050_MST_CLK_DIV_471KHZ					0xA
	#define MPU6050_MST_CLK_DIV_444KHZ					0xB
	#define MPU6050_MST_CLK_DIV_421KHZ					0xC
	#define MPU6050_MST_CLK_DIV_400KHZ					0xD
	#define MPU6050_MST_CLK_DIV_381KHZ					0xE
	#define MPU6050_MST_CLK_DIV_364KHZ					0xF
	
	#define MPU6050_MULT_MST_EN_BIT						7
	#define MPU6050_WAIT_FOR_ES_BIT						6
	#define MPU6050_SLV_3_FIFO_EN_BIT					5
	#define MPU6050_I2C_MST_P_NSR_BIT					4
	#define MPU6050_I2C_MST_CLK_BIT						3
	#define MPU6050_I2C_MST_CLK_LENGTH					4
	
	#define MPU6050_I2C_SLV_RW_BIT						7
	#define MPU6050_I2C_SLV_ADDR_BIT					6
	#define MPU6050_I2C_SLV_ADDR_LENGTH					7
	#define MPU6050_I2C_SLV_EN_BIT						7
	#define MPU6050_I2C_SLV_BYTE_SW_BIT					6
	#define MPU6050_I2C_SLV_REG_DIS_BIT					5
	#define MPU6050_I2C_SLV_GRP_BIT						4
	#define MPU6050_I2C_SLV_LEN_BIT						3
	#define MPU6050_I2C_SLV_LEN_LENGTH					4
	
	#define MPU6050_I2C_SLV4_RW_BIT						7
	#define MPU6050_I2C_SLV4_ADDR_BIT					6
	#define MPU6050_I2C_SLV4_ADDR_LENGTH				7
	#define MPU6050_I2C_SLV4_EN_BIT						7
	#define MPU6050_I2C_SLV4_INT_EN_BIT					6
	#define MPU6050_I2C_SLV4_REG_DIS_BIT				5
	#define MPU6050_I2C_SLV4_MST_DLY_BIT				4
	#define MPU6050_I2C_SLV4_MST_DLY_LENGTH				5
														
	#define MPU6050_MST_PASS_THROUGH_BIT				7
	#define MPU6050_MST_I2C_SLV4_DONE_BIT				6
	#define MPU6050_MST_I2C_LOST_ARB_BIT				5
	#define MPU6050_MST_I2C_SLV4_NACK_BIT				4
	#define MPU6050_MST_I2C_SLV3_NACK_BIT				3
	#define MPU6050_MST_I2C_SLV2_NACK_BIT				2
	#define MPU6050_MST_I2C_SLV1_NACK_BIT				1
	#define MPU6050_MST_I2C_SLV0_NACK_BIT				0
	
	#define MPU6050_INTCFG_INT_LEVEL_BIT				7
	#define MPU6050_INTCFG_INT_OPEN_BIT					6
	#define MPU6050_INTCFG_LATCH_INT_EN_BIT				5
	#define MPU6050_INTCFG_INT_RD_CLEAR_BIT				4
	#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT			3
	#define MPU6050_INTCFG_FSYNC_INT_EN_BIT				2
	#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT			1
	#define MPU6050_INTCFG_CLKOUT_EN_BIT				0
	
	#define MPU6050_INT_LEVEL_HIGH						~(1<<7)			//---INT引脚的逻辑电平是高电平
	#define MPU6050_INT_LEVEL_LOW						(1<<7)			//---INT引脚的逻辑电平是低电平
	
	#define MPU6050_INTDRV_PUSHPULL						~(1<<6)			//---INT引脚推挽输出
	#define MPU6050_INTDRV_OPENDRAIN					(1<<6)			//---INT引脚开漏模式
	
	#define MPU6050_INT_LATCH_50USPULSE					~(1<<5)			//---INT引脚产生50us脉冲
	#define MPU6050_INT_LATCH_WAITCLEAR					(1<<5)			//---INT引脚保持高电平知道中断被清楚
	
	#define MPU6050_INT_CLEAR_STATUSREAD				~(1<<4)			//---读取中断状态寄存器，清除中断状态位
	#define MPU6050_INT_CLEAR_ANYREAD					(1<<4)			//---任何读取中断状态位清除
	
	#define MPU6050_INTERRUPT_FF_BIT					7
	#define MPU6050_MOT_INT_ENABLE						(1<<6)			//---运动检测中断使能
	#define MPU6050_MOT_INT_DISABLE						~(1<<6)			//---运动检测中断不使能
	#define MPU6050_INTERRUPT_ZMOT_BIT					5
	#define MPU6050_FIFO_OFLOW_INT_ENABLE				(1<<4)			//---使能FIFO缓冲区溢出产生中断
	#define	MPU6050_FIFO_OFLOW_INT_DISABLE				~(1<<4)			//---不使能FIFO缓冲区溢出产生中断
	#define MPU6050_I2C_MST_INT_ENABLE					(1<<3)			//---使能I2C主机所有中断源产生中断
	#define MPU6050_I2C_MST_INT_DISABLE					~(1<<3)			//---不使能I2C主机所有中断源产生中断
	#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT			2
	#define MPU6050_INTERRUPT_DMP_INT_BIT				1				//---DMP中断中断位
	#define MPU6050_DATA_RDY_INT_ENABLE					(1<<0)			//---使能数据就绪中
	#define MPU6050_DATA_RDY_INT_DISABLE				~(1<<0)			//---不使能数据就绪中

	#define MPU6050_MOT_MASK							(1<<6)			//---运动检测中断使能
	#define MPU6050_ZMOT_MASK							(1<<5)
	#define MPU6050_FIFO_OFLOW_MASK						(1<<4)			//---使能FIFO缓冲区溢出产生中断
	#define MPU6050_I2C_MST_MASK						(1<<3)			//---使能I2C主机所有中断源产生中断
	#define MPU6050_DATA_RDY_MASK						(1<<0)			//---使能数据就绪中
	
	// TODO: figure out what these actually do
	// UMPL source code is not very obivous
	#define MPU6050_DMPINT_5_BIT						5
	#define MPU6050_DMPINT_4_BIT						4
	#define MPU6050_DMPINT_3_BIT						3
	#define MPU6050_DMPINT_2_BIT						2
	#define MPU6050_DMPINT_1_BIT						1
	#define MPU6050_DMPINT_0_BIT						0
														
	#define MPU6050_MOTION_MOT_XNEG_BIT					7
	#define MPU6050_MOTION_MOT_XPOS_BIT					6
	#define MPU6050_MOTION_MOT_YNEG_BIT					5
	#define MPU6050_MOTION_MOT_YPOS_BIT					4
	#define MPU6050_MOTION_MOT_ZNEG_BIT					3
	#define MPU6050_MOTION_MOT_ZPOS_BIT					2
	#define MPU6050_MOTION_MOT_ZRMOT_BIT				0
	
	#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT		7
	#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT		4
	#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT		3
	#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT		2
	#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT		1
	#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT		0
	
	#define MPU6050_PATHRESET_GYRO_RESET_BIT			2
	#define MPU6050_PATHRESET_ACCEL_RESET_BIT			1
	#define MPU6050_PATHRESET_TEMP_RESET_BIT			0
	
	#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT			5
	#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH		2
	#define MPU6050_DETECT_FF_COUNT_BIT					3
	#define MPU6050_DETECT_FF_COUNT_LENGTH				2
	#define MPU6050_DETECT_MOT_COUNT_BIT				1
	#define MPU6050_DETECT_MOT_COUNT_LENGTH				2
	
	#define MPU6050_DETECT_DECREMENT_RESET				0x0
	#define MPU6050_DETECT_DECREMENT_1					0x1
	#define MPU6050_DETECT_DECREMENT_2					0x2
	#define MPU6050_DETECT_DECREMENT_4					0x3
	
	#define MPU6050_USERCTRL_DMP_EN_BIT					7
	#define MPU6050_USERCTRL_FIFO_EN_BIT				6
	#define MPU6050_USERCTRL_I2C_MST_EN_BIT				5
	#define MPU6050_USERCTRL_I2C_IF_DIS_BIT				4
	#define MPU6050_USERCTRL_DMP_RESET_BIT				3
	#define MPU6050_USERCTRL_FIFO_RESET_BIT				2
	#define MPU6050_USERCTRL_I2C_MST_RESET_BIT			1
	#define MPU6050_USERCTRL_SIG_COND_RESET_BIT			0
	
	#define MPU6050_PWR1_DEVICE_RESET_BIT				7
	#define MPU6050_PWR1_SLEEP_BIT						6
	#define MPU6050_PWR1_CYCLE_BIT						5
	#define MPU6050_PWR1_TEMP_DIS_BIT					3
	#define MPU6050_PWR1_CLKSEL_BIT						2
	#define MPU6050_PWR1_CLKSEL_LENGTH					3
	
	#define MPU6050_CLOCK_INTERNAL						0x00
	#define MPU6050_CLOCK_PLL_XGYRO						0x01
	#define MPU6050_CLOCK_PLL_YGYRO						0x02
	#define MPU6050_CLOCK_PLL_ZGYRO						0x03
	#define MPU6050_CLOCK_PLL_EXT32K					0x04
	#define MPU6050_CLOCK_PLL_EXT19M					0x05
	#define MPU6050_CLOCK_KEEP_RESET					0x07
	
	#define MPU6050_PWR2_LP_WAKE_CTRL_BIT				7
	#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH			2
	#define MPU6050_PWR2_STBY_XA_BIT					5
	#define MPU6050_PWR2_STBY_YA_BIT					4
	#define MPU6050_PWR2_STBY_ZA_BIT					3
	#define MPU6050_PWR2_STBY_XG_BIT					2
	#define MPU6050_PWR2_STBY_YG_BIT					1
	#define MPU6050_PWR2_STBY_ZG_BIT					0
	
	#define MPU6050_WAKE_FREQ_1P25						0x0
	#define MPU6050_WAKE_FREQ_2P5						0x1
	#define MPU6050_WAKE_FREQ_5							0x2
	#define MPU6050_WAKE_FREQ_10						0x3
	
	#define MPU6050_BANKSEL_PRFTCH_EN_BIT				6
	#define MPU6050_BANKSEL_CFG_USER_BANK_BIT			5
	#define MPU6050_BANKSEL_MEM_SEL_BIT					4
	#define MPU6050_BANKSEL_MEM_SEL_LENGTH				5
	#define MPU6050_WHO_AM_I_BIT						6
	#define MPU6050_WHO_AM_I_LENGTH						6
	
	//===设备通讯地址
	#define MPU6050_WADDR								(MPU6050_DEFAULT_ADDRESS<<1)									//---设备的写地址
	#define MPU6050_RADDR								MPU6050_WADDR+1													//---设备的读地址
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===加速度
	typedef struct Accel_HandleType
	{
		INT16_T xAccel;																									//---X轴加速度
		INT16_T yAccel;																									//---Y轴加速度
		INT16_T zAccel;																									//---Z轴加速度
	}Accel_HandleType;	
	
	//===陀螺仪
	typedef struct Gyro_HandleType
	{
	    INT16_T xGyro;																									//---X轴陀螺仪					
		INT16_T yGyro;																									//---Y轴陀螺仪
		INT16_T zGyro;																									//---Z轴陀螺仪
	}Gyro_HandleType;	
	//===结构体定义
	typedef struct _MPU6050_HandleType					MPU6050_HandleType;
	//===指针结构体定义
	typedef struct _MPU6050_HandleType					*pMPU6050_HandleType;
	//===HMC5883的数据结构体
	struct _MPU6050_HandleType
	{
		Accel_HandleType	msgAccel;																					//---加速度
		INT32_T				msgTemp;																					//---放大100倍的温度值
		Gyro_HandleType		msgGyro;																					//---陀螺仪
		GPIO_HandleType		msgINT;																						//---中断引脚
		I2C_HandleType		msgI2C;																						//---使用的I2C
		void(*pMsgDelayms)(UINT32_T delay);																				//---延时参数
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===定义的任务函数
	#define MPU6050_TASK_ONE							pMpu6050Device0													//---任务1
	#define MPU6050_TASK_TWO							0																//---任务2
	#define MPU6050_TASK_THREE							0																//---任务3
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用
	extern MPU6050_HandleType							g_Mpu6050Device0;
	extern pMPU6050_HandleType							pMpu6050Device0;

	//===函数定义
	UINT8_T MPU6050_I2C_Device0_Init(MPU6050_HandleType* MPU6050x);
	UINT8_T MPU6050_I2C_Device1_Init(MPU6050_HandleType* MPU6050x);
	UINT8_T MPU6050_I2C_Device2_Init(MPU6050_HandleType* MPU6050x);
	UINT8_T MPU6050_I2C_Init(MPU6050_HandleType* MPU6050x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T MPU6050_I2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val);
	UINT8_T MPU6050_I2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T MPU6050_I2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T MPU6050_I2C_ReadBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T MPU6050_I2C_ReadChipID(MPU6050_HandleType* MPU6050x, UINT8_T* pChipID);
	UINT8_T MPU6050_I2C_ConfigInit(MPU6050_HandleType* MPU6050x);
	UINT8_T MPU6050_I2C_ReadAccelTempGyro(MPU6050_HandleType* MPU6050x);

//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MPU6050_CFG_H_ */