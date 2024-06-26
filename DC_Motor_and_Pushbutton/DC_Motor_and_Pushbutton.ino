/*
 * file: DC_Motor_and_Pushbutton.ino
 * author: Roy Vicerra
 * revision date: 10/25/2022
 *
 * DC Motor and Pushbutton
 */
 
int ButtonPin=12;
int buttonNew;
int State=0;
int buttonOld=1;
int Speed=9;
int Dir1=4;
int Dir2=5;
 
 
void setup() {
  Serial.begin(9600);
  pinMode(ButtonPin,INPUT);
  pinMode(Speed,OUTPUT);
  pinMode(Dir1,OUTPUT);
  pinMode(Dir2,OUTPUT);
 
}
 
void loop() {
  buttonNew=digitalRead(ButtonPin);
  Serial.print("Button State: ");
  Serial.println(buttonNew);

 
  if(buttonOld==0 && buttonNew==1)
  {
    if(State==0)
    {
      digitalWrite(Dir1,LOW);
      digitalWrite(Dir2,HIGH);
      analogWrite(Speed,0);
      delay(500);
      analogWrite(Speed,255);
      
      State=1;
    }
 
    else
    {
      digitalWrite(Dir1,HIGH);
      digitalWrite(Dir2,LOW);
      analogWrite(Speed,0);
      delay(500);
      analogWrite(Speed,255);
      State=0;
    }
   
  }
 
  buttonOld=buttonNew;
  delay(100);
 
}
