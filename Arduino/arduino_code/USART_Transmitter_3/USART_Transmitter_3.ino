/*
 * USART_TX.pde: 使用 USART 傳資料，中斷版本
 */

 #define interrupt_on()  UCSR0B |= _BV(UDRIE0)
 #define interrupt_off() UCSR0B &= ~_BV(UDRIE0)

char message[] = "Hello World";
volatile int txbuffer_idx = 0;          // transmit buffer index
 
void setup() {
  // 開啟 Serial port, 通訊速率為 9600 bps
  mySerial_begin(9600);

  // 印出 "Hello World" 訊息到 Serial Port
  interrupt_on();

}

void loop() {
  // do nothing
}
// ISR for USART Data Register Empty interrupt
ISR(USART_UDRE_vect)
{
  char c = message[txbuffer_idx++];

  if (c != 0) {
    UDR0 = c;
    } else {
      interrupt_off();
  }
}
void mySerial_begin(unsigned long baud)
{
  // F_CPU is CPU clock, for Arduino UNO or Duemilinove, it is 16000000
  unsigned int baud_setting = (F_CPU / 16 / baud) - 1;

  // Set the baud rate
  UBRR0H = (unsigned char)(baud_setting >> 8);
  UBRR0L = (unsigned char)baud_setting;

  // Enable receiver and transmitter, no interrupt
  UCSR0B  |= _BV(RXEN0) | _BV(TXEN0);
  UCSR0B &= ~_BV(RXCIE0);
  UCSR0B &= ~_BV(TXCIE0);

  // Set frame format: No parity check, 8 Data bits, 1 stop bit
 UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}
