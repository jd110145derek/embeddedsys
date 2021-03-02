/*
 * BlinkWithNoPrescaling.pde: 讓一顆燈號閃爍&#65292;每隔一秒切換一次燈號&#65292;使用 Timer 算時間
 */

volatile unsigned int count = 0; 
const int ledPin =  13;         // LED pin

void setup() {
  pinMode(ledPin, OUTPUT);      // 把 ledPin 設置成 output pin 
  
  TCCR1A = 0x00;                // Normal mode, just as a Timer

  TCCR1B &= ~_BV(CS12);         // no prescaling
  TCCR1B &= ~_BV(CS11);       
  TCCR1B |= _BV(CS10);     
  
  TIMSK1 |= _BV(TOIE1);         // enable timer overflow interrupt
  
  TCNT1 = 0;
}

void loop() {
  // do nothing
}

ISR (TIMER1_OVF_vect)
{  
  count++;
  
  if (count == 244) {             // overflow frequency = 16 MHz/65536 = 244Hz
    PORTB ^= _BV(5);              // Toggle LED, PB5 = Arduino pin 13
    count = 0;
  }  
}
