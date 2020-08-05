#ifndef BSP_FLASH_H_
#define BSP_FLASH_H_

#include <includes.h>

//这些调试打印函数暂时不删除，用于以后移植到其他芯片，方便调试
//extern uint32_t flash_checksum;

#define STM32_FLASH_ONE_PAGE_BYTE		1024	//页大小
#define STM32_FLASH_PAGE_SIZE			FLASH_PAGE_SIZE	//页个数
#define STM32_FLASH_BASE				FLASH_BASE
#define STM32_FLASH_END					FLASH_END

//#define TEST

#ifdef TEST
extern void BSP_Flash_Check(uint8_t PageIndex);
#endif

extern void BSP_Flash_ClearFlashFlag();
extern void BSP_FLASH_ReadPage(uint8_t PageIndex, uint8_t *pBuff);
extern void BSP_FLASH_WritePage(uint8_t PageIndex, uint8_t *pBuff);
extern void BSP_Flash_ErasePage(uint8_t StartPageIndex, uint32_t PageCount);



#endif //BSP_FLASH_H_
