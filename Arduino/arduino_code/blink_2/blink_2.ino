/*
 * Blink.pde:  讓一顆燈號閃爍，每隔一秒切換一次燈號
 * schematic:
 *   Connect a LED on PB5 (Arduino pin 13)
 */

void setup()
{
  DDRB |= (1 << 5);      // 把 PB5 設置成 output pin 
}

void loop()
{
  PORTB |= (1 << 5);     // 打開 LED 燈號
  delay(1000); 
  PORTB &= ~(1 << 5);    // 關閉 LED 燈號 
  delay(1000);
}
