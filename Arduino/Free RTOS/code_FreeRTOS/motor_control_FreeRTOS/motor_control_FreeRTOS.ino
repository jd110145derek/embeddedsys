#include <Arduino_FreeRTOS.h>


// Pin definiton
#define encoderA 2 // define encoder phase A
#define encoderB 7 // define encoder phase B
#define motorPin 3 // define PWM output
#define interruptPin 2 // define external interrupt 

// speed patameter
#define count_per_cycle 1560
#define interval 50
#define t_s 5000


TaskHandle_t Input_Handle;
TaskHandle_t Output_Handle;
TaskHandle_t Encoder_Left_Handle;
TaskHandle_t Encoder_Right_Handle;

// Global variable
volatile int master_count = 0; // universal count
volatile int count = 0; // universal count

String inputString = "";    // a String to hold incoming data    
int pwm_T = 0;
int last_count = 0;
double Speed_Left = 0;
double Speed_Right = 0;



void setup() { 

// Pin Setting
pinMode (encoderA,INPUT); //埠口模式設定：outputA 設為 輸入
pinMode (encoderB,INPUT); //埠口模式設定：outputB 設為 輸入
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
// set direction
digitalWrite(12, HIGH);
digitalWrite(13, LOW);
pinMode(motorPin, OUTPUT); // 設定 pin 3 為輸出
attachInterrupt(digitalPinToInterrupt(interruptPin), Encoder_Left_Flag, RISING); 

// Serial communication
Serial.begin (9600); //Serial通訊鮑率設為9600
inputString.reserve(200);

// Create Task

xTaskCreate(  Serial_input,
              "Serial_input",
              100,
              NULL,
              2,  // priority 
              &Input_Handle
              );

xTaskCreate(  Serial_output,
              "Serial_output",
              100,
              NULL,
              1,  // priority 
              &Output_Handle
              );

xTaskCreate(  Motor,
              "Motor",
              100,
              NULL,
              3,  // priority 
              NULL
              );
              
xTaskCreate(  Enc_Left,
              "Encoder_Left",
              100,
              NULL,
              0,  // priority 
              &Encoder_Left_Handle
              );

xTaskCreate(  Enc_Right,
              "Encoder_Right",
              100,
              NULL,
              0,  // priority 
              &Encoder_Right_Handle
              );
     
} 

void Serial_input(void *pvParameters)
{
  while(1)
  {
    // Block the task
    vTaskSuspend(Input_Handle);

    // Read Data
    while (Serial.available() > 0) {
    char inChar = Serial.read();
    inputString += inChar;

    // if you get a newline, print the string,
    // then the string's value:
    if (  inChar == '\n') {
      //Serial.print("Value:");
      //Serial.println(inputString.toInt());
      //Serial.print("String: ");
      //Serial.println(inputString);
      pwm_T = inputString.toInt();
      // clear the string for new input:
      inputString = "";
    }
  }
  
  }
}

void Serial_output(void *pvParameters)
{
  while(1)
  {
     // Block the task
     vTaskSuspend(Output_Handle);

     // Output data
     //Serial.print("Time:");
     Serial.print(millis());
     Serial.print(" ");
     Serial.print(Speed_Left);
      Serial.print(" ");
     Serial.print(Speed_Right);
     Serial.print(" ");
     Serial.println(pwm_T);
     
  }
}

void Motor(void *pvParameters)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(interval); // set T 

  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  
  while(1)
  {
     // Wait for the next cycle.
     vTaskDelayUntil( &xLastWakeTime, xFrequency );
     
     /*
     if( millis() > 2 * t_s)
       pwm_T = 255;
     else if ( millis()> t_s )
       pwm_T = 125;
     */
     
     // make sure pwm_T = 0-255
     if(pwm_T < 0)
       pwm_T = 0;
     else if(pwm_T > 255)
       pwm_T = 255;
       
     // pwm output  
     noInterrupts();
     analogWrite(motorPin, pwm_T); // 0-255
     interrupts();

     // calculate speed
     Speed_Left = ((master_count - last_count)* 1000.0*60) / (count_per_cycle * interval) ;
     Speed_Right = ((count - last_count)* 1000.0*60) / (count_per_cycle * interval) ;
     master_count = 0;
     count = 0;
     
     // Unblock the task
     vTaskResume(Output_Handle);

     
  }
}

void Enc_Left(void *pvParameters)
{
  while(1)
  {
     // Block the task
     vTaskSuspend(Encoder_Left_Handle);
     
     // add 1 to count for CW
     if (digitalRead(encoderA) && !digitalRead(encoderB)) {
     master_count++ ;
     }
     // subtract 1 from count for CCW
     if (digitalRead(encoderA) && digitalRead(encoderB)) {
     master_count-- ;
     } 

     
  }
}

void Enc_Right(void *pvParameters)
{
  while(1)
  {
     // Block the task
     vTaskSuspend(Encoder_Right_Handle);
     
     // add 1 to count for CW
     if (digitalRead(encoderA) && !digitalRead(encoderB)) {
     count++ ;
     }
     // subtract 1 from count for CCW
     if (digitalRead(encoderA) && digitalRead(encoderB)) {
     count-- ;
     } 

     
  }
}

// ISR
void Encoder_Left_Flag() {
  // Unblock the task
  vTaskResume(Encoder_Left_Handle);
  vTaskResume(Encoder_Right_Handle);
}

void serialEvent() {
  // Unblock the task
  vTaskResume(Input_Handle);
}

void loop(){}
