#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "stm32f1xx_hal.h"

#define CS_SET HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
#define CS_RESET HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
#define CLK_SET HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
#define CLK_RESET HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
#define READ_MISO HAL_GPIO_ReadPin(MISO_GPIO_Port, MISO_Pin)

void BspSpiReceiveSoft(uint8_t *rxbuf, uint16_t len);

#endif // !__BSP_SPI_H
