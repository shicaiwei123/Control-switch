/*对Uart1的IO口重映射，因为占用了定时器1的A9和A10，将其映射到B6和B7*/
#ifndef _UART_REMAP
#define _UART_REMAP
#include "ebox.h"
#include"stm32f10x.h"
class uartRemap:public Uart
{
public:
	uartRemap(USART_TypeDef *USARTx, Gpio *tx_pin, Gpio *rx_pin);
	void remap();
	~uartRemap();

private:
	USART_TypeDef *USARTx;
};

#endif // !