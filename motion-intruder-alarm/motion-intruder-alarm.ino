/*
  Motion Intruder Alarm
  ----------------------
  PIR sensor watches a room / doorway. When the alarm is
  armed and motion is seen, a short entry delay gives you
  time to disarm it; if nobody does, the buzzer sounds and
  the LED flashes until disarmed. A single push button
  arms / disarms it. Alarm is DISARMED and silent on startup
  (safe default).

  Wiring:
    PIR OUT : D2
    PIR VCC : 5V, PIR GND: GND
    Button  : D3 to GND (uses INPUT_PULLUP)
    Buzzer  : D8 (active buzzer, + to D8, - to GND)
    Alarm LED: D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int PIR_PIN    = 2;   // PIR motion sensor output
const int BUTTON_PIN = 3;   // Arm / disarm push button
const int BUZZER_PIN = 8;   // Buzzer
const int ALARM_LED  = 13;  // Alarm / armed LED

// ---- Timing (milliseconds). Tune to your doorway. ----
const unsigned long ENTRY_DELAY_MS = 10000;  // Time to disarm after motion
const unsigned long EXIT_DELAY_MS  = 10000;  // Time to leave after arming
const unsigned long DEBOUNCE_MS    = 50;

enum State { DISARMED, ARMING, ARMED, ENTRY, ALARMING };
State state = DISARMED;

unsigned long stateStartedAt = 0;
bool lastButtonReading = HIGH;

void setOutputs(bool buzzerOn, bool ledOn) {
  digitalWrite(BUZZER_PIN, buzzerOn ? HIGH : LOW);
  digitalWrite(ALARM_LED, ledOn ? HIGH : LOW);
}

void changeState(State next) {
  state = next;
  stateStartedAt = millis();
  setOutputs(false, next == ARMED || next == ARMING);
  if (next == ARMED)    Serial.println("Alarm ARMED.");
  if (next == DISARMED) Serial.println("Alarm DISARMED.");
  if (next == ALARMING) Serial.println("INTRUDER! Alarm sounding!");
}

bool buttonPressed() {
  bool reading = digitalRead(BUTTON_PIN);
  bool pressed = (lastButtonReading == HIGH && reading == LOW);
  lastButtonReading = reading;
  if (pressed) delay(DEBOUNCE_MS);
  return pressed;
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);

  // Safe default: disarmed, buzzer and LED OFF on startup.
  setOutputs(false, false);

  Serial.begin(9600);
  Serial.println("Motion Intruder Alarm ready - DISARMED.");
  Serial.println("Press the button to arm. PIR warms up in ~30 s.");
  changeState(DISARMED);
}

void loop() {
  unsigned long now = millis();

  // The button toggles arming from any quiet state, and
  // silences / disarms the alarm from any active state.
  if (buttonPressed()) {
    if (state == DISARMED) {
      changeState(ARMING);
      Serial.println("Arming - you have the exit delay to leave.");
    } else {
      changeState(DISARMED);
    }
    return;
  }

  switch (state) {
    case ARMING:
      if (now - stateStartedAt >= EXIT_DELAY_MS) changeState(ARMED);
      break;

    case ARMED:
      if (digitalRead(PIR_PIN) == HIGH) {
        changeState(ENTRY);
        Serial.println("Motion detected - entry delay started.");
      }
      break;

    case ENTRY:
      // LED flashes as a "disarm me now" warning, no buzzer yet.
      digitalWrite(ALARM_LED, (now / 250) % 2 == 0 ? HIGH : LOW);
      if (now - stateStartedAt >= ENTRY_DELAY_MS) changeState(ALARMING);
      break;

    case ALARMING:
      // Flash the LED and pulse the buzzer until disarmed.
      bool on = (now / 300) % 2 == 0;
      setOutputs(on, on);
      break;

    case DISARMED:
    default:
      break;
  }
}
