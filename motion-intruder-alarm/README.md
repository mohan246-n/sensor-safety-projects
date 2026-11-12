# Motion Intruder Alarm

A PIR motion sensor watches a room or doorway. Arm the
alarm when you leave; if someone moves in front of the
sensor, you get a short entry delay to disarm it — then the
buzzer sounds and an LED flashes until it is disarmed.

## How it works

A PIR sensor detects the body heat of a moving person. The
alarm is a small state machine in the code:

- **DISARMED** — nothing happens when motion is seen.
- **ARMING** — after you press the button, an exit delay
  (default 10 s) lets you leave without triggering it.
- **ARMED** — motion starts the entry delay.
- **ENTRY** — the LED flashes as a warning for the entry
  delay (default 10 s). Pressing the button now disarms
  the alarm silently (this is how you come home).
- **ALARMING** — the delay expired, so the buzzer pulses
  and the LED flashes until someone presses the button.

One push button does everything: press to arm, press again
to disarm or silence. The alarm starts DISARMED on power-up,
so a power cut never leaves it screaming. The PIR needs
about 30 seconds after power-on to settle.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| PIR motion sensor module | HC-SR501 or similar | 1 |
| Push button | Momentary | 1 |
| Buzzer | 5 V active buzzer | 1 |
| LED | 5 mm red | 1 |
| Resistor | 220 Ω (LED) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
PIR VCC ── Arduino 5V
PIR GND ── Arduino GND
PIR OUT ── Arduino D2

Arduino D3 ── Push button ── GND  (INPUT_PULLUP, no resistor needed)
Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── Red LED ── GND
```

On the HC-SR501, the two small pots set sensitivity and how
long the OUT pin stays HIGH after motion — set the time pot
to its shortest while testing. Buzzer and LED are OFF, and
the alarm DISARMED, on startup.

## Wiring steps

1. Connect the PIR module: VCC → 5 V, GND → GND, OUT → D2.
2. Connect the push button between D3 and GND.
3. Connect the buzzer: + → D8, − → GND.
4. Connect the red LED: D13 → 220 Ω → LED anode, LED cathode → GND.
5. Upload `motion-intruder-alarm.ino` and open the Serial
   Monitor (9600 baud) to watch the state changes.
6. Power on, wait about 30 seconds for the PIR to settle,
   then press the button and walk out of its view during
   the exit delay.
7. Test: wait for "Alarm ARMED" on the Serial Monitor,
   then walk in front of the sensor. The LED should flash
   for the entry delay, then the buzzer should sound.
   Press the button to disarm.

## Calibration

Aim the PIR across the path people walk (it sees sideways
movement best), about head height, away from heaters,
sunny windows and fans — moving warm air causes false
alarms. Adjust the sensitivity pot so it catches a person
walking across the room but not a pet in the corner. Tune
`ENTRY_DELAY_MS` and `EXIT_DELAY_MS` in the code to your
doorway: enough time to reach the button, not so long that
an intruder is already inside. Mount it where the button is
reachable but not visible from outside a window.

## Safety notes

- This is a learning / warning device, **not a certified
  burglar alarm**. It has no battery backup, no tamper
  protection and no way to call anyone — do not rely on it
  as your only home security.
- Low voltage only — this project uses 5 V throughout and
  has no mains wiring.
- Warn family / housemates before testing: the buzzer is
  loud at close range, and a surprise alarm at night is
  nobody's idea of fun.
- If you hear a real intruder alarm, do not confront
  anyone — leave and call the police from a safe place.
