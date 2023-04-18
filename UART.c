#include "UART.h"  //Inkluderar "UART.h" file som innehåller deklarationer av funktionerna och de nödvändiga biblioteken som behövs för att kommunicera med UART.

void USART2_Init(void){    //Definierar en funktion som initierar UART-kommunikationen med hjälp av USART2 på STM32.
 
 //Aktiverar klockorna till USART2 och GPIOA på rätt register genom att ändra bitar i RCC:s (Reset and Clock Control) register.
RCC->APB1ENR  |=  0x20000; 
RCC->AHB1ENR   |=0x01;
 
//Sätter upp GPIOA-pinnarna för att fungera som alternativ funktion till USART2 genom att sätta bits 5-6 till 1 i MODER (mode register) och bits 4-7 till 7 i AFR (alternate function register).
GPIOA->MODER &=~0x00F0;
GPIOA->MODER |= 0x00A0; 

//Sätter upp GPIOA-pinnarna för att fungera som alternativ funktion till USART2 genom att sätta bits 8-15 till 7 i AFR.
GPIOA->AFR[0] &= ~0xFF00;
GPIOA->AFR[0] |= 0x7700;

//Sätter upp USART2:s Baud Rate Register (BRR) till det värde som motsvarar den önskade baud rate, samt sätter konfigurationsregistren CR1, CR2 och CR3 till nödvändiga inställningar för att initiera USART2-kommunikationen.
USART2->BRR  =  0x0683;
USART2->CR1  =  0x000C; 
USART2->CR2  =  0x000;
USART2->CR3  =  0x000;
USART2->CR1  |=  0x2000; 
}


//Skickar en karaktär över USART2 genom att vänta på att sändningsregistret (SR) är tomt och sedan skriva karaktären till dataregistret (DR)
int USART2_write(int ch){

	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch & 0xFF);
	
  return ch;
}

//Läser in en karaktär över USART2 genom att vänta på att mottagningsregistret (SR) har blivit fyllt och sedan läsa av karaktären från dataregistret (DR).
int USART2_read(void){
  while(!(USART2->SR & 0x0020)){}
	return USART2->DR;
}

//Skapar en struktur som fungerar som en filpekare och definierar tre variabler av denna struktur för standard in-, ut- och felutgång.
struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


//läser en byte från USART2 och konverterar \r till \n om den hittas. Returnerar sedan den lästa byten.
int fgetc(FILE *f) {
    int c;

    c = USART2_read();     // läser in ett tecken från USART2

    if (c == '\r') {        // om tecknet är en radbrytning
        USART2_write(c);    // skickar en radbrytning
        c = '\n';           // sätter värdet till att vara en ny rad
    }

    USART2_write(c);        // skickar tecknet till USART2

    return c;               // returnerar det inlästa tecknet
}


//skickar en byte via USART2 och returnerar densamma byte.
int fputc(int c, FILE *f) {
    return USART2_write(c); // skickar det angivna tecknet till USART2
}


int n;
char str[80];
		
void test_setup(void){
	
	printf("please enter a number: ");  // skriver ut en meddelande till USART2
	scanf("%d", &n);                    // läser in ett heltal från USART2
	printf("the number entered is: %d\r\n", n);  // skriver ut det inmatade heltalet till USART2
	printf("please type a character string: "); // skriver ut en meddelande till USART2
	gets(str);                           // läser in en sträng från USART2
	printf("the character string entered is: ");  // skriver ut en meddelande till USART2
	puts(str);                           // skickar den inmatade strängen till USART2
	printf("\r\n");                      // skickar en radbrytning och nyrad till USART2
	
}
