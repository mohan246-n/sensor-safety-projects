/*
  Temperature and Humidity Monitor
  ---------------------------------
  DHT11 sensor measures temperature and humidity, shown on a
  16x2 I2C LCD and the Serial Monitor. If the temperature
  rises above the limit, the buzzer sounds and the LED lights
  as an over-temperature alarm. Buzzer and LED are OFF on
  startup (safe default).

  Requires the "DHT sensor library" by Adafruit (and its
  "Adafruit Unified Sensor" dependency): install both from
  the Arduino IDE Library Manager before uploading.

  Wiring:
    DHT11 DATA : D2
    DHT11 VCC  : 5V, DHT11 GND: GND
    Buzzer     : D8 (active buzzer, + to D8, - to GND)
    Alarm LED  : D13 (through a 220 ohm resistor to GND)
    LCD I2C    : SDA A4, SCL A5 (Uno)
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ---- Pin definitions ----
#define DHT_PIN   2     // DHT11 data pin
#define DHT_TYPE  DHT11 // Change to DHT22 if you use that sensor

const int BUZZER_PIN = 8;   // Buzzer
const int ALARM_LED  = 13;  // Alarm LED

// ---- Thresholds (tune to your room / equipment). ----
// Alarm ON above ALARM_TEMP_C, OFF below CLEAR_TEMP_C.
const float ALARM_TEMP_C = 40.0;
const float CLEAR_TEMP_C = 38.0;

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x3F if needed

bool alarmOn = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);

  // Safe defaults: buzzer and LED OFF on startup.
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(ALARM_LED, LOW);

  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.print("Temp/Humidity");
  delay(1000);
  lcd.clear();
  Serial.println("Temperature and Humidity Monitor ready.");
}

void loop() {
  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature();  // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT read failed - check wiring.");
    lcd.setCursor(0, 0);
    lcd.print("Sensor error    ");
    delay(2000);
    return;
  }

  // Over-temperature alarm with hysteresis.
  if (!alarmOn && temperature > ALARM_TEMP_C) {
    alarmOn = true;
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ALARM_LED, HIGH);
    Serial.println("WARNING: Over-temperature!");
  } else if (alarmOn && temperature < CLEAR_TEMP_C) {
    alarmOn = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    Serial.println("Temperature normal - alarm off.");
  }

  // LCD output.
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%  ");
  lcd.setCursor(0, 1);
  lcd.print(alarmOn ? "OVER-TEMP ALARM " : "Normal          ");

  // Serial output.
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity, 0);
  Serial.print(" % | ");
  Serial.println(alarmOn ? "ALARM" : "Normal");

  delay(2000);  // DHT11 needs about 2 s between readings
}
