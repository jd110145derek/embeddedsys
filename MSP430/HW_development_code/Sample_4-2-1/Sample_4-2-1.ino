#include <msp430g2553.h>
#define B1 BIT3
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
  P1DIR = 0x01;              // P1.0 output, else input
  P1OUT = 0x10;              // P1.4 set, else reset
  P1REN |= 0x10;             // P1.4 pullup
  P1IE |= 0x10;              // P1.4 interrupt enabled
  P1IES |= 0x10;             // P1.4 Hi/lo edge
  //P1IFG &= ~0x10;            // P1.4 IFG cleared
  _BIS_SR(GIE);              // Enter interrupt
  while(1);
}
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
  P1OUT ^= 0x01;              // P1.0 = toggle
  P1IFG &= ~0x10;             // P1.4 IFG cleared
}
