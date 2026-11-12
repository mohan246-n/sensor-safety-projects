/*
  Gas Leak Detector
  -----------------
  MQ-5 sensor watches for LPG / natural gas leaks. Above the
  threshold the buzzer sounds, the LED flashes, and an
  optional exhaust fan relay turns on to clear the gas.
  Everything is OFF on startup (safe default).
  Note: the MQ-5 needs 1-2 minutes to warm up after power-on.
  This is a warning device, not a certified gas alarm.

  Wiring:
    MQ-5 A0 : A0
    MQ-5 VCC: 5V, MQ-5 GND: GND
    Buzzer  : D8 (active buzzer, + to D8, - to GND)
    Alarm LED: D13 (through a 220 ohm resistor to GND)
    Fan relay: D7 (active LOW, optional exhaust fan)
*/

// ---- Pin definitions ----
const int MQ5_PIN    = A0;  // MQ-5 analog output
const int FAN_RELAY  = 7;   // Exhaust fan relay (active LOW)
const int BUZZER_PIN = 8;   // Buzzer
const int ALARM_LED  = 13;  // Alarm LED

// ---- Thresholds (0-1023). Tune from clean-air baseline. ----
// Alarm ON above ALARM_THRESHOLD, OFF below CLEAR_THRESHOLD.
const int ALARM_THRESHOLD = 400;
const int CLEAR_THRESHOLD = 350;

bool alarmOn = false;

void setup() {
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);

  // Safe defaults: fan OFF, buzzer and LED OFF on startup.
  digitalWrite(FAN_RELAY, HIGH);  // HIGH = relay OFF (active LOW)
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(ALARM_LED, LOW);

  Serial.begin(9600);
  Serial.println("Gas leak detector warming up - please wait 1-2 minutes...");
}

void loop() {
  int gasLevel = analogRead(MQ5_PIN);
  Serial.print("Gas level: ");
  Serial.println(gasLevel);

  if (!alarmOn && gasLevel > ALARM_THRESHOLD) {
    alarmOn = true;
    digitalWrite(FAN_RELAY, LOW);  // LOW = relay ON (fan runs)
    Serial.println("WARNING: Gas leak detected! Fan ON.");
  } else if (alarmOn && gasLevel < CLEAR_THRESHOLD) {
    alarmOn = false;
    digitalWrite(FAN_RELAY, HIGH);  // Fan OFF once air clears
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    Serial.println("Air clear - alarm off, fan off.");
  }

  if (alarmOn) {
    // Sound the buzzer and flash the LED.
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ALARM_LED, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    delay(300);
  } else {
    delay(500);
  }
}
