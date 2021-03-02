#include <msp430g2553.h>
int main(void) {
  WDTCTL =WDTPW|WDTHOLD;
  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ ==0xFF) while(1);
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =CALDCO_1MHZ;
  P1DIR = 0x41;
  P1OUT = 0x01;
  BCSCTL3 |=LFXT1S_0;
  IFG1 &= ~OFIFG;
  P1OUT = 0;
  BCSCTL2 |= SELS + DIVS_3;
}
