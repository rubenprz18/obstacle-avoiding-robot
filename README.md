# Obstacle-Avoiding Robot Car
An autonomous 2-wheel drive robot car that navigates its environment independently, detecting obstacles with an ultrasonic sensor and rerouting using an Arduino-controlled motor driver.

Built from scratch in approximately 8-10 hours as my first independent Arduino hardware project.

---

## Demo
> *Video Link*

---

## How It Works
An HC-SR04 ultrasonic sensor continuously measures the distance to objects ahead. When an obstacle is detected within 20cm, the robot stops, reverses briefly, turns right, and resumes driving forward. Motor speeds are independently tuned per wheel to compensate for inconsistencies between the two TT gear motors.

A brief full-power burst is applied at the start of each movement to overcome the static friction of the DC gear motors.

---

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino Uno R3 clone (Horizon Robotics Lab starter kit) |
| Chassis | 2WD acrylic robot car chassis kit |
| Motors | 2x TT DC gear motors (48:1 reduction ratio, included with chassis) |
| Motor Driver | L298N dual H-bridge motor driver board |
| Sensor | HC-SR04 ultrasonic distance sensor |
| Power | 4x AA batteries |
| Other | Breadboard, jumper wires, soldering iron |

---

## Wiring
> *Photo of build*
> 
> *Tinkercad schematic*

**Ultrasonic Sensor → Arduino**
| HC-SR04 | Arduino |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | Pin 9 |
| ECHO | Pin 10 |

**L298N Motor Driver → Arduino**
| L298N | Arduino |
|---|---|
| IN1 | Pin 2 |
| IN2 | Pin 3 |
| IN3 | Pin 4 |
| IN4 | Pin 5 |
| ENA | Pin 6 |
| ENB | Pin 7 |
| GND | GND |

**Power**
- 4x AA battery pack → L298N & Arduino

---

## Software

**Libraries required:**
- [NewPing](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home) — ultrasonic sensor reading

Install via Arduino IDE: Tools → Manage Libraries → search "NewPing"

**Key tunable parameters in the code:**
```cpp
#define STOP_DISTANCE 20    // cm — detection threshold
#define SPEEDL 215          // left motor speed (0-255)
#define SPEEDR 180          // right motor speed (0-255)
#define TURN_SPEED_L 170    // left motor speed during turns
#define TURN_SPEED_R 150    // right motor speed during turns
#define TURN_DURATION 300   // ms — how long to turn
```

**Full sketch:** see `obstacle_avoider.ino`

---

## Challenges & Troubleshooting

**Motor connections required soldering**
The TT motors included with the chassis kit have bare copper solder tabs rather than pre-attached wire leads. Temporary mechanical connections were initially used but were unreliable. Soldering the connections directly to the tabs resolved the issue.

**Robot veered left consistently**
The two TT gear motors, despite being identical models, spin at slightly different speeds due to manufacturing tolerances. The robot consistently drifted left during forward driving. Fixed by independently tuning left and right motor PWM values (SPEEDL 215 vs SPEEDR 180) until straight-line driving was achieved.

**Turns were overshooting (~200° instead of ~90°)**
Initial TURN_DURATION was too long and turn speed too high, causing the robot to overshoot the intended 90° turn significantly. Reduced both TURN_DURATION and the turn speed values (separate from forward speed) until turns were approximately 90°.

**Motors stalling after stopping**
At lower PWM values, the TT motors couldn't overcome their own static friction when starting from a dead stop — they would receive a signal but not begin rotating. Solved by adding a kickstart function: a brief 80ms full-power pulse (PWM 255) applied before every movement command to break static friction, followed by the normal cruising speed.

**9V battery insufficient for full circuit**
A 9V block battery couldn't sustain simultaneous power to both motors, the L298N board, and the Arduino. Switched to a 4x AA battery pack (6V, significantly higher current capacity); this is the standard recommended power setup for small 2WD robot builds.

---

## What I Learned
- How ultrasonic sensors measure distance via time-of-flight (sound pulse timing)
- How an L298N H-bridge motor driver controls DC motor direction and speed via PWM signals
- The difference between voltage and current capacity — and why a "higher voltage" battery isn't always better
- PID-adjacent thinking: independently tuning two outputs (left/right motor speed) to achieve a desired behavior (straight driving)
- The concept of static friction vs. kinetic friction in motor control, and software-side workarounds (kickstart pulse)
- Practical soldering for motor connections and sensor header pins

---

## Future Improvements
- [ ] Add a physical on/off button to start and stop the robot without disconnecting the battery
- [ ] Implement left/right turn selection: use a second sensor to determine which side has more clearance
- [ ] Wire management: color-coded wires and hot glue instead of electrical tape for cleaner, more permanent builds
- [ ] Add a line-following mode using photoresistors on the underside of the chassis

---

## Background
Built during the summer of 2026 as a personal engineering project alongside a physics REU at Coe College. Prior hardware experience limited to a servo-controlled robotic arm built in high school. All motor control logic, sensor integration, and troubleshooting done independently.
