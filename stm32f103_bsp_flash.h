#ifndef __STM32F103_BSP_FLASH_H
#define __STM32F103_BSP_FLASH_H

#include "stm32f1xx_hal.h"

#define FLASH_SECTOR_BASE_ADDRESS 0x08000000
// #define FLASH_PAGE_SIZE 0x400

HAL_StatusTypeDef OverWriteFlashU32(uint32_t *data, uint32_t data_len, uint32_t address);
HAL_StatusTypeDef WriteFlashU32(uint32_t *data, uint32_t data_len, uint32_t address);
void ReadFlashU32(uint32_t *data, uint32_t data_len, uint32_t address);
HAL_StatusTypeDef EraseFlashPage(uint32_t address, uint16_t page_num);
HAL_StatusTypeDef EraseFlash(uint32_t address, uint32_t length);

#endif
