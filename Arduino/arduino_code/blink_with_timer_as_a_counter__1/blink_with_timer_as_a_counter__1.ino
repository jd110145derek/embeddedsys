/*
 *  Timer1AsCounter.pde: Timer1 As a Counter
 */
void setup() {
  Serial.begin(9600);                //開啟 Serial port,通訊速率為9600 bps

TCCR1A = 0x00;                      //Normal mode, just as a Timer/Counter

//External clock  source in T1/PD5 pin. Clock on rising edge.
//Note that T1/PD5 pin = Arduino pin 5
TCCR1B |= _BV(CS12);
TCCR1B |= _BV(CS11);
TCCR1B |= _BV(CS10);

TCNT1 = 0;
}


void loop() {
  Serial.print("TCNT1:");
  Serial.println(TCNT1);

  delay(1000);

}
