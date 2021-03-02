/*
 * Arduino_RX.pde: 使用 USART 接收資料，非中斷版本
 */
void setup() {
  // 開啟 Serial port, 通訊速率為 9600 bps
  mySerial_begin(9600);
}

void loop() {
  char ReceivedChar;

  // 等到 RXC0 (USART Receive Complete) 旗號豎起來時才代表有收到資料
  loop_until_bit_is_set(UCSR0A, RXC0);
  ReceivedChar  = UDR0;

  serial_putchar(ReceivedChar);
}
void serial_putchar(char c)
{
  // 等到 UDRE (USART Data Register Empty) 旗號豎起來才能放資料
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
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
