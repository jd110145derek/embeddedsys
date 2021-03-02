/*
 * BlinkWithBV.pde:  讓一顆燈號閃爍，每隔一秒切換一次燈號，使用 _BV() 巨集
 * schematic:
 *   Connect a LED on PB5 (Arduino pin 13)
 */

/* 在 avr-libc 中的 sfr_defs.h 有這樣的定義:
#define _BV(bit) (1 << (bit))
*/

void setup()
{
  DDRB |= _BV(5);      // 把 PB5 設置成 output pin
}

void loop()
{
  PORTB |= _BV(5);     // 打開 LED 燈號
  delay(1000); 
  PORTB &= ~_BV(5);    // 關閉 LED 燈號
  delay(1000);
}
