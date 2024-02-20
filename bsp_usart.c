#include "bsp_usart.h"

/* DMA usart receive part start */

/*
 * @brief Initial usart receive DMA
 * @note  DMA initialization must be front of usart initialization
*/
void UsartRxDmaInit(UART_HandleTypeDef *huart, uint8_t *rxbuf, uint16_t size)
{
  /* Enable usart IDLE interrupt */
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
  /* Receive an amount of data in DMA mode */
	HAL_UART_Receive_DMA(huart, rxbuf, size);
}

/*
 * @brief Usart interrupt
 * @note  Add this function into usart global interrupt
*/
void UsartIRQHandler(UART_HandleTypeDef *huart)
{
  if(__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE))
	{
    /* Clear IDLE flag */
		__HAL_UART_CLEAR_IDLEFLAG(huart);
    /* Usart IDLE Interrupt */
		UsartIdleInterrupt(huart);
	}
}

/*
 * @brief Usart IDLE interrupt
*/
void UsartIdleInterrupt(UART_HandleTypeDef *huart)
{
  uint16_t receive_data_length;

  /* Stop usart DMA */
  HAL_UART_DMAStop(huart);

  /* Calculate receive date length */
  receive_data_length = huart->RxXferSize - __HAL_DMA_GET_COUNTER(huart->hdmarx);

  /* Usart IDLE Callback */
  UsartIdleCallback(huart, receive_data_length);

  /* Receive an amount of data in DMA mode */
  HAL_UART_Receive_DMA(huart, huart->pRxBuffPtr, huart->RxXferSize);
}

/*
 * @brief Usart IDLE interrupt callback
*/
__weak void UsartIdleCallback(UART_HandleTypeDef *huart, uint16_t receive_data_length)
{

}

/* DMA usart receive part end */

void WaitUartTramsmitDmaEnd(UART_HandleTypeDef *huart) {
	while(__HAL_UART_GET_FLAG(huart, UART_FLAG_TC) == RESET) {
	}
}
