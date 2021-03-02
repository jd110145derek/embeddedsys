#include <msp430g2553.h>
#define LED1 BIT0
#define B1 BIT3
volatile unsigned int i, j;
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT |= LED1 +B1;
  P1DIR = LED1;
  P1REN = B1 ;
  for(;;){
  while((P1IN & B1) !=0){
    i = P1IN; j = P1OUT; }
  P1OUT &= ~LED1;
  while((P1IN & B1) == 0){
    i = P1IN ; j = P1OUT; }
  P1OUT |= LED1;
  }
  }
