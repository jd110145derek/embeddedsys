#include "msp430g2553.h"
unsigned char rxData;
int main(void)
{
WDTCTL = WDTPW + WDTHOLD;      // stop watchdog timer
BCSCTL1 = CALBC1_1MHZ;         // Set DCO (SMCLK)、設定次系統時脈(提供給周邊模組使用)
DCOCTL = CALDCO_1MHZ;          // Set DCO (SMCLK)、設定次系統時脈(提供給周邊模組使用)
P1DIR |= BIT0;                //設定P1.0為輸出(Output)
P1OUT &= ~BIT0;                //P1.0 一開始輸出為 Low(滅燈)
P1SEL = BIT1 + BIT2;           // P1.1 = RXD, P1.2 = TXD
P1SEL2 = BIT1 + BIT2;          // P1.1 = RXD, P1.2 = TXD
UCA0CTL1 |= UCSSEL_2;          // UART模組使用SMCLK
UCA0BR0 = 104;                // 1MHZ 9600
UCA0BR1 = 0;                  // 1MHZ 9600
UCA0CTL1 &= ~UCSWRST;          // **Initialize USCI state machine**
IE2 |= UCA0RXIE;               //Enable USCI_A0 RX interrupt
__bis_SR_register(GIE);         //Interrupts enabled

while(1);
}
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  rxData = UCA0RXBUF;          // Receive Character
  if (rxData =='1')
  P1OUT |= BIT0;
  else
  P1OUT &= ~BIT0;
}
