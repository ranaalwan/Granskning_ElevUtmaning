#ifndef __UART_H // Om __UART_H inte har definierats tidigare, definiera det här
#define __UART_H // Definiera __UART_H här


#include "stm32f4xx.h" // Inkludera headerfilen för STM32F4-serien mikrokontroller
#include <stdio.h> // Inkludera standard input/output biblioteket


void USART2_Init(void); // Funktion för att initiera USART2
void test_setup(void); // Funktion för att göra inställningar för USART2


#endif // Avsluta ifndef-makrodefinieringen