const char stringl [] = {"Hello World\r\n"};
unsigned char txCount;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;    //stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;        //Set DCO (SMCLK),設定次系統時脈(提供給周邊模組使用)
  DCOCTL = CALDCO_1MHZ;        //Set DCO (SMCLK),設定次系統時脈(提供給周邊模組使用)
  P1SEL = BIT1 + BIT2;              //P1.1 = RXD, P1.2 = TXD
  P1SEL2 = BIT1 + BIT2;              //P1.1 = RXD, P1.2 = TXD
  UCA0CTL1 |= UCSSEL_2;              //UART模組使用SMCLK
  UCA0BR0 = 104;                    //1MHZ 9600
  UCA0BR1 = 0 ;                     //1MHZ 9600
  UCA0CTL1 &= ~UCSWRST;              //**Initialize USCI state machine**
  IE2 |= UCA0RXIE;                   //Enable USCI_A0 RX interrupt
  __bis_SR_register(GIE);             //Interrupts enabled
  while(1);
}
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  if (txCount < sizeof stringl - 1)    //sizeof stringl = 14
      UCA0TXBUF = stringl[txCount++];  //傳送下一個Byte
  else
      IE2 &= ~UCA0TXIE;               //最後一個Byte傳完之後，關閉TX Interrupt
}
