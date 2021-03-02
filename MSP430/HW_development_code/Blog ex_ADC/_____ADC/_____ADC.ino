#include <msp430.h>

int main(void) {
  WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;

  ADC10CTL1 = INCH_1; // Input A1

  ADC10AE0 |= 0x02; //Enable A1 for analog input

  P1DIR |= 0x01;

  for (;;)
  {
    ADC10CTL0 |= ENC + ADC10SC;
    __bis_SR_register(CPUOFF + GIE); // SLEEP

    if (ADC10MEM > 0x1FF) // 0x1FF = 511
      P1OUT &= ~0x01; // LED off
    else
      P1OUT |= 0x01; // LED on
  }
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);
}
