#include "uartReamp.h"
uartRemap::uartRemap(USART_TypeDef *USARTx, Gpio *tx_pin, Gpio *rx_pin) :Uart(USARTx, tx_pin, rx_pin)
{
	this->USARTx = USARTx;
}

uartRemap::~uartRemap()
{
}

void uartRemap::remap()
{
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//使能端口重映射
}