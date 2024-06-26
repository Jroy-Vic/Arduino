/*
  Capacitive-Touch Arduino Keyboard Piano
  
  Plays piano tones through a buzzer when the user taps touch-sensitive piano "keys"
  
  Created  18 May 2013
  Modified 23 May 2013
  by Tyler Crumpton and Nicholas Jones
  
  This code is released to the public domain. For information about the circuit,
  visit the Instructable tutorial at http://www.instructables.com/id/Capacitive-Touch-Arduino-Keyboard-Piano/
*/

#include <CapacitiveSensor.h>
#include "pitches.h"

#define COMMON_PIN      2    // The common 'send' pin for all keys
#define BUZZER_PIN      A4   // The output pin for the piezo buzzer
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   150  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     4    // Number of keys that are on the keyboard
#define LED_PIN         8    // Green LED
#define LOCK_PIN        9    // Red LED
#define pulse_ip        A0   // Pulse Read
#define failSafepin     13

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(2, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={NOTE_C4,NOTE_D4,NOTE_E4,NOTE_F4,NOTE_G4,NOTE_A4,NOTE_B4,NOTE_C5}; // C-Major scale
//int notes[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5}; // A-Minor scale
//int notes[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5}; // C Blues scale

char zelda_notes[] = "gabygabyxzCDxzCDabywabywzCDEzCDEbywFCDEqywFGDEqi        azbC"; // a space represents a rest
int length = sizeof(zelda_notes); // the number of notes
int beats[] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 2,3,3,16,};
int tempo = 75;


// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3), CS(4), CS(5), CS(6)};
int PASSCODE[5] = {0, 1, 2, 3, 0};
int keyList[5];
unsigned long startTime;

// Metal Detector Section
int ontime, offtime, duty;
float freq, period;

void setup() { 
  // Turn off autocalibrate on all channels:
  for(int i=0; i<4; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  // Set the buzzer as an output:
  pinMode(BUZZER_PIN, OUTPUT); 
  // Set LED_Pin
  pinMode(LED_PIN, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LOCK_PIN, LOW);

  pinMode(failSafepin, OUTPUT);
  digitalWrite(failSafepin, LOW);
}

void loop() {    


  digitalWrite(LOCK_PIN, LOW);
  startTime = millis();
  for (int x = 0; x < 5; x++) {
    keyList[x] = 0;
  }
  int current = 0;

  while( (millis() - startTime) < 5000) {

    if (current > 0 && current < 5) {
      digitalWrite(LOCK_PIN, HIGH);
    }
    else {
      digitalWrite(LOCK_PIN, LOW);
    }

    // Loop through each key:
    for (int i = 0; i < 4; ++i) {
      // If the capacitance reading is greater than the threshold, play a note:
      if(keys[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
        Serial.println(current);
        keyList[current] = i;
        current += 1;
        tone(BUZZER_PIN, notes[i], 250); // Plays the note corresponding to the key pressed
        delay(200);  
      }
    }

    if (current == 5) {
      bool MATCH = true;

      for (int x = 0; x < 5; x++) {
        if (PASSCODE[x] != keyList[x]) {
          MATCH = false;
          break;
        }
      } 

      if (MATCH) {
        delay(1000);
        for (int i = 0; i < length; i++) {
          if (zelda_notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
          } else {
          playNote(zelda_notes[i], beats[i] * tempo);
        }
    
        //pause between notes
        delay(tempo / 2); 
        }

        delay(1000);
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(failSafepin, HIGH);
        digitalWrite(LOCK_PIN, LOW);
        delay(10000);
        digitalWrite(LED_PIN, LOW);
      }

      int keyList[5];
      int current = 0;
    }
  }
  
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'x', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  // c=C4, C = C5. These values have been tuned.
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };
   
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}