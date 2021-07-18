#include "Macros.h"
#include "Std_Types.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "APP_interface.h"
#include "TM4C123GH6PM.h"



int main(void)
{
	/*LED on port B*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	/*UART on port A*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	
	/*LED configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN3,GPIO_DEN_SET);
	
	GPIO_vidSetPinDirection(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT);

	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	
	/*UART Configuration*/
	UARTConfig_t strctUARTConfig;
	
	/*Integer and fraction value for 9600 baudrate*/
	strctUARTConfig.u8Fraction = 11;
	strctUARTConfig.u16Integer = 104;
	strctUARTConfig.u8WordLength = UART_WORDSIZE_8;
	strctUARTConfig.u8ClockSource = UART_CLOCKSOURCE_RC;
	strctUARTConfig.u8RxTx = UART_RXTX_BOTH;
	strctUARTConfig.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	strctUARTConfig.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	strctUARTConfig.ptrF = vidReceiveCommands;
	
	/*Initializing UART*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x11);
	UART0_vidInit(&strctUARTConfig);
		
	
	/*UART receive interrupt*/
	/*Priority*/
	NVIC_vidSetPriority(NVIC_UART0,3);
	/*Enabling interrupt*/
	NVIC_vidSetInterrupt(NVIC_UART0);

	/*Global interrupt enable*/
	__enable_irq();

	while(1);
}


