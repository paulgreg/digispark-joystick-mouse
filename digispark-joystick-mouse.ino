#include <DigiMouse.h>

#define PIN_X    A0
#define PIN_Y    A1
#define PIN_BTN  0

#define INVERT_X false
#define INVERT_Y false

// Adjust after calibration if necessary
const int CENTER_X = 512;
const int CENTER_Y = 512;

// Dead zone around the center
const int DEADZONE = 50;

// Maximum cursor speed
const float MAX_SPEED = 8.0;

// Cursor accumulators (fractional pixels)
float accX = 0.0;
float accY = 0.0;

void setup() {
  pinMode(PIN_BTN, INPUT_PULLUP);
  DigiMouse.begin();
  DigiMouse.delay(2000);
}

void loop() {
  DigiMouse.update();

  int rawX = analogRead(PIN_X);
  int rawY = analogRead(PIN_Y);

  int dx = rawX - CENTER_X;
  int dy = rawY - CENTER_Y;

  float speedX = 0.0;
  float speedY = 0.0;

  // ----- X axis -----
  if (abs(dx) > DEADZONE) {
    float amount = (float)(abs(dx) - DEADZONE) / (512.0 - DEADZONE);
    speedX = amount * amount * MAX_SPEED;   // quadratic response

    if ((dx > 0) ^ INVERT_X)
      speedX = -speedX;
  }

  // ----- Y axis -----
  if (abs(dy) > DEADZONE) {
    float amount = (float)(abs(dy) - DEADZONE) / (512.0 - DEADZONE);
    speedY = amount * amount * MAX_SPEED;

    if ((dy < 0) ^ INVERT_Y)
      speedY = -speedY;
  }

  // Accumulate fractional movement
  accX += speedX;
  accY += speedY;

  int moveX = (int)accX;
  int moveY = (int)accY;

  accX -= moveX;
  accY -= moveY;

  DigiMouse.move(moveX, moveY, 0);

  // Left button
  if (digitalRead(PIN_BTN) == LOW)
    DigiMouse.setButtons(1);
  else
    DigiMouse.setButtons(0);

  DigiMouse.delay(15);
}
