/*
  Rain Detector Alarm
  --------------------
  Rain sensor plate gets wet: its analog reading falls as
  water bridges the tracks. Below the rain threshold the
  buzzer sounds, the LED lights, and an optional servo swings
  to close a small window / cover. Everything is OFF, and
  the servo rests open, on startup (safe default).

  Wiring:
    Rain module A0 : A0 (analog rain level)
    Rain module VCC: 5V, Rain module GND: GND
    Buzzer         : D8 (active buzzer, + to D8, - to GND)
    Alarm LED      : D13 (through a 220 ohm resistor to GND)
    Servo signal   : D9 (optional, window closer)
*/

#include <Servo.h>

// ---- Pin definitions ----
const int RAIN_PIN   = A0;  // Rain sensor analog output
const int BUZZER_PIN = 8;   // Buzzer
const int SERVO_PIN  = 9;   // Optional window-closer servo
const int ALARM_LED  = 13;  // Alarm LED

// ---- Thresholds (0-1023). Tune from dry / wet readings. ----
// Analog output FALLS when wet. Rain ON below RAIN_THRESHOLD,
// rain OFF (dry again) above DRY_THRESHOLD.
const int RAIN_THRESHOLD = 600;
const int DRY_THRESHOLD  = 700;

// Servo positions (degrees): window open vs. closed.
const int WINDOW_OPEN_ANGLE   = 0;
const int WINDOW_CLOSED_ANGLE = 90;

Servo windowServo;
bool raining = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);

  // Safe defaults: buzzer and LED OFF, window open on startup.
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(ALARM_LED, LOW);
  windowServo.attach(SERVO_PIN);
  windowServo.write(WINDOW_OPEN_ANGLE);

  Serial.begin(9600);
  Serial.println("Rain Detector Alarm ready.");
}

void loop() {
  int rainLevel = analogRead(RAIN_PIN);
  Serial.print("Rain level: ");
  Serial.println(rainLevel);

  if (!raining && rainLevel < RAIN_THRESHOLD) {
    raining = true;
    windowServo.write(WINDOW_CLOSED_ANGLE);  // Close the window
    Serial.println("WARNING: Rain detected! Closing window.");
  } else if (raining && rainLevel > DRY_THRESHOLD) {
    raining = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    windowServo.write(WINDOW_OPEN_ANGLE);
    Serial.println("Rain stopped and plate dry - window open.");
  }

  if (raining) {
    // Sound the buzzer and flash the LED while it rains.
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ALARM_LED, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    delay(700);
  } else {
    delay(500);
  }
}

/*
  Note: rain sensor plates corrode if left powered and wet
  outdoors for months. For a permanent build, power the
  sensor module only while measuring (e.g. from a digital
  pin or a transistor) and clean / dry the plate regularly.
  The servo is optional - the buzzer and LED alarm work
  without it.
*/
