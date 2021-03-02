/*
 * Arduino_RX.pde: 使用 USART 接收資料
 */
void setup() {
  // 開啟 Serial port, 通訊速率為 9600 bps
  Serial.begin(9600);
}

void loop() {
  char ReceivedChar;

  if (Serial.available()) {
     ReceivedChar  = Serial.read();
     Serial.print(ReceivedChar);
}
}
