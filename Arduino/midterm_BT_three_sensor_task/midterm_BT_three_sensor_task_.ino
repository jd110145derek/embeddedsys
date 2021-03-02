#include <Arduino_FreeRTOS.h>

#define PIN_MT_L1 6   // the trigger pin
#define PIN_MT_L2 5
#define PIN_MT_R1 10
#define PIN_MT_R2 9

#define PIN_TRIG 12    // the trigger pin sonar
#define PIN_ECHO 13 

#define PIN_TRIG1 7    // the trigger pin sonar1
#define PIN_ECHO1 8 

#define PIN_TRIG2 2    // the trigger pin sonar2
#define PIN_ECHO2 3 

typedef int TaskProfiler;

TaskProfiler ControlProfiler;
TaskProfiler AutoLEDProfiler;

TaskHandle_t  control_Handle,auto_Handle;

long snr_duration;
float distance;

long snr_duration1;
float distance1;

long snr_duration2;
float distance2;

char cmd;
byte spd = 100;
byte spd1 = 20;

int i=0 ;
int j=0 ;
int k=0 ;
int l=0 ;
int m=0 ;
int n=0 ;
void setup() {

 xTaskCreate(ControlTask,"Control Task",100,NULL,3,&control_Handle);
 xTaskCreate(AutoTask,"Auto Task",100,NULL,2,&auto_Handle);
   
    Serial.begin(9600);
    pinMode(PIN_MT_L1, OUTPUT);  
    pinMode(PIN_MT_L2, OUTPUT);  
    pinMode(PIN_MT_R1, OUTPUT);  
    pinMode(PIN_MT_R2, OUTPUT);  
    digitalWrite(PIN_MT_L1, LOW);
    digitalWrite(PIN_MT_L2, LOW);
    digitalWrite(PIN_MT_R1, LOW);
    digitalWrite(PIN_MT_R2, LOW);

    Serial.println(spd);
    Serial.println("initialize the Line Dectector program");

    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);

    pinMode(PIN_TRIG1, OUTPUT);
    digitalWrite(PIN_TRIG1, LOW);
    pinMode(PIN_ECHO1, INPUT);

    pinMode(PIN_TRIG2, OUTPUT);
    digitalWrite(PIN_TRIG2, LOW);
    pinMode(PIN_ECHO2, INPUT);
}
void ControlTask(void *pvParameters)
{
  while(1)
  {
  cmd = Serial.read();
    
    switch(cmd) {
        case 'w':
            analogWrite(PIN_MT_L1, spd);
            analogWrite(PIN_MT_R1, spd);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;
        case 'a':
            analogWrite(PIN_MT_L1, spd);
            analogWrite(PIN_MT_R1, 0); 
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;    
        case 's':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, spd);
            analogWrite(PIN_MT_R2, spd);
            break;
        case 'd':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, spd);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;
        case ' ':
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            break;
        case 'r':
        Serial.println(spd);
            if(spd <= 250) spd += 5;
            else    spd =255;
            break;
        case 'f':
        Serial.println(spd);
            if(spd >= 5) spd -= 5;
            else    spd =0;
            break;
        default:
            break;
    case 'g':
   
    vTaskSuspend(control_Handle);
    
    }
  }
}

void AutoTask(void *pvParameters)
{
    for(;;){
      if( Serial.read()== 'h'){
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);
            vTaskResume(control_Handle);
        break;
      }
      else{
  //sonar
    Serial.println("Sending soundwave  ;");
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    snr_duration = pulseIn(PIN_ECHO,HIGH);          // default timeout 1 sec
    //Serial.print("duration in microseconds: ");
    //Serial.println(snr_duration);
    
    distance = (float)snr_duration * 340 / 2 / 1000000;
    Serial.print("distance in meters: ");
    Serial.println(distance);
    
    //delay(20);                 // wait for 0.1 sec
//sonar1
    digitalWrite(PIN_TRIG1, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG1, LOW);
    
    snr_duration1 = pulseIn(PIN_ECHO1,HIGH);          // default timeout 1 sec
    //Serial.print("duration1 in microseconds: ");
    //Serial.println(snr_duration1);
    
    distance1 = (float)snr_duration1 * 340 / 2 / 1000000;
    Serial.print("distance1 in meters: ");
    Serial.println(distance1);
    
    //delay(20);                 // wait for 0.1 sec
    //sonar2
    digitalWrite(PIN_TRIG2, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG2, LOW);
    
    snr_duration2 = pulseIn(PIN_ECHO2,HIGH);          // default timeout 1 sec
    //Serial.print("duration2 in microseconds: ");
    //Serial.println(snr_duration2);
    
    distance2 = (float)snr_duration2 * 340 / 2 / 1000000;
    Serial.print("distance2 in meters: ");
    Serial.println(distance2);
    
    //delay(20);                 // wait for 0.1 sec

            analogWrite(PIN_MT_L1, spd);
            analogWrite(PIN_MT_R1, spd);
            analogWrite(PIN_MT_L2, 0);
            analogWrite(PIN_MT_R2, 0);

    if( distance2< 0.05 ){
      while( k <25000 ){
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0); 
            analogWrite(PIN_MT_L2, spd1);
            analogWrite(PIN_MT_R2, spd);
            k++ ;
      }
      k = 0;
    }
    if( distance1<0.05 ){
      while( j <20000 ){
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0); 
            analogWrite(PIN_MT_L2, spd1);
            analogWrite(PIN_MT_R2, spd);
            j++ ;
      }
      j = 0;
    }
    if( distance <0.09 ){
      while( i <30000 ){
            analogWrite(PIN_MT_L1, 0);
            analogWrite(PIN_MT_R1, 0); 
            analogWrite(PIN_MT_L2, spd);
            analogWrite(PIN_MT_R2, spd1);
            i++ ;
      }
      i = 0;
    }
 }
    }
}

void loop()
{}
