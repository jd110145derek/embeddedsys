#include "msp430g2553.h"
#define LED1 BIT0
#define LED2 BIT6
int temp_ =0 ;
int main(void) {
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  ADC10CTL1 = SHS_1 + CONSEQ_2 + INCH_10;    
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + 
              ADC10ON + ADC10IE;
  __enable_interrupt();  // Enable interrupts.

  /*if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ ==0xFF) while(1);  //DCO as src of MCLK
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =CALDCO_1MHZ;
      P1DIR = 0x41;
      P1OUT = 0x41;
  BCSCTL3 |=LFXT1S_0;
  IFG1 &= ~OFIFG;
      P1OUT = 0;
  BCSCTL2 |= SELM_3 + DIVM_3;  */
 
  TACCR0 = 30;     // Delay for Volt Ref to settle
  TACCTL0 |= CCIE; // Compare-mode interrupt.
  TACTL = TASSEL_2 + MC_1; // SMCLK, Up mode.
  LPM0;                    // Wait for settle.
  TACCTL0 &= ~CCIE;     // Disable timer Interrupt
  __disable_interrupt();    

  if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ ==0xFF) while(1); //VLO as ACLK
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL =CALDCO_1MHZ;
      //P1DIR = 0x41;
      //P1OUT = 0x41;
  BCSCTL3 |=LFXT1S_2; //Enable VLO as ACLK src
  IFG1 &= ~OFIFG;
      //P1OUT = 0;
  
  ADC10CTL0 |= ENC;    // ADC10 Enable
  ADC10AE0 |= 0x02;    // P1.1 ADC10 option select
  P1DIR |= 0x41;       // Set P1.0 P1.6 output
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
  
  if (ADC10MEM < temp_) 
     P1OUT ^= LED1;
   if (ADC10MEM > temp_) 
     P1OUT ^= LED2;
   if (ADC10MEM == temp_) 
     P1OUT ^= LED1 + LED2;
    
     // save current reading 
     temp_ = ADC10MEM;
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void ta0_isr(void){
  TACTL = 0;
  LPM0_EXIT;            // Exit LPM0 on return
}
