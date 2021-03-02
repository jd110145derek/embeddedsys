/*
 * Arduino_TX.pde: 使用 USART 傳資料
 */
char message[] = "Hello World" ;
void setup() {
  // 開啟 Serial port, 通訊速率為 9600 bps
  Serial.begin(9600);
  
  //印出 "Hello World" 訊息到 Serial Port
  Serial.print(message);
}

void loop() {
  // do nothing

}
