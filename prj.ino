Code For Servo, Alcohol Sensor, ISR and Alarm.
#include "TimerOne.h"
#include<Servo.h>
Servo Myservo;
const int buzzer = 4;
const byte MOTOR1 = 2;
const byte MOTOR2 = 3;

unsigned int counter1 = 0;
unsigned int counter2 = 0;

float diskslots = 20;
void ISR_count1(){
  counter1++;  // increment Motor 1 counter value
} 
 
// Motor 2 pulse count ISR
void ISR_count2(){
  counter2++;  // increment Motor 2 counter value
} 

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt (MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR2), ISR_count2, RISING);  // Increase counter 2 when speed sensor pin goes High
  //Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
  Myservo.attach(5);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  float rotation1 = (counter1 / diskslots) * 60.00;  // calculate RPM for Motor 1
  counter1 = 0;  //  reset counter to zero
  float rotation2 = (counter2 / diskslots) * 60.00;  // calculate RPM for Motor 2
  counter2 = 0;  //  reset counter to zero
  if(rotation1 == 0 || rotation2 == 0){
    if(sensorValue>=500){
      Myservo.write(90);
    }else{
      Myservo.write(0);
    }
  }else if(rotation1 > 0 || rotation2 > 0){
     Myservo.write(0);
    if(sensorValue>=500){
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(100);        // ...for 1sec
    }
  }
}
