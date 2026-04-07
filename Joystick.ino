// ==========================================
// Beroepsproject: The Navigator - EBSY
// Student: Alireza Oftadeh (92143)
// ==========================================

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

ArduinoLEDMatrix matrix;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int pinJoyKnop = A0; 
const int pinJoyY    = A1; 
const int pinJoyX    = A2; 

bool startFase = true; 

void setup() {
  Serial.begin(9600); 
  matrix.begin();

  lcd.init(); 
  lcd.backlight(); 
  
  lcd.setCursor(0, 0);
  lcd.print("92143 Alireza");
  lcd.setCursor(0, 1);
  lcd.print("Oftadeh - BP03");

  pinMode(pinJoyKnop, INPUT_PULLUP);
}

void loop() {
  if (startFase == true) {
    toonNaamOpMatrix(); 
    
    // Controleer de joystick knop (zonder vertraging!)
    if (digitalRead(pinJoyKnop) == LOW) {
      startFase = false; 
      matrix.clear();    
      lcd.clear();       
      delay(300); // Korte pauze om te voorkomen dat je de klik vasthoudt
    }
  } 
  else {
    leesEnToonJoystick(); 
  }
}

void toonNaamOpMatrix() {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(60); 
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  
  matrix.println(" 92143 Alireza Oftadeh - BP03 "); 
  
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw(); 
}

void leesEnToonJoystick() {
  int waardeX = analogRead(pinJoyX);
  int waardeY = analogRead(pinJoyY);

  String richting = "Midden"; 
  int percentage = 0;

  // We bepalen eerst hoe ver elke as uit het absolute midden (512) is.
  // We gebruiken abs() zodat het altijd een positief getal is.
  int uitslagX = abs(waardeX - 512);
  int uitslagY = abs(waardeY - 512);

  // We negeren kleine bewegingen (deadzone). Alles onder uitslag 80 is 'Midden'.
  if (uitslagX < 80 && uitslagY < 80) {
    richting = "Midden";
    percentage = 0;
  } 
  else {
    // Welke as is het verst geduwd?
    if (uitslagY > uitslagX) {
      // Y-as wint (Up of Down)
      if (waardeY < 400) { // Duw je naar boven?
        richting = "Up";
        // Map de waarde (van rand deadzone 400, naar theoretisch uiterste 0)
        percentage = map(waardeY, 400, 0, 0, 100); 
      } 
      else if (waardeY > 600) { // Duw je naar beneden?
        richting = "Down";
        percentage = map(waardeY, 600, 1023, 0, 100);
      }
    } 
    else {
      // X-as wint (Left of Right)
      if (waardeX < 400) { // Duw je naar links?
        richting = "Left";
        percentage = map(waardeX, 400, 0, 0, 100);
      } 
      else if (waardeX > 600) { // Duw je naar rechts?
        richting = "Right";
        percentage = map(waardeX, 600, 1023, 0, 100);
      }
    }
  }

  // Beveiliging: percentage mag nooit negatief of boven 100 zijn.
  if (percentage < 0) percentage = 0;
  if (percentage > 100) percentage = 100;

  // --- Printen naar Serial Monitor ---
  if (richting == "Midden") {
    Serial.println("Midden");
  } else {
    Serial.print(richting);
    Serial.print(" ");
    Serial.print(percentage);
    Serial.println("%");
  }

  // --- Printen naar LCD Monitor ---
  lcd.clear();
  lcd.setCursor(0, 0);
  
  if (richting == "Midden") {
    lcd.print("Midden");
  } else {
    lcd.print(richting);
    lcd.print(" ");
    lcd.print(percentage);
    lcd.print("%");
  }

  delay(150); // Iets snellere update voor een soepeler gevoel
}