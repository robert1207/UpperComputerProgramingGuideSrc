#ifndef APP_PROGRAM_H_
#define APP_PROGRAM_H_

#include "includes.h"




extern void APP_RunApp(void);

extern void APP_SetAppFlag();
extern bool APP_IsHadAppFlag(void);
extern void APP_ClearAppFlag();

extern void APP_ProgramOnePageIntoFlash(uint8_t* pageBuf, uint16_t pageLen);
extern void APP_EraseAppUsingPages();
extern uint32_t APP_CheckAppSum(uint16_t page_count);

#endif //APP_PROGRAM_H_
