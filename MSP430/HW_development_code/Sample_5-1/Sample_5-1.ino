#include "msp430g2553.h"
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;    // Stop WDT
  // H&S time 16x, interrupt enabled
  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
  ADC10CTL1 = INCH_1;    // Input A1
  ADC10AE0 |= 0x02; // Enable pin A1 for analog in
  P1DIR |= 0x01;    // Set P1.0 to output
  for (;;)  {
    ADC10CTL0 |= ENC + ADC10SC; // Start sampling
    __bis_SR_register(CPUOFF + GIE); // Sleep
    if (ADC10MEM < 0x1FF) // 0x1FF = 511
      P1OUT &= ~0x01;  // Clear P1.0 LED off
    else
      P1OUT |= 0x01;    }
}
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)  {
  __bic_SR_register_on_exit(CPUOFF);
  // Clear CPUOFF bit from 0(SR)
}
