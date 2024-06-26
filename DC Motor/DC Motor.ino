int Speed=9;
int Dir1=4;
int Dir2=5;
 
void setup()
{
  Serial.begin(9600);
  pinMode(Speed,OUTPUT);
  pinMode(Dir1,OUTPUT);
  pinMode(Dir2,OUTPUT);
}
 
void loop()
{
 digitalWrite(Dir1,LOW);
 digitalWrite(Dir2,HIGH);
 analogWrite(Speed,80);
 delay(100);
 analogWrite(Speed,255);
 delay(100);

 for(int i=100;i<=128;i++)
  {
    analogWrite(Speed,i);
    delay(10);
  }
 
  delay(1000);
 
  for(int i=128;i<=255;i++)
  {
    analogWrite(Speed,i);
    delay(10);
  }
 
  delay(1000);
 
  for(int i=255;i>=100;i--)
  {
    analogWrite(Speed,i);
    delay(10);
  }
  
}