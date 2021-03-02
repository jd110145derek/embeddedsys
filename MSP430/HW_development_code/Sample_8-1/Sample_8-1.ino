#include "msp430g2553.h"
#define UART_TXD 0x02
#define UART_RXD 0x04
#define UART_TBIT_DIV_2   (1000000 / (9600*2))
#define UART_TBIT        (1000000 / 9600)
unsigned int txData;
unsigned char rxBuffer;
void TimerA_UART_init(void);
void TimerA_UART_tx(unsigned char byte);
void TimerA_UART_print(char *string);
int main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  DCOCTL = 0x00;
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
  P1OUT = 0x00;
  P1SEL = UART_TXD + UART_RXD;
  P1DIR = 0xFF & ~UART_RXD;
  __enable_interrupt();
TimerA_UART_init();     // Start Timer_A UART
  TimerA_UART_print("G2xx2 TimerA UART\r\n");
  TimerA_UART_print("READY.\r\n");
  for (;;) {
    // Wait for incoming character
    __bis_SR_register(LPM0_bits);
    // Echo received character
    TimerA_UART_tx(rxBuffer);
  }
}
void TimerA_UART_print(char *string) {
  while (*string) TimerA_UART_tx(*string++);
}
void TimerA_UART_init(void) {
  TACCTL0 = OUT;   // Set TXD Idle as Mark = '1'
  TACCTL1 = SCS + CM1 + CAP + CCIE;     
  // Sync, Neg Edge, Capture, Int
  TACTL = TASSEL_2 + MC_2;  // SMCLK, continuous mode
}
void TimerA_UART_tx(unsigned char byte) {
  while (TACCTL0 & CCIE); // Ensure last char TX'd
  TACCR0 = TAR;      // Current state of TA counter
  TACCR0 += UART_TBIT; // One bit time till first bit
  TACCTL0 = OUTMOD0 + CCIE; // Set TXD on EQU0, Int
  txData = byte;       // Load global variable
  txData |= 0x100;    // Add mark stop bit to TXData
  txData <<= 1;       // Add space start bit
}
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void) {
  static unsigned char txBitCnt = 10;
  TACCR0 += UART_TBIT;     // Add Offset to CCRx
  if (txBitCnt == 0) {     // All bits TXed?
    TACCTL0 &= ~CCIE;   // All bits TXed, disable int
    txBitCnt = 10;        // Re-load bit counter
  } else {
    if (txData & 0x01) {
      TACCTL0 &= ~OUTMOD2;  // TX Mark '1’
    } else {
      TACCTL0 |= OUTMOD2;} // TX Space '0‘
  txData >>= 1;        txBitCnt--;
  }
} 
