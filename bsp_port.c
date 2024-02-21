#include "bsp_port.h"

void PortInit(Port *port, void TransmitData(uint8_t *, uint16_t), void ReceiveData(uint8_t *, uint16_t)) {
	port->port_status = PORT_READY;
	port->tick_update = 0;
	port->TransmitData = TransmitData;
	port->ReceiveData = ReceiveData;
}


