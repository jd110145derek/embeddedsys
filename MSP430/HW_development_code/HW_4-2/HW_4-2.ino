#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define B1 BIT3
int main(void) {
  WDTCTL =WDTPW|WDTHOLD;
  P1OUT =  ~LED2 + ~LED1 ;
  P1DIR = LED2 + LED1;
  P1REN |= B1 ;
  TACCR0 = 49999;
  TACTL = MC_1|ID_3|TASSEL_2|TACLR;
  P1IE |= B1;             // P1.3 Interrupt Enable
  P1IES |= B1;            // P1.3 Falling Trigger
  P1IFG &= ~B1;

  _BIS_SR(GIE);
 for (;;){
    while (!(TACTL&TAIFG)){

    }
    TACTL &= ~TAIFG;
    P1OUT ^=LED2;
  }
}
  #pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
     P1OUT ^= LED1;
      P1IFG &= ~B1;  // P1.3 IFG Cleared
    }
