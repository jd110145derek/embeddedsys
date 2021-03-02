/*
 * externalInterrupt.pde: INT 0 外部中斷
 */

const int buttonPin = 2;                 // 按鈕(pushbutton)
const int ledPin = 13;                   // LED

void setup() {
  DDRD &= ~(1<<2);               //Set Button pin to be input with pullup
  PORTD |= (1<<2);

  DDRB |= (1<<5);                    //Failing edge  of INT0 generates interrupt
  
  EIMSK |= (1 << INT0);                  // enable INT 0
  EICRA |= (1 << ISC00);                 // pin 狀態改變時觸發中斷
  EICRA &= ~(1 << ISC01);  

 // Enable global interrupts
 sei();

}

void loop() {
  // do nothing
}


// Interrupt 0 的中斷處理函式
ISR(INT0_vect) {
  PORTB ^= (1<<5);
}
