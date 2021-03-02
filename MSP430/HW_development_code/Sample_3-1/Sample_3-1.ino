#include <msp430g2553.h>
#define LED1 BIT0
int main(void) {
  WDTCTL =WDTPW+WDTHOLD;
  P1OUT = ~LED1;
  P1DIR = LED1;
  TACCR0 = 49999;
  TACTL = MC_1|ID_3|TASSEL_2|TACLR;
  for (;;){
    while (!(TACTL&TAIFG)){

    }
    TACTL &= ~TAIFG;
    P1OUT ^=LED1;
  }
}
