# Sensor and Safety Projects

A collection of 5 practical, beginner-friendly Arduino-based sensor
and safety projects, built for learning, home use, and portfolio / college work.
Each project lives in its own folder with its own README, working
Arduino code (`.ino`), and a text circuit diagram.

## Projects

| # | Project | What it does |
|---|---------|--------------|
| 1 | [smoke-fire-alarm](smoke-fire-alarm/) | MQ-2 smoke sensor triggers a buzzer and LED alarm when smoke crosses a threshold. |
| 2 | [gas-leak-detector](gas-leak-detector/) | MQ-5 gas sensor sounds a buzzer/LED alarm and runs an exhaust fan when LPG / gas crosses a threshold. |
| 3 | [temperature-humidity-monitor](temperature-humidity-monitor/) | DHT11 sensor shows temperature and humidity on LCD/serial, with an over-temperature alarm. |
| 4 | [motion-intruder-alarm](motion-intruder-alarm/) | PIR motion sensor arms/disarms with one button; entry delay, then a buzzer/LED intruder alarm. |
| 5 | [rain-detector-alarm](rain-detector-alarm/) | Rain sensor sounds a buzzer/LED alarm at the first drops, with an optional servo to close a window. |

## How to use

1. Pick a project folder and read its `README.md` first — it lists the
   exact components, wiring, and safety notes for that project.
2. Open the `.ino` file in the Arduino IDE (or Arduino CLI / VS Code
   with the Arduino extension). Project 3 needs the Adafruit
   "DHT sensor library" (plus "Adafruit Unified Sensor") installed
   from the Library Manager first — its README says so.
3. Select your board (Arduino Uno for all projects in this repo) and
   the correct port, then upload.
4. Wire the circuit exactly as described in the project README.
   **Do not power the circuit until you have double-checked the wiring.**
5. Open the Serial Monitor at 9600 baud (where the project uses it)
   to see readings and status messages.

## Common components and tools

- Arduino Uno (all 5 projects)
- Breadboard, jumper wires, USB cable
- Resistors: 10 kΩ, 220 Ω (see each project for exact values)
- MQ-2 smoke sensor (project 1), MQ-5 gas sensor (project 2)
- DHT11 temperature/humidity sensor and 16×2 LCD with I2C backpack (project 3)
- PIR motion sensor and push button (project 4)
- Rain sensor module and SG90 servo (project 5)
- 5 V relay module (project 2), buzzer and red LEDs (all projects)
- Multimeter, wire stripper, screwdriver, soldering iron (optional)

## ⚠️ Safety warnings — read before building anything

- **None of these projects is a certified safety device.** They are
  learning and early-warning projects. Install certified smoke,
  gas and intruder alarms in your home, and never let one of these
  builds be your only protection.
- If any alarm sounds for real, act first and investigate later:
  for fire or gas, leave the building and call emergency services
  (and the gas company for a leak) from outside. Do not touch
  electrical switches near a suspected gas leak — a spark can
  ignite gas.
- The MQ-2 and MQ-5 sensors get warm in normal use — that is
  expected. They both need 1–2 minutes of warm-up after power-on
  before readings are stable, and their thresholds must be
  calibrated in the room where they will be used.
- Test smoke and gas alarms only in small, controlled ways (a
  blown-out match, an unlit lighter) in a ventilated area, away
  from flammable materials. Never make a real fire or a large
  gas release to test an alarm.
- All projects in this repo are low-voltage (5 V) only. Never
  connect them to AC mains. The only relay here is the optional
  exhaust-fan relay in project 2 — keep that DC and low-voltage,
  and get a qualified electrician for anything involving mains.
- Alarms only help if they stay powered and are checked. Test
  each build regularly, and plan on sensor drift / wear (rain
  plates corrode; gas sensors age).

## Repo layout

```
sensor-safety-projects/
├── README.md
├── LICENSE
├── .gitignore
├── smoke-fire-alarm/
├── gas-leak-detector/
├── temperature-humidity-monitor/
├── motion-intruder-alarm/
└── rain-detector-alarm/
```

## Pushing to GitHub

```bash
git init
git add .
git commit -m "Add 5 Arduino sensor and safety projects"
git branch -M main
git remote add origin https://github.com/<your-username>/sensor-safety-projects.git
git push -u origin main
```

## License

MIT — see [LICENSE](LICENSE).
