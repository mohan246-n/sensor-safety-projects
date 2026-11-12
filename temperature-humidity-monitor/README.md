# Temperature Humidity Monitor

A DHT11 sensor measures room temperature and humidity and
shows both on a 16×2 LCD and the Serial Monitor. If the
temperature climbs above a set limit, a buzzer and LED warn
you — useful for a server / equipment corner, a greenhouse,
or a baby's room.

## How it works

The DHT11 is a digital sensor: the Arduino asks it for a
reading about every 2 seconds (the DHT11 cannot be read
much faster) and gets temperature in °C and relative
humidity in %. The values are printed to the Serial Monitor
and shown on the I2C LCD. If the temperature rises above
the alarm limit the buzzer sounds and the alarm LED lights;
the alarm clears only when the temperature falls below a
slightly lower clear limit, so it does not toggle on and
off at one temperature (hysteresis). Failed sensor reads
are reported on the Serial Monitor / LCD instead of showing
nonsense values. This project uses the DHT library so the
humidity reading is real — an analog temperature sensor
alone (like an LM35) cannot measure humidity.

**Library needed:** install "DHT sensor library" by
Adafruit, plus "Adafruit Unified Sensor", from the Arduino
IDE Library Manager before uploading.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| DHT11 sensor module | Temperature + humidity (DHT22 also works) | 1 |
| LCD | 16×2 with I2C backpack | 1 |
| Buzzer | 5 V active buzzer | 1 |
| LED | 5 mm red | 1 |
| Resistor | 220 Ω (LED); 10 kΩ pull-up if using a bare DHT11 | 1–2 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
DHT11 module VCC ── Arduino 5V
DHT11 module GND ── Arduino GND
DHT11 module DATA ── Arduino D2
(Bare DHT11 sensor: DATA needs a 10k pull-up to 5V.)

Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── Red LED ── GND
Arduino SDA/SCL ── LCD I2C (SDA A4, SCL A5 on Uno)
```

The buzzer and LED are OFF on startup.

## Wiring steps

1. Connect the DHT11 module: VCC → 5 V, GND → GND,
   DATA → D2. A *module* has the pull-up resistor built
   in; a bare 4-pin sensor needs 10 kΩ from DATA to 5 V.
2. Connect the LCD I2C lines (SDA → A4, SCL → A5,
   VCC → 5 V, GND → GND).
3. Connect the buzzer: + → D8, − → GND.
4. Connect the red LED: D13 → 220 Ω → LED anode,
   LED cathode → GND.
5. Install the DHT libraries (see above), then upload
   `temperature-humidity-monitor.ino`.
6. Open the Serial Monitor (9600 baud) — readings should
   appear every 2 seconds and match the LCD.
7. Test the alarm by warming the sensor gently with your
   hand or a hair dryer held well away — never a flame.

## Calibration

Compare the readings with a known thermometer / hygrometer
in the same spot. The DHT11 is accurate to about ±2 °C and
±5 % humidity, so treat this as a guide, not a precision
instrument; a DHT22 is more accurate if you need better.
Set `ALARM_TEMP_C` (default 40 °C) to the limit for what
you are watching and `CLEAR_TEMP_C` (default 38 °C) a
couple of degrees below it. Keep the sensor out of direct
sunlight and away from heaters, or it will report the
heater, not the room.

## Safety notes

- This is a monitoring / warning device, not a safety
  control. Do not use it as the only protection against
  overheating for people, animals or expensive equipment.
- Low voltage only — this project uses 5 V throughout and
  has no mains wiring.
- If the over-temperature alarm sounds, check the cause.
  Do not just silence it and leave equipment running hot.
- Keep the sensor and LCD dry; humidity sensors drift and
  fail early if they get wet.
