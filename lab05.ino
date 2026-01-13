#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int lightPin = A0;
const int buttonPin = 2;     
const int buzzerPin = 8;

volatile bool buzzerFlag = false;

void initInterrupt() {

  EICRA &= ~(1 << ISC00);   
  EICRA |=  (1 << ISC01);   

  EIFR  |=  (1 << INTF0);   
  EIMSK |=  (1 << INT0);    
}


ISR(INT0_vect) {
  buzzerFlag = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(lightPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);

  lcd.setCursor(0, 0);
  lcd.print("CMPE453-Section2");
  delay(2000);
  lcd.clear();

  
  initInterrupt();
}

void loop() {
  if (buzzerFlag) {
    Serial.println("ISR Calisti!");
    digitalWrite(buzzerPin, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Buzzer Active");

    delay(2000);
    digitalWrite(buzzerPin, LOW);
    buzzerFlag = false;
    lcd.clear();
  }

  int lightValue = analogRead(lightPin);

  lcd.setCursor(0, 0);
  lcd.print("Light Value:   ");

  lcd.setCursor(0, 1);
  lcd.print(lightValue);
  lcd.print("     ");

  delay(200);
}