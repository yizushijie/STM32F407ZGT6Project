#ifndef WWDG_TASK_H_
#define WWDG_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"wwdg_lib.h"
	/////////////////////////////////////////////////////////////////////////////////////

	//===��������
	UINT8_T WWDGTask_Init(UINT8_T wr, UINT32_T prv);
	UINT8_T WWDGTask_DeInit(void);
	UINT8_T WWDGTask_Reset(void);
	/////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*WWDG_TASK_H_ */