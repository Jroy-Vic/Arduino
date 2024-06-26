#include <FreqMeasure.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int electro = 53;   // Electromagnet Pin
const int wPin = A5;      // Water Detector Pin
const int failSafepin = 7;
const int speedPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(electro, OUTPUT);    
  FreqMeasure.begin();
  digitalWrite(electro, LOW);  

  lcd.begin(16,2);
  pinMode(wPin, INPUT);

  myservo.attach(50);     // Servo Pin
  myservo.write(0);

  malloc()
  pinMode(failSafepin, INPUT);
  pinMode(speedPin, OUTPUT);
  analogWrite(speedPin, 0);
}

double sum=0;
int count=0;
int startTime;
int read;
int start = 0;

void loop() {
  myservo.write(0);               // Reset all external hardware
  digitalWrite(electro, LOW);
  analogWrite(speedPin, 0);

  lcd.setCursor(0,0);
  lcd.print("Water Detector");
  lcd.setCursor(0,1);
  lcd.print("Disabled");
  read = digitalRead(failSafepin);
  Serial.print("Pin Read: ");
  Serial.println(read);
  delay(250);
  start = 0;

  while(read == 1) {
    delay(3000);

    startTime = millis();

    while( (millis() - startTime) < 3500) {
      if (FreqMeasure.available()) {
        // average several reading together
        sum = sum + FreqMeasure.read();
        count = count + 1;
        if (count > 30) {
          int frequency = FreqMeasure.countToFrequency(sum / count);
          Serial.print("Freqency: ");
          Serial.println(frequency);
          sum = 0;
          count = 0;

          int cnt = 0;

          while ((frequency == 135) && read == 1) {
            read = digitalRead(failSafepin);
            digitalWrite(electro, HIGH);
            if (cnt == 0) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Activating...");
              delay(3000);
              cnt = 1;
            }
            waterdet();
          }
        }
      }
    }

    int cnt = 0;

    while (read == 1) {
      read = digitalRead(failSafepin);
      digitalWrite(electro, HIGH);
      if (cnt == 0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Activating...");
        delay(3000);
        cnt = 1;
      }
      waterdet();
    }
  }
}

int wSig;

void waterdet() {
  wSig = analogRead(wPin);
  read = digitalRead(failSafepin);
  lcd.setCursor(0,0);
  lcd.print("Water Level: ");
  lcd.setCursor(13,0);
  lcd.print(wSig);
  Serial.println(wSig);
  delay(500);
  lcd.clear();

  while ((wSig >= 10) && read == 1) {
    read = digitalRead(failSafepin);
    lcd.setCursor(0,0);
    lcd.print("Clean up on");
    lcd.setCursor(0,1);
    lcd.print("Aisle 9!");
    analogWrite(speedPin, 255);
  }

  lcd.clear();

  if (start >= 0 && start < 5) {
    myservo.write(0);
    Serial.print("Servo Inc: ");
    Serial.println(start);
    start++;
  }
  else if (start >= 5 && start < 10) {
    myservo.write(90);
    Serial.print("Servo Inc: ");
    Serial.println(start);
    start++;
  }
  else if (start == 10) {
    myservo.write(180);
    Serial.print("Servo Inc: ");
    Serial.println(start);
  }
}