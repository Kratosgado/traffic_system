# Traffic System

An Arduino-based intelligent traffic light management system that communicates with the [TrafficControlApp](https://github.com/Kratosgado/TrafficControlApp) Android application via Bluetooth.

## Overview

This project implements a dual-lane traffic light controller using IR sensors to detect approaching vehicles and push buttons for pedestrian crossings. The system sends real-time traffic state updates to a paired Android device over a Bluetooth serial connection, and can also receive override commands from the app to manually control the lights.

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino (Uno/Mega) | Main microcontroller |
| IR sensor (×2) | Vehicle detection for each lane |
| RGB/LED traffic lights (×2) | Red, yellow, and green indicators per lane |
| Push button (×2) | Pedestrian crossing request per lane |
| Bluetooth module (e.g. HC-05) | Serial communication with the Android app |

### Pin Mapping

**Right lane**

| Signal | Pin |
|---|---|
| IR sensor | 2 |
| Human button | 3 |
| Red LED | 4 |
| Blue LED | 5 |
| Green LED | 6 |

**Left lane**

| Signal | Pin |
|---|---|
| IR sensor | 9 |
| Human button | 8 |
| Red LED | 10 |
| Green LED | 11 |
| Blue LED | 12 |

## Android App Integration

The system connects to the [TrafficControlApp](https://github.com/Kratosgado/TrafficControlApp) Android application over Bluetooth. The Bluetooth module is wired to the Arduino's hardware serial (TX/RX) pins and communicates at **9600 baud**.

### Traffic State Protocol

The Arduino sends a single integer code whenever a traffic light changes state:

| Code | Constant | Description |
|---|---|---|
| 0 | `RRED` | Right lane → Red |
| 1 | `RYELLOW` | Right lane → Yellow |
| 2 | `RGREEN` | Right lane → Green |
| 3 | `LRED` | Left lane → Red |
| 4 | `LYELLOW` | Left lane → Yellow |
| 5 | `LGREEN` | Left lane → Green |
| 6 | `RHUMAN` | Right lane — pedestrian crossing active |
| 7 | `LHUMAN` | Left lane — pedestrian crossing active |
| 8 | `NORHUMAN` | Right lane — pedestrian crossing ended |
| 9 | `NOLHUMAN` | Left lane — pedestrian crossing ended |

The Android app can also **send** command codes to the Arduino to override the automatic behaviour:

| Code | Effect |
|---|---|
| `RRED` (0) | Force right lane to Red |
| `RGREEN` (2) | Force right lane to Green |
| `LRED` (3) | Force left lane to Red |
| `LGREEN` (5) | Force left lane to Green |

## Getting Started

1. Wire the hardware according to the pin mapping above.
2. Connect a Bluetooth module (e.g. HC-05) to the Arduino's TX/RX pins.
3. Open `traffic_system.ino` in the [Arduino IDE](https://www.arduino.cc/en/software).
4. Upload the sketch to your Arduino board.
5. Pair your Android device with the Bluetooth module.
6. Install and open the [TrafficControlApp](https://github.com/Kratosgado/TrafficControlApp) on your Android device and connect to the paired module.

## Project Structure

```
traffic_system/
├── traffic_system.ino   # Arduino entry point (setup / loop)
├── TrafficSystem.hpp    # TrafficSystem class declaration & timing constants
├── TrafficSystem.cpp    # Main control logic & Bluetooth serial communication
├── Traffic.hpp          # Base Traffic class (ultrasonic sensor variant)
├── Traffic.cpp          # Ultrasonic detection, state switching, LED control
├── IrTraffic.hpp        # IrTraffic subclass declaration (IR sensor variant)
└── IrTraffic.cpp        # IR-based vehicle detection loop
```

## Timing Constants

| Constant | Default | Description |
|---|---|---|
| `MAX_GO_TIME` | 7000 ms | Maximum time a lane stays green |
| `MAX_WAIT_TIME` | 7000 ms | Maximum time a lane waits before getting green |
| `YELLOW_WAIT_TIME` | 2000 ms | Duration of the yellow phase |
| `EMERGENCY_WAIT_TIME` | 5000 ms | Hold time during an emergency override |
| `HUMAN_CROSS_TIME` | 5000 ms | Minimum pedestrian crossing hold time |
| `MAX_DISTANCE` | 10 cm | Vehicle detection distance threshold (base `Traffic` ultrasonic variant) |

## License

This project is open source. Feel free to use and modify it for your own purposes.
