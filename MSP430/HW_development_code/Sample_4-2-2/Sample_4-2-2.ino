#include <msp430g2553.h> 
void ConfigWDT(){
 WDTCTL = WDTPW + WDTHOLD;
 }
void ConfigClocks(){
P1OUT = 0x10 , P1REN |= 0x10 , P1IE |= 0x10;
}
void ConfigLEDs(){
P1DIR = 0x01;
}
void ConfigTimerA2(){
  P1IES |= 0x10 , P1IFG &= ~0x10;
 }
//#define ConfigWDT WDTCTL = WDTPW + WDTHOLD
//#define ConfigClocks P1OUT = 0x10 + P1REN |= 0x10 + P1IE |= 0x10
//#define ConfigLEDs P1DIR = 0x01
//#define ConfigTimerA2 P1IES |= 0x10 + P1IFG &= ~0x10 
int main(void) {
  ConfigWDT();
  ConfigClocks();
  ConfigLEDs();    // enable and turn off LED
  ConfigTimerA2();
  _BIS_SR(GIE);   // Turn on Interrupts
                  // GIE: general iterrupt enable
  while(1)
    P1OUT |= BIT0;  // turn on red LED
}
