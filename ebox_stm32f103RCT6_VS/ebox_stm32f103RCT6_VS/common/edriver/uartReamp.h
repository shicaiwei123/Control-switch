/*��Uart1��IO����ӳ�䣬��Ϊռ���˶�ʱ��1��A9��A10������ӳ�䵽B6��B7*/
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