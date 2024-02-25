#include "bsp_spi.h"
#include "main.h"
#include "delay.h"

/* 软件模拟SPI */

void BspSpiReceiveSoft(uint8_t *rxbuf, uint16_t len) {
	uint8_t dat;
	CS_RESET
	CLK_RESET
	DelayUs(2);
	for(uint16_t i = 0; i < len; i++) {
		for(uint8_t j = 0; j < 8; j++) {
			HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
			DelayUs(1);
			dat = dat << 1;
			if(READ_MISO == GPIO_PIN_SET) {
				dat |= 0x01;
			}
			HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
			DelayUs(1);
		}
		rxbuf[i] = dat;
	}
	CS_SET
	DelayUs(2);
}