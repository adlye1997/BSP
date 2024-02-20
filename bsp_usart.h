#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "stm32f1xx_hal.h"

void UsartRxDmaInit(UART_HandleTypeDef *huart, uint8_t *rxbuf, uint16_t size);
void UsartIRQHandler(UART_HandleTypeDef *huart);
void UsartIdleInterrupt(UART_HandleTypeDef *huart);
void UsartIdleCallback(UART_HandleTypeDef *huart, uint16_t receive_data_length);
void WaitUartTramsmitDmaEnd(UART_HandleTypeDef *huart);

#endif
