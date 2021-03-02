#include <Arduino_FreeRTOS.h>
typedef int TaskProfiler;
TaskProfiler ForwardProfiler;
TaskProfiler FirstProfiler;
TaskProfiler SecondProfiler;
TaskProfiler ThirdProfiler;
TaskProfiler FourthProfiler;
TaskHandle_t  Forward_Handle,First_Handle,Second_Handle,Third_Handle,Fourth_Handle;

#define PIN_MT_L1 6   // the trigger pin
#define PIN_MT_L2 5
#define PIN_MT_R1 10
#define PIN_MT_R2 9

#define PIN_TRIG 12    // the trigger pin sonar
#define PIN_ECHO 13 

long snr_duration;
float distance;

//char cmd;
//byte spd = 100;
//byte spd1 = 0;

unsigned int i=0 ;
unsigned int j=0 ;
unsigned int k=0 ;
unsigned int l=0 ;
unsigned int m=0 ;
unsigned int n=0 ;
unsigned int o=0 ;

void setup() {
 xTaskCreate(ForwardTask,"Forward Task",100,NULL,3,&Forward_Handle);
 xTaskCreate(FirstTask,"First Task",100,NULL,1,&First_Handle);
 xTaskCreate(SecondTask,"Second Task",100,NULL,1,&Second_Handle);
 xTaskCreate(ThirdTask,"Third Task",100,NULL,1,&Third_Handle);
 xTaskCreate(FourthTask,"Fourth Task",100,NULL,1,&Fourth_Handle);
    Serial.begin(9600);
    Serial.println("initialize the Line Dectector program");
    pinMode(PIN_MT_L1, OUTPUT);  
    pinMode(PIN_MT_L2, OUTPUT);  
    pinMode(PIN_MT_R1, OUTPUT);  
    pinMode(PIN_MT_R2, OUTPUT);  
    digitalWrite(PIN_MT_L1, LOW);
    digitalWrite(PIN_MT_L2, LOW);
    digitalWrite(PIN_MT_R1, LOW);
    digitalWrite(PIN_MT_R2, LOW);

    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
}
void ForwardTask(void *pvParameters)
{ 

    while(1){

    //Serial.println(80);
  
    analogWrite(PIN_MT_L1, 80);
    analogWrite(PIN_MT_R1, 80);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);

    //sonar
    //Serial.println("Sending soundwave  ;");
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    
    snr_duration = pulseIn(PIN_ECHO,HIGH);          // default timeout 1 sec
    //Serial.print("duration in microseconds: ");
    //Serial.println(snr_duration);
    distance = (float)snr_duration * 340 / 2 / 1000000;
    Serial.print("distance in meters: ");
    Serial.println(distance); 

    if( distance <0.2 ){

    analogWrite(PIN_MT_L1, 0);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
    delay(1000);
    vTaskPrioritySet(Forward_Handle,2);
    vTaskPrioritySet(First_Handle,3);
    } 
    }   
}

void FirstTask(void *pvParameters)
{   
  vTaskSuspend(Forward_Handle);
    while( i < 33000 ){
    analogWrite(PIN_MT_L1, 50);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      i++ ;
      }
    analogWrite(PIN_MT_L1, 0);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      i = 0;
    Serial.println(" First ");
    delay(1000);
    vTaskPrioritySet(First_Handle,2);
    vTaskPrioritySet(Second_Handle,3);
}
void SecondTask(void *pvParameters)
{   
  vTaskSuspend(First_Handle);
    while( j < 65000 ){
    analogWrite(PIN_MT_L1, 75);
    analogWrite(PIN_MT_R1, 122);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      j++ ;
      }
    analogWrite(PIN_MT_L1, 0);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      j = 0;

    Serial.println(" Second ");
    delay(1000);
    vTaskPrioritySet(Second_Handle,2);
    vTaskPrioritySet(Third_Handle,3);
}
void ThirdTask(void *pvParameters)
{   
  vTaskSuspend(Second_Handle);
    while( k < 65000 ){
    analogWrite(PIN_MT_L1, 75);
    analogWrite(PIN_MT_R1, 122);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      k++ ;
      }
    analogWrite(PIN_MT_L1, 0);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      k = 0;

    Serial.println(" Third ");
    delay(1000);
    vTaskPrioritySet(Third_Handle,2);
    vTaskPrioritySet(Fourth_Handle,3);
}
void FourthTask(void *pvParameters)
{   

    while( l < 36000 ){
    analogWrite(PIN_MT_L1, 50);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      l++ ;
      }
    analogWrite(PIN_MT_L1, 0);
    analogWrite(PIN_MT_R1, 0);
    analogWrite(PIN_MT_L2, 0);
    analogWrite(PIN_MT_R2, 0);
      l = 0;
    Serial.println(" Fourth ");
    delay(1000);   
    asm volatile ("  jmp 0");
}
void loop() {
}
