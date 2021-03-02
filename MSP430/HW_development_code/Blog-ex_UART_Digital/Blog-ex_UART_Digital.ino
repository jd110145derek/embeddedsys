#include <msp430g2553.h>
const char stringl [] = {"Hello World\r\n"};
void txSendByte(unsigned char sendData);
unsigned char txCount;
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;    //stop watchdog timer
  BCSCTL1 = CALBC1_1MHZ;        //Set DCO (SMCLK),設定次系統時脈(提供給周邊模組使用)
  DCOCTL = CALDCO_1MHZ;        //Set DCO (SMCLK),設定次系統時脈(提供給周邊模組使用)
  P1DIR |= BIT2;              //P1.2 = OUTPUT(TXD)
  P1OUT |= BIT2;              //P1.2 = High (Start Bit)(TX Idle Statuts)
  while(1)
  {
    if (txCount < sizeof stringl - 1)          //sizeof stringl = 14
       txSendByte(stringl[txCount++]);         //傳送下一個Byte
    else txCount = 0;                        //重頭開始傳送字串
       __delay_cycles(200000);
  }
}

void txSendByte (unsigned char sendData)
{
  unsigned char i ;
  P1OUT &= ~BIT2;                             //TX pin =0 (Start Bit)
  __delay_cycles(96);                          //Delay Baud Rate Time
  for (i= BIT0 ; i !=0 ; i<<=1)                //Data Bit = 8
  {
    if ((sendData & i) ==0) P1OUT &= ~BIT2;     //從對低位元(LSB)開始傳送，傳0
    else                  P1OUT |= BIT2;      //傳1
    __delay_cycles(96);                      //Delay Baud Rate Time
  }
  P1OUT |= BIT2;                             //P1.2 = High (Stop Bit)(TX Idle Status)
  __delay_cycles(96);                         //Stop Bit = 1, (Delay 一個，接收端選擇 Stop bit = 1)
  __delay_cycles(96);                         //Stop Bit = 2, (Delay 兩個，接收端選擇 Stop bit = 1 or 20
}
