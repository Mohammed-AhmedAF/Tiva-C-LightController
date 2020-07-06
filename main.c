#include "Macros.h"
#include "Std_Types.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TM4C123GH6PM.h"

void vidReceiveCommands(void);

int main(void)
{
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	GPIO_vidSetPinDirection(GPIO_PORTB,GPIO_PIN0,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN0,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTB,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT);

	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	UARTConfig_t strctUARTConfig;
	
	strctUARTConfig.u8Fraction = 11;
	strctUARTConfig.u8Integer = 104;
	strctUARTConfig.u8WordLength = UART_WORDSIZE_8;
	strctUARTConfig.u8ClockSource = UART_CLOCKSOURCE_RC;
	
	/*Initializing UART*/
	GPIOA->AFSEL |= 0x03;
	GPIOA->PCTL |= 0x11;
	UART_vidInit(&strctUARTConfig);
	
	UART_vidPutISRFunction(vidReceiveCommands);
	
	
	/*UART receive interrupt*/
			NVIC->IP[5] = 3 << 5;

	NVIC->ISER[0] |= 0x00000020;
	__enable_irq();

	while(1);
}

void vidReceiveCommands(void)
{
	u8 u8Byte = UART_u8GetReceivedByte();
	if (u8Byte == 'a')
	{
		GPIO_vidTogglePin(GPIO_PORTB,GPIO_PIN0);
	}
	else if (u8Byte == 'b')
	{
		GPIO_vidTogglePin(GPIO_PORTB,GPIO_PIN1);
	}
}