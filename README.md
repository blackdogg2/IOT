# Ctrl+Home — ESP32 Smart Home IoT Dashboard

Ctrl+Home is a smart home IoT project that connects an **ESP32** to a mobile-friendly **web dashboard** using **MQTT**.  
The ESP32 reads sensors, controls output devices, publishes live data, and receives commands from the dashboard.

This project includes two main files:

```text
IOT_project.ino   # ESP32 Arduino code
index.html        # Web dashboard
```

---

## Table of Contents

- [Project Overview](#project-overview)
- [Main Features](#main-features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Pin Configuration](#pin-configuration)
- [Software and Libraries](#software-and-libraries)
- [MQTT Configuration](#mqtt-configuration)
- [MQTT Topics](#mqtt-topics)
- [Dashboard Pages](#dashboard-pages)
- [Smart Modes](#smart-modes)
- [Sensor Logic](#sensor-logic)
- [Safety and Emergency Logic](#safety-and-emergency-logic)
- [How to Run the Project](#how-to-run-the-project)
- [How to Test with MQTT](#how-to-test-with-mqtt)
- [Project File Structure](#project-file-structure)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

## Project Overview

Ctrl+Home is an IoT smart home controller designed to monitor and control a room environment in real time.

The **ESP32** collects data from sensors such as temperature, humidity, light, motion, gas, water level, and potentiometer. The data is published to an MQTT broker. The **web dashboard** subscribes to those MQTT topics and displays the readings in a clean mobile app style interface.

The user can also control devices from the dashboard, such as:

- Main light
- Fan
- Curtain servo
- Alarm buzzer
- Mood LEDs

The project also includes smart modes and safety automation, so the system can react automatically when dangerous conditions are detected.

---

## Main Features

### Real-Time Monitoring

The dashboard displays live sensor values from the ESP32:

- Temperature
- Humidity
- LDR light level
- PIR motion status
- MQ-2 gas / smoke level
- Water tank level
- Potentiometer value

### Remote Control

The dashboard can send commands to the ESP32 using MQTT:

- Adjust main light brightness
- Change fan speed
- Move curtain position
- Turn alarm on or off
- Turn mood LEDs on or off
- Select smart mode

### Smart Automation

The ESP32 can automatically react to sensor conditions:

- Gas danger activates emergency mode
- Motion in Away Mode triggers emergency mode
- High temperature sends an alert
- Full water tank sends an alert
- Energy Mode adjusts light and fan based on motion and light level
- Sleep Mode adjusts light and fan based on motion and temperature

### Mobile-Friendly Dashboard

The web dashboard includes:

- Home page
- Control page
- Mood page
- Settings page
- Dark mode
- Device ID setting
- MQTT broker setting
- Browser notification option

---

## System Architecture

```text
Sensors
   ↓
ESP32
   ↓ MQTT publish
HiveMQ MQTT Broker
   ↓ MQTT WebSocket subscribe
Web Dashboard

Web Dashboard
   ↓ MQTT WebSocket publish
HiveMQ MQTT Broker
   ↓ MQTT subscribe
ESP32 Outputs
```

The ESP32 uses normal MQTT on port `1883`.  
The browser dashboard uses MQTT over WebSocket through:

```text
wss://broker.hivemq.com:8884/mqtt
```

---

## Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller |
| DHT11 Sensor | Temperature and humidity |
| LDR Sensor | Light level detection |
| PIR Sensor | Motion detection |
| MQ-2 Sensor | Gas / smoke detection |
| Water Level Sensor | Water tank level monitoring |
| Potentiometer | Manual brightness input |
| Servo Motor | Curtain control |
| Buzzer | Alarm output |
| Red LED | Mood / emergency light |
| Green LED | Mood light |
| Yellow LED | Mood light |
| I2C LCD 16x2 | Local display and notification |
| Breadboard and jumper wires | Circuit connection |

---

## Pin Configuration

### Sensors

| Sensor | ESP32 Pin |
|---|---|
| DHT11 | GPIO 4 |
| LDR | GPIO 34 |
| PIR Motion Sensor | GPIO 27 |
| MQ-2 Gas Sensor | GPIO 35 |
| Water Level Sensor | GPIO 32 |
| Potentiometer | GPIO 39 |

### Outputs

| Output | ESP32 Pin |
|---|---|
| Main Light | GPIO 14 |
| Fan | GPIO 26 |
| Buzzer | GPIO 25 |
| Curtain Servo | GPIO 13 |
| Red Mood LED | GPIO 16 |
| Green Mood LED | GPIO 17 |
| Yellow Mood LED | GPIO 15 |

### LCD I2C

| LCD Pin | ESP32 Pin |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## Software and Libraries

### ESP32 Arduino Libraries

Install these libraries in Arduino IDE:

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

Required libraries:

| Library | Purpose |
|---|---|
| WiFi | Connect ESP32 to WiFi |
| PubSubClient | MQTT communication |
| DHT | Read DHT11 temperature and humidity |
| ESP32Servo | Control servo motor |
| Wire | I2C communication |
| LiquidCrystal_I2C | Control I2C LCD |

### Web Dashboard Library

The dashboard uses MQTT.js from CDN:

```html
<script src="https://unpkg.com/mqtt/dist/mqtt.min.js"></script>
```

---

## MQTT Configuration

### ESP32 MQTT Settings

```cpp
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
```

### Web Dashboard MQTT Settings

```text
wss://broker.hivemq.com:8884/mqtt
```

### Default Device ID

```text
B6737115
```

### Base Topic

```text
ctrlhome/B6737115
```

The web dashboard allows the user to change the device ID in the Settings page.  
The ESP32 code uses `B6737115`, so the dashboard must use the same ID to communicate correctly.

---

## MQTT Topics

### Sensor Topics

The ESP32 publishes sensor data to these topics:

| Topic | Description |
|---|---|
| `ctrlhome/B6737115/temperature` | Temperature from DHT11 |
| `ctrlhome/B6737115/humidity` | Humidity from DHT11 |
| `ctrlhome/B6737115/light` | LDR analog value |
| `ctrlhome/B6737115/motion` | PIR motion status |
| `ctrlhome/B6737115/gas` | MQ-2 gas analog value |
| `ctrlhome/B6737115/water` | Water tank status |
| `ctrlhome/B6737115/potentiometer` | Potentiometer analog value |
| `ctrlhome/B6737115/alert` | Alert or system message |
| `ctrlhome/B6737115/currentmode` | Current smart mode |

### Control Topics

The dashboard publishes control commands to these topics:

| Topic | Example Message | Description |
|---|---:|---|
| `ctrlhome/B6737115/mode` | `study` | Change smart mode |
| `ctrlhome/B6737115/light/control` | `180` | Set light brightness |
| `ctrlhome/B6737115/fan/control` | `low` | Set fan speed |
| `ctrlhome/B6737115/curtain/control` | `90` | Set curtain servo angle |
| `ctrlhome/B6737115/alarm/control` | `ON` | Turn alarm on or off |

### Custom Mood Topics

| Topic | Example Message | Description |
|---|---:|---|
| `ctrlhome/B6737115/custom/brightness` | `150` | Custom mood brightness |
| `ctrlhome/B6737115/custom/rgb` | `255,0,255` | Custom LED color states |
| `ctrlhome/B6737115/custom/fan` | `low` | Custom fan speed |
| `ctrlhome/B6737115/custom/curtain` | `90` | Custom curtain position |
| `ctrlhome/B6737115/custom/alarm` | `ON` | Custom alarm monitoring |
| `ctrlhome/B6737115/custom/temp` | `25` | Preferred temperature |

### Output Status Topics

The ESP32 publishes output status back to the dashboard:

| Topic | Description |
|---|---|
| `ctrlhome/B6737115/status/light` | Current light PWM value |
| `ctrlhome/B6737115/status/fan` | Current fan PWM value |
| `ctrlhome/B6737115/status/curtain` | Current curtain angle |
| `ctrlhome/B6737115/status/rgb` | Active mood LED colors |
| `ctrlhome/B6737115/status/alarm` | Alarm status |

---

## Dashboard Pages

The web app is called **Ctrl+Home** and is written in one HTML file.

### Home Page

Shows:

- Current mode
- Temperature
- Humidity
- Alert message
- Live sensor readings
- Output status

### Control Page

Allows the user to control:

- Main light brightness
- Fan speed
- Curtain position
- Mood LEDs
- Alarm

### Mood Page

Allows the user to create a custom room setup:

- Mood name
- Brightness
- LED colors
- Fan speed
- Curtain position
- Preferred temperature
- Alarm monitoring

### Settings Page

Allows the user to configure:

- MQTT broker URL
- Device ID
- Notifications
- Theme

---

## Smart Modes

The ESP32 supports these modes:

| Mode | Light | Fan | Curtain | Mood LEDs | Alarm |
|---|---:|---|---:|---|---|
| Sleep | 0 | Low | 0° | Yellow | Off |
| Study | 255 | Medium | 140° | Red + Green + Yellow | Off |
| Relax | 100 | Low | 60° | Green + Yellow | Off |
| Away | 0 | Off | 0° | Off | Off |
| Energy | 60 | Low | 140° | Green | Off |
| Emergency | 255 | High | 180° | Blinking Red | On |
| Comfort | Custom | Custom | Custom | Custom | Custom |

---

## Sensor Logic

### LDR Light Level

The dashboard converts the LDR analog value into a human-readable label:

| LDR Value | Dashboard Status |
|---:|---|
| Below 1200 | Bright |
| 1200 to 2799 | Dim |
| 2800 and above | Dark |

### Gas / Smoke Safety

| MQ-2 Value | Dashboard Status |
|---:|---|
| Below 1200 | Safe |
| 1200 to 1999 | Warning |
| 2000 and above | Danger |

### Water Tank Level

The ESP32 maps the water sensor value from `0–4095` to `0–100%`.

| Percentage | Tank Status |
|---:|---|
| Below 10% | Tank Empty |
| 10% to 34% | Tank Low |
| 35% to 69% | Tank Medium |
| 70% to 89% | Tank Almost Full |
| 90% and above | Tank Full Filled |

### Potentiometer

The dashboard converts the potentiometer analog value into a percentage:

```text
percentage = analogValue / 4095 × 100
```

In Manual Mode, the ESP32 also uses the potentiometer to control light brightness.

---

## Safety and Emergency Logic

The ESP32 checks sensor values repeatedly and sends alerts when needed.

### Thresholds

```cpp
#define TEMP_HIGH_C 35
#define HUMIDITY_HIGH_PERCENT 80
#define GAS_HIGH_VALUE 2000
#define WATER_FULL_PERCENT 90
```

### Automatic Safety Actions

| Condition | Action |
|---|---|
| Gas value above 2000 | Sends gas alert and activates Emergency Mode |
| Water tank 90% or more | Sends water tank full alert |
| Temperature 35°C or higher | Sends high temperature alert |
| Humidity 80% or higher | Sends high humidity alert |
| Motion detected in Away Mode | Activates Emergency Mode |
| Motion detected when custom alarm is enabled | Activates Emergency Mode |

### Emergency Mode Behavior

When Emergency Mode is active:

- Main light turns on at full brightness
- Fan runs at high speed
- Curtain opens to 180°
- Buzzer turns on
- Red mood LED blinks every 500 ms
- Dashboard shows emergency status

---

## How to Run the Project

### 1. Prepare Arduino IDE

Install Arduino IDE and add ESP32 board support.

Install the required libraries:

- PubSubClient
- DHT sensor library
- ESP32Servo
- LiquidCrystal_I2C

### 2. Open ESP32 Code

Open:

```text
IOT_project.ino
```

### 3. Update WiFi Information

Change the WiFi name and password in the ESP32 code:

```cpp
const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";
```

### 4. Upload to ESP32

Connect the ESP32 to your computer and upload the code.

### 5. Open the Dashboard

Open:

```text
index(3).html
```

You can open it directly in a browser or host it using GitHub Pages.

### 6. Connect MQTT

On the dashboard:

1. Go to **Settings**
2. Check broker URL:

```text
wss://broker.hivemq.com:8884/mqtt
```

3. Check device ID:

```text
B6737115
```

4. Press **Connect**

### 7. Test Sensor Data

When the ESP32 connects successfully, the dashboard should show live readings.

---

## How to Test with MQTT

You can test the dashboard without ESP32 by publishing messages manually using an MQTT client.

### Example Sensor Test

Publish temperature:

```text
Topic: ctrlhome/B6737115/temperature
Message: 28.5
```

Publish humidity:

```text
Topic: ctrlhome/B6737115/humidity
Message: 65
```

Publish gas value:

```text
Topic: ctrlhome/B6737115/gas
Message: 2100
```

Publish water level:

```text
Topic: ctrlhome/B6737115/water
Message: Tank Medium (55% filled)
```

### Example Control Test

Set mode:

```text
Topic: ctrlhome/B6737115/mode
Message: study
```

Set light brightness:

```text
Topic: ctrlhome/B6737115/light/control
Message: 200
```

Set fan:

```text
Topic: ctrlhome/B6737115/fan/control
Message: high
```

Set curtain:

```text
Topic: ctrlhome/B6737115/curtain/control
Message: 90
```

Turn alarm on:

```text
Topic: ctrlhome/B6737115/alarm/control
Message: ON
```

---

## Project File Structure

```text
Ctrl-Home/
│
├── IOT_project(1).ino
├── index(3).html
└── README.md
```

---

## Important Notes

- The ESP32 uses MQTT port `1883`.
- The web dashboard uses MQTT WebSocket port `8884`.
- The ESP32 and dashboard must use the same base topic.
- The default base topic is:

```text
ctrlhome/B6737115
```

- GPIO 34, 35, and 39 are input-only pins on ESP32, so they are correctly used for analog sensors.
- The dashboard can work remotely as long as the ESP32 and browser both connect to the same online MQTT broker.
- The public HiveMQ broker is useful for testing, but a private broker is better for real deployment.

---

## Future Improvements

- Add login system
- Add cloud database storage
- Add sensor history charts
- Add Node-RED integration
- Add mobile app version
- Add voice assistant control
- Add automatic WiFi setup page
- Add private MQTT broker for better security
- Add HTTPS hosting for the web dashboard
- Add stronger notification system

---

## Author

**Sokvisal Leng**

---

## License

This project is for educational purposes only.
