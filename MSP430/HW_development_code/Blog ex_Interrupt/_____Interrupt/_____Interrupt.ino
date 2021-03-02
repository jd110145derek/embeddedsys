#include <msp430.h>
#define LED1 BIT0

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer
  P1OUT = ~LED1;
  P1DIR = LED1;
  P1REN |= BIT3;

  P1IE |= BIT3;                   // P1.3 Interrupt Enable
  P1IES |= BIT3;                  // P1.3 Falling Trigger
  P1IFG &= ~BIT3;

  _BIS_SR(GIE);
  while (1) {}
}

// Port1 Interrupt Service Routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
  P1OUT ^= LED1;
  P1IFG &= ~BIT3;  // P1.3 IFG Cleared
}
