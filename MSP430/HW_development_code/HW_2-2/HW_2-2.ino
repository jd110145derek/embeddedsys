#include <msp430g2553.h>
#define LED2 BIT6
#define B1 BIT3
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT |= LED2 +B1;
  P1DIR = LED2;
  P1REN = B1 ;
  for(;;){
    if ((P1IN & B1)==0){
      P1OUT &= ~LED2; }
    else{
      P1OUT |= LED2; }
    }
  }
