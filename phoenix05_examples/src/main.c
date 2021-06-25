/*
 ============================================================================
 Name        : main.c
 Author      : David Lin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello RISC-V World in C
 ============================================================================
 */
#include "lib_include.h"
#include <stdio.h>
#include "shell.h"

SHELL_TypeDef shell;

signed char uartRead(char* byte)
{
	*byte = UART_Receive();
	return 0;
}

void uartWrite(char byte)
{
	UART_Send(byte);
}

int main(void)
{
	u8 i;

	GPIO_PinConfigure(GPIO_PIN14, DISABLE, ENABLE, DISABLE, DISABLE, DISABLE);
	GPIO_SetPin(GPIO_PIN14);

    shell.read = uartRead;
    shell.write = uartWrite;
    shellInit(&shell);

    while(1)
    {
	    shellTask(&shell);
    }

	return 0;
}
