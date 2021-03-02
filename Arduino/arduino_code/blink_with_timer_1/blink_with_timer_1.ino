
/*
 * BlinkWithTimer1.pde: 讓一顆燈號閃爍&#65292;每隔一秒切換一次燈號&#65292;使用 Timer 算時間
 */
 
const int ledPin =  13;         // LED pin

void setup() {
  pinMode(ledPin, OUTPUT);      // 把 ledPin 設置成 output pin 
  
  TCCR1A = 0x00;                // Normal mode, just as a Timer

  TCCR1B |= _BV(CS12);          // prescaler = CPU clock/1024
  TCCR1B &= ~_BV(CS11);       
  TCCR1B |= _BV(CS10);        

  TCNT1 = 0;
}

void loop() {
  digitalWrite(ledPin, HIGH);   // 打開 LED 燈號 
  delay1s();                    // 延遲一秒鐘
  digitalWrite(ledPin, LOW);    // 關閉 LED 燈號 
  delay1s();                    // 延遲一秒鐘 
}

void delay1s()
{
  while (TCNT1 <15625)         // Ticks for 1 second @16 MHz,prescale=1024
    ;  // do nothing
  
  TCNT1 = 0;
}
