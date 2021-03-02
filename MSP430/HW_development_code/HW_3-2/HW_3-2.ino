#include <msp430g2553.h>//要怎麼同時跑兩種
#define LED2 BIT6
#define LED1 BIT0
#define B1 BIT3
int main(void) {
  WDTCTL =WDTPW|WDTHOLD;
  P1OUT = ~LED2;
  P1DIR = LED1+LED2;
  P1REN = B1;
  TACCR0 =59999;
  TACTL = MC_1|ID_3|TASSEL_2|TACLR;

  for (;;){
    while (!(TACTL&TAIFG)){

      }

    TACTL &= ~TAIFG;
    if((P1IN & B1) ==0){
      P1OUT |= LED1; }
    else{
      P1OUT &= ~LED1;}

    P1OUT ^=(LED2);
  }
  }
