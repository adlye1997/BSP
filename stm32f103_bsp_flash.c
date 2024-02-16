#include "stm32f103_bsp_flash.h"

HAL_StatusTypeDef WriteFlashU16(uint16_t *data, uint16_t data_len, uint32_t address)
{
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();
	if (status == HAL_OK) {
			for (uint32_t i = 0; i < data_len; i++) {
					status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address, data[i]);
					if (status != HAL_OK) {
						return status;
					}
					address += 2;
			}
			HAL_FLASH_Lock();
	}
	return status;
}

HAL_StatusTypeDef WriteFlashU32(uint32_t *data, uint16_t data_len, uint32_t address)
{
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();
	if (status == HAL_OK) {
			for (uint32_t i = 0; i < data_len; i++) {
					status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, data[i]);
					if (status != HAL_OK) {
						return status;
					}
					address += 4;
			}
			HAL_FLASH_Lock();
	}
	return status;
}

HAL_StatusTypeDef WriteFlashU64(uint64_t *data, uint16_t data_len, uint32_t address)
{
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();
	if (status == HAL_OK) {
			for (uint32_t i = 0; i < data_len; i++) {
					status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data[i]);
					if (status != HAL_OK) {
						return status;
					}
					address += 8;
			}
			HAL_FLASH_Lock();
	}
	return status;
}

void ReadFlashU16(uint16_t *data, uint16_t data_len, uint32_t address)
{
	for(uint16_t i = 0; i < data_len; i++)
	{
		*data = *(uint16_t*)address;
		data += 1;
		address += 2;
	}
}

void ReadFlashU32(uint32_t *data, uint16_t data_len, uint32_t address)
{
	for(uint16_t i = 0; i < data_len; i++)
	{
		*data = *(uint32_t*)address;
		data += 1;
		address += 4;
	}
}

void ReadFlashU64(uint64_t *data, uint16_t data_len, uint32_t address)
{
	for(uint16_t i = 0; i < data_len; i++)
	{
		*data = *(uint64_t*)address;
		data += 1;
		address += 8;
	}
}

HAL_StatusTypeDef EraseFlashPage(uint32_t address)
{
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();
	
	if (status == HAL_OK) {
		uint32_t PageError = 0;
		FLASH_EraseInitTypeDef EraseInitStruct;

		EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = address;
		EraseInitStruct.NbPages = 1;
		status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

    HAL_FLASH_Lock();
	}
	return status;
}
