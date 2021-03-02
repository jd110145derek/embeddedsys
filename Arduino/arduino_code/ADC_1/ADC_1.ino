/*
 * potentiometer
 * Reads an analog input on pin 3, prints the result to the serial monitor
 *  
 * This example code is in the public domain.
 */
 int potPin = 3;        //select the input pin for the potentiometer
 int ledPin = 9;        //select the pin for LED
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(potPin);
  Serial.println(sensorValue, DEC);

  sensorValue = sensorValue/4;   //convert from 0-1023 to 0-255
  analogWrite(ledPin,sensorValue);
  delay(150);  
}
