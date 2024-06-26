/*
 * file: Ultrasonic_sensor&DC_Motor.ino
 * author: Roy Vicerra
 * revision date: 10/25/2022
 *
 * Ultrasonic Sensor and DC Motor
 */

#include <HCSR04.h>

HCSR04 hc(5,6);
int LED=7;
int Speed=11;
int Dir1=3;
int Dir2=4;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(Speed,OUTPUT);
  pinMode(Dir1,OUTPUT);
  pinMode(Dir2,OUTPUT);
}

void loop() 
{
 Serial.print("Distance: ");
 Serial.println(hc.dist());
 delay(60);

 while(hc.dist() > 100)
 {
   digitalWrite(LED,HIGH);
   Serial.print("Distance: ");
   Serial.println(hc.dist());
   digitalWrite(Dir1,LOW);
   digitalWrite(Dir2,HIGH);
   analogWrite(Speed,255);
   delay(60);
 }

 while(hc.dist() > 5 && hc.dist() < 100)
 {
   digitalWrite(LED,HIGH);
   Serial.print("Distance: ");
   Serial.println(hc.dist());
   digitalWrite(Dir1,HIGH);
   digitalWrite(Dir2,LOW);
   analogWrite(Speed,128);
   delay(60);
 }

 while(hc.dist() < 5)
 {
   digitalWrite(LED,LOW);
   Serial.print("Distance: ");
   Serial.println(hc.dist());
   digitalWrite(Dir1,LOW);
   digitalWrite(Dir2,HIGH);
   analogWrite(Speed,128);
   delay(60);
 }

}
