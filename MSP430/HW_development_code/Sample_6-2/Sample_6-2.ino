#include  "msp430g2553.h"
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
  BCSCTL1 = CALBC1_1MHZ;  // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;   // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;  // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;   // SMCLK
  UCA0BR0 = 104;          // 1MHz 9600
  UCA0BR1 = 0;            // 1MHz 9600
  UCA0MCTL = UCBRS0;      // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;   // Initialize USCI 
  IE2 |= UCA0RXIE;  // Enable USCI_A0 RX interrupt
  // Enter LPM0, interrupts enabled
  __bis_SR_register(LPM0_bits + GIE);       }
//  Echo back RXed character, 
// confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
  // USCI_A0 TX buffer ready?
  while (!(IFG2&UCA0TXIFG));
    UCA0TXBUF = UCA0RXBUF; // TX -> RXed character
}
