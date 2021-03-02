/*
 * Blink.pde: 讓一顆燈號閃爍，每隔一秒切換一次燈號
 */

const int ledPin =  13;         // LED pin

void setup() {                
  pinMode(ledPin, OUTPUT);      // 把 ledPin 設置成 output pin 
}

void loop() {
  digitalWrite(ledPin, HIGH);   // 打開 LED 燈號 
  delay(1000);                  // 延遲一秒鐘
  digitalWrite(ledPin, LOW);    // 關閉 LED 燈號 
  delay(1000);                  // 延遲一秒鐘
}
