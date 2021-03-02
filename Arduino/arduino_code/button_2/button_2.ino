
/*
 * Button.pde: 使用按鍵 (PushButton)控制 LED 燈號的開關
 * 
 * Pin map:
 *  Arduino pin 13 = PB5
 *  Arduino pin  2 = PD2 
 */

// 底下兩個常數程式沒有用到，只是當作參考 
const int buttonPin = 2;           // 按鈕(pushbutton)
const int ledPin = 13;             // LED

#define buttonPinBitMask  _BV(2)   // pin 2  = PD2
#define ledPinBitMask     _BV(5)   // pin 13 = PB5

int buttonState;                   // 用來儲存按鈕狀態

void setup()
{
  DDRB |= ledPinBitMask;           // 把 ledPin 設置成 OUTPUT
  DDRD &= ~buttonPinBitMask;       // 把 buttonPin 設置成 INPUT
}

void loop()
{    
  // 讀取按鈕的狀態
  if (PIND & buttonPinBitMask) {
    buttonState = HIGH;
  } else {
    buttonState = LOW;     
  }

  // 檢查按鈕是否被按下
  // 是的話&#65292;buttonState 會是 HIGH  
  if (buttonState == HIGH) {
    PORTB |= ledPinBitMask;         // 打開 LED
  } else {
    PORTB &= ~ledPinBitMask;        // 關閉 LED
  }
}
