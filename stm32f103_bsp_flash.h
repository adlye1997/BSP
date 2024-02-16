#ifndef __STM32F103_BSP_FLASH_H
#define __STM32F103_BSP_FLASH_H

#include "stm32f1xx_hal.h"

HAL_StatusTypeDef WriteFlashU16(uint16_t *data, uint16_t data_len, uint32_t address);
HAL_StatusTypeDef WriteFlashU32(uint32_t *data, uint16_t data_len, uint32_t address);
HAL_StatusTypeDef WriteFlashU64(uint64_t *data, uint16_t data_len, uint32_t address);

void ReadFlashU16(uint16_t *data, uint16_t data_len, uint32_t address);
void ReadFlashU32(uint32_t *data, uint16_t data_len, uint32_t address);
void ReadFlashU64(uint64_t *data, uint16_t data_len, uint32_t address);

HAL_StatusTypeDef EraseFlashPage(uint32_t address);

#endif
