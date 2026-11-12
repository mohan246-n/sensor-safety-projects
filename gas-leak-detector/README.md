# Gas Leak Detector

An MQ-5 gas sensor watches for LPG / natural gas leaks;
when the gas level rises above a set threshold, a buzzer
sounds, an LED flashes, and an exhaust fan switches on to
clear the gas until the air is safe again.

## How it works

The MQ-5 sensor's analog output rises with the concentration
of LPG, natural gas and similar combustible gases. The
Arduino reads it continuously and compares it with a
threshold. Above the threshold it turns on the buzzer,
flashes the alarm LED, and switches the exhaust fan relay
on, and prints a warning on the Serial Monitor. Below the
threshold (with a lower switch-off level, so the alarm does
not flicker on and off) the buzzer and fan stop. The sensor
needs about 1–2 minutes of warm-up after power-on before its
readings are stable. Mount the sensor near the likely leak
source — LPG is heavier than air, so for LPG mount it low,
near floor level; natural gas rises, so mount it high.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| MQ-5 gas sensor module | with analog + digital output | 1 |
| Buzzer | 5 V active buzzer | 1 |
| LED | 5 mm red | 1 |
| Resistor | 220 Ω (LED) | 1 |
| Relay module | 5 V, 1-channel (optional, for exhaust fan) | 1 |
| Exhaust fan | 12 V DC fan preferred (see safety notes) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
MQ-5 VCC ── Arduino 5V
MQ-5 GND ── Arduino GND
MQ-5 A0 ─── Arduino A0 (analog gas level)
MQ-5 D0 ─── (not used)

Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── Red LED ── GND
Arduino D7 ── Relay IN (fan relay, active LOW)
Fan supply + ── Relay COM     Relay NO ── Fan +
Fan supply - ───────────────── Fan - / GND (common)
```

The buzzer, LED and fan are OFF on startup.

## Wiring steps

1. Connect the MQ-5 module: VCC → 5 V, GND → GND, A0 → A0.
2. Connect the buzzer: + → D8, − → GND.
3. Connect the red LED: D13 → 220 Ω → LED anode, LED cathode → GND.
4. Optional fan: relay IN → D7, VCC → 5 V, GND → GND. Fan
   supply + → relay COM, relay NO → fan +, fan − → supply −.
   Keep this DC and low-voltage (see safety notes).
5. Upload `gas-leak-detector.ino`.
6. Power on and wait 1–2 minutes for the sensor to warm up
   and the baseline reading to settle (watch the Serial
   Monitor).
7. Test *without* an open gas source: hold an unlit gas
   lighter close to the sensor for a second or two (gas
   only, no flame) — the buzzer should sound and the fan
   start. Move it away and the alarm should clear.

## Calibration

Note the baseline analog reading in clean air from the
Serial Monitor (typically 100–300). Set `ALARM_THRESHOLD`
in the code well above the baseline (default 400) and
`CLEAR_THRESHOLD` (default 350) below it, so cooking fumes
do not set it off but a real leak does. If it alarms too
easily, raise the threshold; if it misses the lighter test,
lower it. Recheck the baseline after moving the sensor —
kitchens and garages have different normal air.

## Safety notes

- This is a learning / warning device, **not a certified
  gas alarm**. Do not rely on it as your only gas leak
  protection.
- If the alarm sounds for real: do NOT touch electrical
  switches or use a phone nearby — a spark can ignite gas.
  Turn off the gas supply at the cylinder / meter if it is
  safe to do so, open doors and windows from outside if
  possible, leave, and call the gas company / emergency
  services from outside the building.
- Prefer a 12 V DC exhaust fan. A mains fan switched by a
  relay in a gassy room is an ignition risk and a mains
  hazard — if one is ever used, get a qualified electrician
  to install it and use a motor rated for the environment.
- The MQ-5 gets warm in normal use — that is expected.
- Never test with a large gas release. The lighter test
  produces plenty of signal on its own.
