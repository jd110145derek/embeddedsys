/*#include <msp430g2553.h>
#define LED2 BIT6
int main(void) {
 WDTCTL =WDTPW+WDTHOLD;
  P1OUT = ~LED1;
  P1DIR = LED1;
  TACCR0 = 49999;
  TACTL = MC_1|ID_3|TASSEL_2|TACLR;
  for (;;) {
    while(!(TACTL&TAIFG)) {
    }
    TACTL &= ~TAIFG;
    P1OUT ^=LED2;
  }
}*/


#include <msp430g2553.h>
#define LED2 BIT6
int main(void) {
 WDTCTL =WDTPW+WDTHOLD;
 if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ ==0xFF) while(1);
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =CALDCO_1MHZ;
  P1DIR = 0x41;
  P1OUT = LED2;
  BCSCTL3 |=LFXT1S_0;
  IFG1 &= ~OFIFG;
  P1OUT = 0;
  BCSCTL2 |= ~SELS + DIVS_3;
  
  //P1OUT = ~LED2;
  //P1DIR = LED2;
  TACCR0 = 4096;
  TACTL = MC_1|ID_1|TASSEL_2|TACLR;
   for (;;) {
    while(!(TACTL&TAIFG)) {
    }
    TACTL &= ~TAIFG;
    P1OUT ^=LED2;
  }
}
