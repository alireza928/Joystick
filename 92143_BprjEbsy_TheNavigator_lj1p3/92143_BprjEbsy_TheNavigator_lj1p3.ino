/* * PROJECT: The Navigator - Professional Project EBSY
 * STUDENT: Alireza Oftadeh (92143)
 * DATE: April 7, 2026
 * DESCRIPTION: This program starts with a name animation on the LED Matrix. 
 * After clicking the joystick, the LCD screen shows the real-time direction 
 * and the movement percentage (0-100%).
 */

#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Hardware Objects ---
ArduinoLEDMatrix matrix;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- Pin Configuration ---
const int pinJoyButton = A0; // SW pin
const int pinJoyY      = A1; // VRy pin
const int pinJoyX      = A2; // VRx pin

// --- Variables ---
bool startPhase = true; 
int lastButtonStatus = HIGH;

void setup() {
  Serial.begin(9600); // Start Serial Monitor for feedback
  matrix.begin();     // Start the R4 LED Matrix

  lcd.init();         // Initialize LCD
  lcd.backlight(); 
  
  // Show startup data on LCD according to assignment
  lcd.setCursor(0, 0);
  lcd.print("92143 Alireza");
  lcd.setCursor(0, 1);
  lcd.print("Oftadeh - BP03");

  pinMode(pinJoyButton, INPUT_PULLUP);
}

void loop() {
  int currentButtonStatus = digitalRead(pinJoyButton);

  if (startPhase) {
    displayTitleOnMatrix(); 
    
    // Detect click to transition to Phase 2
    if (currentButtonStatus == LOW && lastButtonStatus == HIGH) {
      startPhase = false; 
      matrix.clear();    
      lcd.clear();       
      delay(200); 
    }
  } 
  else {
    readAndDisplayJoystick(); 
  }
  
  lastButtonStatus = currentButtonStatus;
}

// --- Custom Function for LED Matrix ---
void displayTitleOnMatrix() {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(60); 
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  
  // Requirements: Last 3 digits student ID + Name - BP03
  matrix.println(" 143 Alireza Oftadeh - BP03 "); 
  
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw(); 
}

// --- Custom Function for Joystick & LCD ---
void readAndDisplayJoystick() {
  int x = analogRead(pinJoyX);
  int y = analogRead(pinJoyY);
  
  String direction = "Center"; 
  int percentage = 0;

  // Calculation with Deadzone for stability
  // Determine which axis is moved the most
  int deviationX = abs(x - 512);
  int deviationY = abs(y - 512);

  if (deviationX < 70 && deviationY < 70) {
    direction = "Center";
    percentage = 0;
  } 
  else if (deviationY > deviationX) {
    if (y < 512) {
      direction = "Up";
      percentage = map(y, 450, 0, 0, 100);
    } else {
      direction = "Down";
      percentage = map(y, 570, 1023, 0, 100);
    }
  } 
  else {
    if (x < 512) {
      direction = "Left";
      percentage = map(x, 450, 0, 0, 100);
    } else {
      direction = "Right";
      percentage = map(x, 570, 1023, 0, 100);
    }
  }

  // Constrain values between 0 and 100
  if (percentage > 100) percentage = 100;
  if (percentage < 0) percentage = 0;

  // --- Output to LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Status: ");
  lcd.print(direction);
  lcd.print("     "); // Spaces to clear old text
  
  lcd.setCursor(0, 1);
  if (direction != "Center") {
    lcd.print("Power:  ");
    lcd.print(percentage);
    lcd.print("%    ");
  } else {
    lcd.print("Idle            ");
  }

  // --- Output to Serial Monitor ---
  Serial.print("Direction: ");
  Serial.print(direction);
  Serial.print(" | ");
  Serial.print(percentage);
  Serial.println("%");

  delay(150); 
}