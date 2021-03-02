int main(void) {
  WDTCTL = WDT_ADLY_1000; // Interval ~1000ms
  IE1 |= WDTIE;         // Enable WDT interrupt
  P1DIR |= 0x01;        // Set P1.0 to output
  _BIS_SR(LPM0_bits + GIE);  // LPM0 w/ interrupt
}
// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void) {
  P1OUT ^= 0x01;      // Toggle P1.0
}
