#include <IRremote.h>

const byte IR_RECEIVE_PIN = 11;
int LED=9;
int Nib1=3;
int Nib2=5;
int Nib3=6;
int Nib4=10;
 

void setup()
{
   Serial.begin(115200);
   Serial.println("IR Receive test");
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
   pinMode(LED,OUTPUT);
   pinMode(Nib1,OUTPUT);
   pinMode(Nib2,OUTPUT);
   pinMode(Nib3,OUTPUT);
   pinMode(Nib4,OUTPUT);
}

void loop()
{
   if (IrReceiver.decode())
   {
      Serial.println(IrReceiver.decodedIRData.command);
      digitalWrite(LED,HIGH);
      
      if(IrReceiver.decodedIRData.command==12)
      {
        for(int i=0;i<=255;i++)
         {
           analogWrite(Nib1,i);
           delay(10);
         }
        digitalWrite(Nib1,LOW);
      }

      if(IrReceiver.decodedIRData.command==24)
      {
        for(int i=0;i<=255;i++)
         {
           analogWrite(Nib2,i);
           delay(10);
         }

         digitalWrite(Nib2,LOW);
      }

      if(IrReceiver.decodedIRData.command==94)
      {
        for(int i=0;i<=255;i++)
         {
           analogWrite(Nib3,i);
           delay(10);
         }

         digitalWrite(Nib3,LOW);
      }

      if(IrReceiver.decodedIRData.command==8)
      {
         digitalWrite(Nib4,HIGH);
         delay(1200);
         digitalWrite(Nib4,LOW);
      }
      
      IrReceiver.resume();
      delay(10);
      digitalWrite(LED,LOW);
      
   }


}
