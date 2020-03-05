#ifndef RFASK_LIB_H_
#define RFASK_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "rfask_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	void	 RFASKLib_Init(RFASK_HandleType *rfask);
	UINT32_T RFASKLib_CalcXTAL(RFASK_HandleType *rfask, UINT32_T rfX100MHz);
	UINT8_T  RFASKLib_SetDeviceType(RFASK_HandleType *rfask, UINT8_T deviceType);
	UINT32_T RFASKLib_GetDeviceType(RFASK_HandleType *rfask);
	UINT8_T  RFASKLib_ActivateSites(RFASK_HandleType *rfask, UINT8_T activateSites);
	UINT8_T  RFASKLib_SetFreqCurrentPointCmd(FREQ_CURRENT_HandleType *rfaskFreqCurrent, UINT8_T cmd);
	UINT8_T  RFASKLib_ScanYSEL(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASK_LIB_H_ */