/*
 *  my_AnalogRead.pde:
 */
 int potPin = 3;        //select the input pin for the potentiometer
 int ledPin = 9;        //select the pin for LED
 
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = my_analogRead(potPin);
  Serial.println(sensorValue,DEC);

  sensorValue = sensorValue/4;   //convert from 0-1023 to 0-255
  analogWrite(ledPin,sensorValue);
  delay(150);  
}
int my_analogRead(unsigned int pin)
{
  unsigned int low, high;
  // set prescale to 128 and enable ADC
  // 16 MHz / 128 = 125 KHz, inside the desired 50-200 KHz range
  ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
  // set the analog reference (use default AVcc),
  // and select the channel, this also sets ADLAR(left-adjust result) to
  // 0 (result is right adjusted)
  ADMUX |= _BV(REFS0);        // default AVcc as the reference
  ADMUX &= ~_BV(ADLAR);       // result is right adjusted
  ADMUX |= (pin & 0x07);      // select the channel

  // start ADC conversion
  ADCSRA |= _BV(ADSC);

  // wait until coversion finish
  loop_until_bit_is_clear(ADCSRA, ADSC);

  // read and return result
  // We have to read ADCL first then ADCH
  low = ADCL;
  high = ADCH;

  // combine the two bytes
  return (high << 8) | low;
}
