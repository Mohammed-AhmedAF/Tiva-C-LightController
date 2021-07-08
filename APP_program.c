#include "STD_TYPES.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include "APP_interface.h"

/*Holding the received character from UART*/
volatile u8 u8Byte;

void vidReceiveCommands(void)
{
	u8Byte = UART0_u8GetReceivedByte();
	if (u8Byte == 'a')
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	}
	else if (u8Byte == 'b')
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
	}
	else if (u8Byte == 'c')
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN3);
	}
}

