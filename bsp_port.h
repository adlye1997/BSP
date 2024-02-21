#ifndef __BSP_PORT_H
#define __BSP_PORT_H

#include "stm32f1xx_hal.h"

typedef struct {
	uint8_t port_status;
	uint16_t tick_update;
	void (*TransmitData)(uint8_t *data, uint16_t length);
	void (*ReceiveData)(uint8_t *data, uint16_t length);
}Port;

typedef enum {
	PORT_READY = 0,
	PORT_TIMEOUT,
	PORT_ERROR,
}PortStatus;

void PortInit(Port *port, void TransmitData(uint8_t *, uint16_t), void ReceiveData(uint8_t *, uint16_t));

#endif
