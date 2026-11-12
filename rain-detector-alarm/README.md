# Rain Detector Alarm

A rain sensor plate detects the first drops of rain; a
buzzer and LED warn you to bring the washing in or close
the windows — and an optional servo closes a small window
or cover for you.

## How it works

The rain sensor is an exposed plate of interlaced tracks.
Dry, almost no current flows between them; rain drops
bridge the tracks and the module's analog output *falls*.
The Arduino reads that level continuously: below the rain
threshold it sounds the buzzer, flashes the LED, and (if
fitted) swings the servo to the "window closed" position.
Rain has only cleared when the plate has dried enough for
the reading to rise above a higher dry threshold — that
gap (hysteresis) stops the alarm chattering as the plate
slowly dries. The module also has a digital output and a
sensitivity pot, but this project uses the analog output in
code, so the thresholds live in one place and can be tuned
from the Serial Monitor readings.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| Rain sensor module | Plate + control board, analog + digital output | 1 |
| Buzzer | 5 V active buzzer | 1 |
| LED | 5 mm red | 1 |
| Resistor | 220 Ω (LED) | 1 |
| Servo motor | SG90 (optional, for a light window / cover model) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
Rain module VCC ── Arduino 5V
Rain module GND ── Arduino GND
Rain module A0 ─── Arduino A0 (analog rain level)
Rain module D0 ─── (not used)
Rain plate ──────── connected to its control board

Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── Red LED ── GND
Arduino D9 ── Servo signal (optional)
Servo + ── 5V, Servo - ── GND
```

The buzzer and LED are OFF, and the servo rests in the
window-open position, on startup.

## Wiring steps

1. Connect the rain plate to its control board with the
   two supplied wires (polarity does not matter).
2. Connect the control board: VCC → 5 V, GND → GND,
   A0 → A0.
3. Connect the buzzer: + → D8, − → GND.
4. Connect the red LED: D13 → 220 Ω → LED anode, LED cathode → GND.
5. Optional servo: signal → D9, + → 5 V, − → GND. Link
   its horn to a light model window / cover before giving
   it a real one (see safety notes).
6. Upload `rain-detector-alarm.ino` and open the Serial
   Monitor (9600 baud). Note the dry reading.
7. Test with a few drops of water from a fingertip or a
   spray bottle on the plate — the buzzer should sound
   and the servo swing. Wipe the plate dry to reset.

## Calibration

Readings run from about 1023 (completely dry) down to a
few hundred (soaked), depending on the module. Note your
own dry reading and your "first drops" reading from the
Serial Monitor and set `RAIN_THRESHOLD` (default 600)
between them, with `DRY_THRESHOLD` (default 700) above it.
Mount the plate at a slight angle so water runs off and it
dries reasonably quickly, and where sprinklers or dripping
gutters will not soak it on a dry day. Clean dust and
leaves off the plate now and then.

## Safety notes

- Low voltage only — this project uses 5 V throughout and
  has no mains wiring. Keep the Arduino, LCD wiring and
  power supply indoors / dry; only the sensor plate belongs
  outside in the weather.
- Rain plates corrode over months outdoors. For a permanent
  build, power the module only while measuring and expect
  to clean or replace the plate seasonally.
- A small SG90 servo can close a light model window or
  flap only. A real window needs a proper actuator, end
  switches and a manual override — and must never trap
  fingers or block a fire escape route.
- This is a convenience alarm, not a flood / weather
  safety system. Do not rely on it to protect anything
  valuable from water damage.
