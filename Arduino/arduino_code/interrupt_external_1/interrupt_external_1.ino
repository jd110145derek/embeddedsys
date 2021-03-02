/*
 * externalInterrupt.pde: INT 0 外部中斷
 */

const int interruptNumber = 0;           // Interrupt 0 在 pin 2 上
const int buttonPin = 2;                 // 按鈕(pushbutton)
const int ledPin = 13;                   // LED
volatile int buttonState;                // 用來儲存按鈕狀態

void setup() {
  pinMode(ledPin, OUTPUT);               // 把 ledPin 設置成 OUTPUT
  pinMode(buttonPin, INPUT);             // 把 buttonPin 設置成 INPUT
  
  EIMSK |= _BV(INT0);                    // enable INT 0
  EICRA &= ~_BV(ISC01);                  // pin 狀態改變時觸發中斷
  EICRA |= _BV(ISC00);                   
}

void loop() {
  // do nothing
}

// 讀取 buttonPin 的狀態&#65292;並反應到 ledPin 上
void buttonStateChanged() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, buttonState);
}

// Interrupt 0 的中斷處理函式
ISR(INT0_vect) {
  buttonStateChanged();
}
