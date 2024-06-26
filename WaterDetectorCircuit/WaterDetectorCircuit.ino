#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int wPin = A5;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(wPin, INPUT);
}

int wSig;

void loop() {
  wSig = analogRead(wPin);
  lcd.setCursor(0,0);
  lcd.print("Water Level: ");
  lcd.setCursor(13,0);
  lcd.print(wSig);
  Serial.println(wSig);
  delay(500);
  lcd.clear();

  while (wSig >= 100) {
    lcd.setCursor(0,0);
    lcd.print("Clean up on");
    lcd.setCursor(0,1);
    lcd.print("Aisle 9!");
    wSig = analogRead(wPin);
  }

  lcd.clear();
}
