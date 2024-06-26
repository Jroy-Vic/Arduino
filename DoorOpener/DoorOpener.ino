#include <IRremote.hpp>
#include <Stepper.h>
#include <Servo.h>
#define IRpin 8
#define stepsPerRev 2048
#define speed 30
#define servoPin 9

Stepper stepper(stepsPerRev, 7, 6, 5, 4);
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(IRpin);
  stepper.setSpeed(speed);
  servo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    uint32_t IRcode = IrReceiver.decodedIRData.command;
    Serial.print("IR Code: ");
    Serial.println(IRcode);

    if (IRcode == 10) {
      servo.write(180);
      delay(500);
    } else if (IRcode == 11) {
      servo.write(0);
      delay(500);
    } 
    delay(1000);
    IrReceiver.resume();
  }
  else {
    Serial.println("No Input");
  }

}

