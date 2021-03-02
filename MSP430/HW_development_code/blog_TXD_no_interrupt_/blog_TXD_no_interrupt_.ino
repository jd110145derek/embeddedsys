#include "msp430g2553.h"
int main(void)
{
WDTCTL = WDTPW + WDTHOLD;      // stop watchdog timer
BCSCTL1 = CALBC1_1MHZ;         // Set DCO (SMCLK)、設定次系統時脈(提供給周邊模組使用)
DCOCTL = CALDCO_1MHZ;          // Set DCO (SMCLK)、設定次系統時脈(提供給周邊模組使用)
P1SEL = BIT1 + BIT2;           // P1.1 = RXD, P1.2 = TXD
P1SEL2 = BIT1 + BIT2;          // P1.1 = RXD, P1.2 = TXD
UCA0CTL0 |= UCPEN +UC7BIT;      // Enable Parity 開啟其偶校正，Data Bit = 7
UCA0CTL1 |= UCSSEL_2;          // UART模組使用SMCLK
UCA0BR0 = 104;                // 1MHZ 9600
UCA0BR1 = 0;                  // 1MHZ 9600
UCA0CTL1 &= ~UCSWRST;          // **Initialize USCI state machine**
while(1)
{
  while (!(IFG2 & UCA0TXIFG));  // USCI_A0 TX buffer ready?
  UCA0TXBUF = 0x03;            // Transmit character
 __delay_cycles(30000);         // delay
}
}
