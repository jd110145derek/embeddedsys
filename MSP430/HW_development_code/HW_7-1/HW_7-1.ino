#include <msp430g2553.h> // Specific device
//#include <intrinsics.h> // Intrinsic functions
#define LED1 BIT0
#define LED2 BIT6
#define B1 BIT3
int main(void) {
  WDTCTL = WDT_ADLY_1000; // Interval ~1000ms
  IE1 |= WDTIE;         // Enable WDT interrupt
  P1DIR |= LED1 + LED2;        // Set LED2 to output


  P1OUT |= ~LED1 + B1 ;
  P1REN = B1;
  P1IE |= BIT3;                   // P1.3 Interrupt Enable
  P1IES |= BIT3;                  // P1.3 Falling Trigger
  P1IFG &= ~BIT3;

TACCR0 = 49999; // Upper limit of count for TAR
  TACCTL0 = CCIE; // Enable interrupts 
  TACTL = MC_1|ID_3|TASSEL_2|TACLR; 

  __enable_interrupt(); // Enable interrupts (intrinsic)
  
  _BIS_SR(LPM0_bits + GIE);  // LPM0 w/ interrupt
}
// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void) {
  P1OUT ^= LED2;// Toggle LED2
}
/*  #pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
    if ((P1IN & B1)==0){
  P1OUT |= LED1; 
}   
    else{
      P1OUT &= ~LED1; }
    } */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TA0_ISR (void){
  if ((P1IN & B1)==0){
  P1OUT ^= LED1; 
}   
    else{
      P1OUT &= ~LED1; }
}
