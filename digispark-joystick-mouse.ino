#include <DigiMouse.h>

#define pinX   A0
#define pinY   A1
#define pinBtn  0

void setup() {
  pinMode(pinBtn, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  DigiMouse.begin();
}
 
void loop() {
  int X = analogRead(pinX); // 0–1023
  int Y = analogRead(pinY);

  // Center joystick around 512, scale movement
  int moveX = map(X, 0, 1023, 12, -12);
  int moveY = map(Y, 0, 1023, -12, 12);

  // Deadzone (avoid drift)
  if (abs(moveX) < 2) moveX = 0;
  if (abs(moveY) < 2) moveY = 0;

  // Move mouse
  DigiMouse.move(moveX, moveY, 0);

  // Button click
  if (digitalRead(pinBtn) == LOW) {  // active LOW
    DigiMouse.setButtons(1 << 0); // left click
  } else {
    DigiMouse.setButtons(0); // release
  }
  DigiMouse.delay(20);
}