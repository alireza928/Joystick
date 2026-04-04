// Joystick pins
const int JoyX = A0;
const int JoyY = A1;

// Button pin
const int buttonPin = 2;

// LED pin
const int ledPin = 13;

// Variables
int joyXValue = 0;
int joyYValue = 0;

bool buttonPressed = false;
bool cheatMode = false;

void setup() 
{
  Serial.begin(9600); // Start serial communication

  pinMode(buttonPin, INPUT_PULLUP); // Button
  pinMode(ledPin, OUTPUT);          // LED
}

void loop() 
{
  // Read joystick
  joyXValue = analogRead(JoyX);
  joyYValue = analogRead(JoyY);

  // Read button (LOW = pressed)
  buttonPressed = (digitalRead(buttonPin) == LOW);

  // Check if joystick is centered
  bool joystickCentered = (joyXValue > 400 && joyXValue < 600 &&
                           joyYValue > 400 && joyYValue < 600);

  // Cheat mode = button + joystick center
  cheatMode = buttonPressed && joystickCentered;

  // LED ON when shooting or cheat mode
  if (buttonPressed || cheatMode)
    digitalWrite(ledPin, HIGH);
  else
    digitalWrite(ledPin, LOW);

  // Send data to C#
  Serial.print(joyXValue);
  Serial.print(",");
  Serial.print(joyYValue);
  Serial.print(",");
  Serial.print(buttonPressed);
  Serial.print(",");
  Serial.println(cheatMode);

  delay(100);
}