#include  "msp430g2553.h"
int main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT 
  // TA1 trigger sample start
  ADC10CTL1 = SHS_1 + CONSEQ_2 + INCH_1;    
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + 
              ADC10ON + ADC10IE;
  __enable_interrupt();  // Enable interrupts.
  TACCR0 = 30;     // Delay for Volt Ref to settle
  TACCTL0 |= CCIE; // Compare-mode interrupt.
  TACTL = TASSEL_2 + MC_1; // SMCLK, Up mode.
  LPM0;                    // Wait for settle.
  TACCTL0 &= ~CCIE;     // Disable timer Interrupt
  __disable_interrupt();  
  ADC10CTL0 |= ENC;    // ADC10 Enable
  ADC10AE0 |= 0x02;    // P1.1 ADC10 option select
  P1DIR |= 0x01;       // Set P1.0 output
  TACCR0 = 2048;     // Sampling period
  TACCTL1 = OUTMOD_3;  // TACCR1 set/reset
  TACCR1 = 2047;       // TACCR1 OUT1 on time
  TACTL = TASSEL_1 + MC_1;    // ACLK, up mode

  // Enter LPM3 w/ interrupts
  __bis_SR_register(LPM3_bits + GIE);
}
  // ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  if (ADC10MEM < 0x155) // ADC10MEM = A1 > 0.5V?
    P1OUT &= ~0x01;     // Clear P1.0 LED off
  else
    P1OUT |= 0x01;      // Set P1.0 LED on
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void ta0_isr(void){
  TACTL = 0;
  LPM0_EXIT;            // Exit LPM0 on return
}
