#include "stm32f103_bsp_flash.h"
#include "bsp_usart.h"

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

HAL_StatusTypeDef OverWriteFlashU32(uint32_t *data, uint16_t data_len, uint32_t address)
{
	EraseFlash(address, data_len * 4);
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

void ReadFlashU32(uint32_t *data, uint16_t data_len, uint32_t address)
{
	for(uint16_t i = 0; i < data_len; i++)
	{
		*data = *(uint32_t*)address;
		data += 1;
		address += 4;
	}
}

HAL_StatusTypeDef EraseFlashPage(uint32_t address, uint16_t page_num)
{
	HAL_StatusTypeDef status = HAL_FLASH_Unlock();

	if (status == HAL_OK) {
		uint32_t PageError = 0;
		FLASH_EraseInitTypeDef EraseInitStruct;

		EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = address;
		EraseInitStruct.NbPages = page_num;
		status = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

    HAL_FLASH_Lock();
	}
	return status;
}

uint32_t flash_reserve1[256];
uint32_t flash_reserve2[256];
void EraseFlash(uint32_t address, uint16_t length) {
	uint32_t address_erase_begin = (address - FLASH_SECTOR_BASE_ADDRESS) / FLASH_PAGE_SIZE * FLASH_PAGE_SIZE + FLASH_SECTOR_BASE_ADDRESS;
	uint32_t address_erase_end = (address + length - FLASH_SECTOR_BASE_ADDRESS) / FLASH_PAGE_SIZE * FLASH_PAGE_SIZE + FLASH_SECTOR_BASE_ADDRESS + FLASH_PAGE_SIZE - 1;
	uint32_t erase_page_num = (address_erase_end - address_erase_begin) / FLASH_PAGE_SIZE + 1;
	uint32_t address_reserve1_end = address - 1;
	uint32_t address_reserve2_begin = address + length;
	uint32_t reserve1_length = address_reserve1_end - address_erase_begin + 1;
	uint32_t reserve2_length = address_erase_end - address_reserve2_begin + 1;

	ReadFlashU32(flash_reserve1, reserve1_length / 4, address_erase_begin);
	ReadFlashU32(flash_reserve2, reserve2_length / 4, address_reserve2_begin);
	EraseFlashPage(address_erase_begin, erase_page_num);
	WriteFlashU32(flash_reserve1, reserve1_length / 4, address_erase_begin);
	WriteFlashU32(flash_reserve2, reserve2_length / 4, address_reserve2_begin);
}
