#include <msp430g2553.h> // Specific device
#include <intrinsics.h> // Intrinsic functions
#define LED1 BIT6
int main (void) {
  WDTCTL = WDTPW|WDTHOLD; // Stop watchdog timer

if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ ==0xFF) while(1);
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =CALDCO_1MHZ;
  P1DIR = LED1;
  P1OUT = LED1;
  BCSCTL3 |=LFXT1S_2;
  IFG1 &= ~OFIFG;
  TACCR0 = 9999; // Upper limit of count for TAR
  P1OUT = 0;
  BCSCTL2 |= SELM_3 + DIVS_3;
  TACCTL0 = CCIE; // Enable interrupts 
  TACTL = MC_1|ID_3|TASSEL_2|TACLR; 
  // Up mode, divide clock by 8, clock from SMCLK, clear
  __enable_interrupt(); // Enable interrupts (intrinsic)
  
  for (;;) {  }
}
// Interrupt service routine for Timer_A
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR (void){
  P1OUT ^= LED1; // Toggle LED
}
