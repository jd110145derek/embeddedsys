#include <msp430g2553.h> // Specific device
#include <intrinsics.h> // Intrinsic functions
#define LED1 BIT0
int main (void) {
  WDTCTL = WDTPW|WDTHOLD; // Stop watchdog timer
  P1OUT = ~LED1;   P1DIR = LED1;
  TACCR0 = 49999; // Upper limit of count for TAR
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
