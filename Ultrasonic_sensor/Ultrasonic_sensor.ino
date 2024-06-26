/*
 * file: Ultrasonic_sensor.ino
 * author: Roy Vicerra
 * revision date: 10/25/2022
 *
 * Ultrasonic Sensor and LED
 */

#include <HCSR04.h>

HCSR04 hc(5,6);
int LED=7;

void setup() 
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
}

void loop() 
{
 Serial.print("Distance: ");
 Serial.println(hc.dist());
 delay(60);

 while(hc.dist()<=5)
 {
   digitalWrite(LED,HIGH);
   hc.dist();
 }

}
