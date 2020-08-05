#include "program.h"

static uint16_t current_program_flash_page_index = 0;

uint32_t check_sum_write = 0;

//total flash size : 128k 128page
//boot_loader 		page index : 0 ~ 30		31k
//boot_loader_flag 	page index : 31			1k
//app 				page index : 32 ~ 127	96k
//uint32_t addr = STM32_FLASH_BASE + StartPageIndex * STM32_FLASH_ONE_PAGE_BYTE;
#define FLASH_USER_APP_FLAG_START_ADDR	(STM32_FLASH_BASE + STM32_FLASH_ONE_PAGE_BYTE * 31)
#define FLASH_USER_APP_START_ADDR		(STM32_FLASH_BASE + STM32_FLASH_ONE_PAGE_BYTE * 32) //= 32768 = 0x8000
//#define FLASH_USER_APP_END_ADDR			(STM32_FLASH_BASE + STM32_FLASH_ONE_PAGE_BYTE * 127)

//此芯片共128页 对应的序号范围是：0 - 127
//举例说明：当index序号为0的时候，实际使用的 是flash的第1页。
//因此下面的 序号31 指的的flash的 第 32 页。
//下面的 应用程序 序号 32 指的是flash的 第 33页, 最大到 128页
#define FLASH_FLAG_PAGE_START_INDEX 31
#define FLASH_APP_PAGE_START_INDEX 32
#define FLASH_APP_PAGE_END_INDEX 127


#define APPLICATION_ADDRESS        FLASH_USER_APP_START_ADDR //0x08008000

typedef  void (*pFunction)(void);
pFunction JumpToApplication;

uint8_t FlashOnePageCache[STM32_FLASH_ONE_PAGE_BYTE];

void APP_RunApp(void) {
	pFunction appEntry;
	uint32_t appStack;

	BSP_DisableIrq();

	/* Get the application stack pointer (First entry in the application vector table) */
	appStack = (uint32_t) *((__IO uint32_t*)APPLICATION_ADDRESS);

	/* Get the application entry point (Second entry in the application vector table) */
	appEntry = (pFunction) *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);

	/* Reconfigure vector table offset register to match the application location */
	SCB->VTOR = APPLICATION_ADDRESS; //跳转到 使用FreeRTOS的app，此行代码无效，需要在
	//App的主函数第一行加入，此行，以完成设置中断向量表

	/* Set the application stack pointer */
	__set_MSP(appStack);//设置新的栈的储存地址指针

	/* Start the application */
	appEntry();

}

void APP_ProgramOnePageIntoFlash(uint8_t* pageBuf, uint16_t pageLen) {
	if(pageLen != STM32_FLASH_ONE_PAGE_BYTE) return;
	BSP_DisableIrq();
	BSP_Flash_ClearFlashFlag();
	uint16_t page_index = FLASH_APP_PAGE_START_INDEX + current_program_flash_page_index;
	BSP_FLASH_WritePage(page_index, pageBuf);
	current_program_flash_page_index ++;
	BSP_EnableIrq();
}

void APP_EraseAppUsingPages() {
	BSP_DisableIrq();
	BSP_Flash_ClearFlashFlag();
	uint32_t erase_page_count = FLASH_APP_PAGE_END_INDEX - FLASH_APP_PAGE_START_INDEX + 1;
	BSP_Flash_ErasePage(FLASH_APP_PAGE_START_INDEX, erase_page_count);
	current_program_flash_page_index = 0;
	BSP_EnableIrq();
}

void APP_SetAppFlag() {
	memset(FlashOnePageCache, 0, STM32_FLASH_ONE_PAGE_BYTE);

	FlashOnePageCache[0] = 0xa0;
	FlashOnePageCache[1] = 0xa1;
	FlashOnePageCache[2] = 0xa2;
	FlashOnePageCache[3] = 0xa3;

	//ERASE
	BSP_DisableIrq();
	BSP_Flash_ClearFlashFlag();
	BSP_Flash_ErasePage(FLASH_FLAG_PAGE_START_INDEX, 1); //erase one page

	//WRITE FLAG
	BSP_Flash_ClearFlashFlag();
	BSP_FLASH_WritePage(FLASH_FLAG_PAGE_START_INDEX, FlashOnePageCache);

	BSP_EnableIrq();
}

bool APP_IsHadAppFlag(void) {
	bool retValue = false;

	BSP_DisableIrq();
	memset(FlashOnePageCache, 0, STM32_FLASH_ONE_PAGE_BYTE);

	//READ FALG
	BSP_FLASH_ReadPage(FLASH_FLAG_PAGE_START_INDEX, FlashOnePageCache);
	if( 	FlashOnePageCache[0] == 0xa0 &&
			FlashOnePageCache[1] == 0xa1 &&
			FlashOnePageCache[2] == 0xa2 &&
			FlashOnePageCache[3] == 0xa3) {
		retValue = true;
	}

	BSP_EnableIrq();
	return retValue;
}

void APP_ClearAppFlag() {
	memset(FlashOnePageCache, 0, STM32_FLASH_ONE_PAGE_BYTE);

	FlashOnePageCache[0] = 0x00;
	FlashOnePageCache[1] = 0x00;
	FlashOnePageCache[2] = 0x00;
	FlashOnePageCache[3] = 0x00;

	//ERASE
	BSP_DisableIrq();
	BSP_Flash_ClearFlashFlag();
	BSP_Flash_ErasePage(FLASH_FLAG_PAGE_START_INDEX, 1); //erase one page

	//WRITE FLAG
	//BSP_Flash_ClearFlashFlag();
	//BSP_FLASH_WritePage(FLASH_FLAG_PAGE_START_INDEX, FlashOnePageCache);

	BSP_EnableIrq();
}

/*
 * @brief 检查app是否被正确下载到flash
 */
uint32_t APP_CheckAppSum(uint16_t page_count) {

	uint32_t myCheckSum = 0;

	BSP_DisableIrq();

	uint16_t page_index = 0;

	//printf("page_count = %d\n", page_count);

	for (int i = 0; i < page_count; i ++) {
		memset(FlashOnePageCache, 0, STM32_FLASH_ONE_PAGE_BYTE);
		page_index = FLASH_APP_PAGE_START_INDEX + i;
		BSP_FLASH_ReadPage(page_index, FlashOnePageCache);

		for (int k = 0; k < STM32_FLASH_ONE_PAGE_BYTE; k ++) {
			myCheckSum += FlashOnePageCache[k];
		}
	}

	BSP_EnableIrq();
	return myCheckSum;
}





