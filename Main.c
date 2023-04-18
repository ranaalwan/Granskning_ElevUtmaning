#include "UART.h" // includes the UART header file

int main(){ // main function

  USART2_Init(); // initializes the USART2

  //test_setup(); 

  printf("Hello there from main function"); // prints a message to the console
  while(1){ // enters an infinite loop
  }
}
