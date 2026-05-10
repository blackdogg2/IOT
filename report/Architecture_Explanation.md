# Architecture Explanation — Ctrl+Home Smart Home IoT System

## 1. Project Name

**Ctrl+Home — Smart Home IoT Dashboard**

Ctrl+Home is an IoT smart home system that uses an **ESP32**, sensors, output devices, MQTT communication, and a browser-based web dashboard. The system can monitor real-time room conditions and control devices remotely.

Main files:

```text
IOT_project(1).ino
index(3).html
```

---

## 2. Architecture Overview

The system is built using a simple IoT communication architecture:

```text
Sensors → ESP32 → MQTT Broker → Web Dashboard
Web Dashboard → MQTT Broker → ESP32 → Output Devices
```

The ESP32 works as the physical IoT device. It reads sensors and controls hardware outputs.  
The web dashboard works as the user interface. It displays data and sends commands.

---

## 3. Main Architecture Diagram

```text
+-----------------------------+
|        Sensor Layer         |
|-----------------------------|
| DHT11 Temperature/Humidity  |
| LDR Light Sensor            |
| PIR Motion Sensor           |
| MQ-2 Gas Sensor             |
| Water Level Sensor          |
| Potentiometer               |
+-------------+---------------+
              |
              v
+-----------------------------+
|      ESP32 Controller       |
|-----------------------------|
| Reads sensor values         |
| Processes safety logic      |
| Controls outputs            |
| Publishes MQTT data         |
| Subscribes to commands      |
+-------------+---------------+
              |
              | MQTT TCP Port 1883
              v
+-----------------------------+
|        MQTT Broker          |
|-----------------------------|
| broker.hivemq.com           |
| Message routing             |
| Publish / Subscribe system  |
+-------------+---------------+
              ^
              | MQTT over WebSocket
              | wss://broker.hivemq.com:8884/mqtt
              |
+-------------+---------------+
|       Web Dashboard         |
|-----------------------------|
| index(3).html               |
| MQTT.js                     |
| Real-time monitoring        |
| Manual control              |
| Smart mode selection        |
+-----------------------------+
```

---

## 4. Layer-by-Layer Explanation

## 4.1 Sensor Layer

The sensor layer collects environmental data from the room.

| Sensor | Purpose |
|---|---|
| DHT11 | Reads temperature and humidity |
| LDR | Measures light level |
| PIR Sensor | Detects motion |
| MQ-2 Sensor | Detects gas or smoke level |
| Water Level Sensor | Measures water tank level |
| Potentiometer | Provides manual analog input |

These sensors are connected directly to the ESP32 pins. The ESP32 reads their values repeatedly in the `loop()` function.

---

## 4.2 ESP32 Controller Layer

The ESP32 is the brain of the project. It performs five main jobs:

1. Connects to WiFi
2. Connects to MQTT broker
3. Reads sensor values
4. Controls output devices
5. Sends and receives MQTT messages

The ESP32 code is written in Arduino C++ in:

```text
IOT_project(1).ino
```

The ESP32 publishes sensor data every **2.5 seconds** using this timing logic:

```cpp
if (millis() - lastPublish >= 2500) {
    lastPublish = millis();
}
```

This prevents the ESP32 from sending data too fast and keeps the system stable.

---

## 4.3 MQTT Broker Layer

The MQTT broker works as the middle communication server.

The broker used in this project is:

```text
broker.hivemq.com
```

The ESP32 connects to the broker using normal MQTT:

```text
Port: 1883
```

The web dashboard connects to the same broker using MQTT over WebSocket:

```text
wss://broker.hivemq.com:8884/mqtt
```

This is important because a browser cannot normally use raw MQTT TCP directly. The browser needs WebSocket, so the dashboard uses MQTT.js to communicate through WebSocket.

---

## 4.4 Web Dashboard Layer

The web dashboard is written in:

```text
index(3).html
```

It includes:

- HTML for page structure
- CSS for mobile app design
- JavaScript for MQTT and control logic
- MQTT.js for WebSocket MQTT connection

The dashboard has four main pages:

| Page | Purpose |
|---|---|
| Home | Shows live sensor values and output status |
| Control | Allows manual control of devices |
| Mood | Allows custom mood creation |
| Settings | Allows MQTT broker and device ID setup |

---

## 5. Data Flow Explanation

## 5.1 Sensor Data Flow

```text
Sensor → ESP32 analog/digital read → MQTT publish → Broker → Dashboard subscribe → UI update
```

Example using temperature:

1. DHT11 measures temperature.
2. ESP32 reads temperature.
3. ESP32 publishes the value to:

```text
ctrlhome/B6737115/temperature
```

4. MQTT broker receives the value.
5. Dashboard subscribes to the topic.
6. Dashboard updates the temperature card.

---

## 5.2 Control Command Flow

```text
Dashboard button → MQTT publish → Broker → ESP32 subscribe → Hardware output changes
```

Example using fan control:

1. User presses **High** fan button on dashboard.
2. Dashboard publishes:

```text
Topic: ctrlhome/B6737115/fan/control
Message: high
```

3. MQTT broker forwards the command.
4. ESP32 receives the command in the callback function.
5. ESP32 changes fan PWM to high speed.
6. ESP32 publishes the new fan status back to the dashboard.

---

## 6. MQTT Topic Architecture

The project uses a topic structure based on the device ID.

Default device ID:

```text
B6737115
```

Base topic:

```text
ctrlhome/B6737115
```

This means all topics begin with:

```text
ctrlhome/B6737115/
```

---

## 6.1 Sensor Topics

These topics are published by the ESP32 and received by the dashboard.

| Topic | Data Type | Example |
|---|---|---|
| `ctrlhome/B6737115/temperature` | Float | `28.50` |
| `ctrlhome/B6737115/humidity` | Float | `65.00` |
| `ctrlhome/B6737115/light` | Integer | `900` |
| `ctrlhome/B6737115/motion` | Text | `Motion Detected` |
| `ctrlhome/B6737115/gas` | Integer | `1500` |
| `ctrlhome/B6737115/water` | Text | `Tank Medium (55% filled)` |
| `ctrlhome/B6737115/potentiometer` | Integer | `2048` |
| `ctrlhome/B6737115/alert` | Text | `All sensors normal` |
| `ctrlhome/B6737115/currentmode` | Text | `manual` |

---

## 6.2 Control Topics

These topics are published by the dashboard and received by the ESP32.

| Topic | Message Example | Function |
|---|---|---|
| `ctrlhome/B6737115/mode` | `study` | Change smart mode |
| `ctrlhome/B6737115/light/control` | `180` | Set light brightness |
| `ctrlhome/B6737115/fan/control` | `medium` | Set fan speed |
| `ctrlhome/B6737115/curtain/control` | `90` | Set curtain angle |
| `ctrlhome/B6737115/alarm/control` | `ON` | Turn alarm on |

---

## 6.3 Custom Mood Topics

These topics allow the dashboard to send custom mood settings.

| Topic | Example |
|---|---|
| `ctrlhome/B6737115/custom/brightness` | `150` |
| `ctrlhome/B6737115/custom/rgb` | `255,0,255` |
| `ctrlhome/B6737115/custom/fan` | `low` |
| `ctrlhome/B6737115/custom/curtain` | `90` |
| `ctrlhome/B6737115/custom/alarm` | `ON` |
| `ctrlhome/B6737115/custom/temp` | `25` |

---

## 6.4 Status Topics

The ESP32 publishes output status back to the dashboard.

| Topic | Meaning |
|---|---|
| `ctrlhome/B6737115/status/light` | Current light brightness |
| `ctrlhome/B6737115/status/fan` | Current fan PWM |
| `ctrlhome/B6737115/status/curtain` | Current curtain angle |
| `ctrlhome/B6737115/status/rgb` | Mood LED status |
| `ctrlhome/B6737115/status/alarm` | Alarm ON/OFF |

---

## 7. Hardware Architecture

## 7.1 Input Pins

| Component | Pin | Type |
|---|---:|---|
| DHT11 | GPIO 4 | Digital |
| LDR | GPIO 34 | Analog input |
| PIR | GPIO 27 | Digital |
| MQ-2 | GPIO 35 | Analog input |
| Water sensor | GPIO 32 | Analog input |
| Potentiometer | GPIO 39 | Analog input |

GPIO 34, 35, and 39 are input-only pins on ESP32, so they are suitable for analog sensors.

---

## 7.2 Output Pins

| Component | Pin | Type |
|---|---:|---|
| Main light | GPIO 14 | PWM output |
| Fan | GPIO 26 | PWM output |
| Buzzer | GPIO 25 | Digital output |
| Servo curtain | GPIO 13 | Servo PWM |
| Red LED | GPIO 16 | PWM output |
| Green LED | GPIO 17 | PWM output |
| Yellow LED | GPIO 15 | PWM output |

---

## 7.3 LCD Pins

| LCD Signal | ESP32 Pin |
|---|---:|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

The LCD is used to show system messages such as:

- Startup message
- Current mode
- Notifications
- Alerts

---

## 8. Smart Mode Architecture

The smart mode system is controlled using the function:

```cpp
applyMode(String mode)
```

When the dashboard sends a mode name, the ESP32 applies a group of output settings.

| Mode | Light | Fan | Curtain | LEDs | Alarm |
|---|---:|---|---:|---|---|
| Sleep | 0 | Low | 0° | Yellow | Off |
| Study | 255 | Medium | 140° | Red + Green + Yellow | Off |
| Relax | 100 | Low | 60° | Green + Yellow | Off |
| Away | 0 | Off | 0° | Off | Off |
| Energy | 60 | Low | 140° | Green | Off |
| Emergency | 255 | High | 180° | Blinking Red | On |
| Comfort | Custom | Custom | Custom | Custom | Custom |

---

## 9. Safety Architecture

The safety system is checked in:

```cpp
checkEmergencyLogic()
```

The project uses these threshold values:

```cpp
TEMP_HIGH_C = 35
HUMIDITY_HIGH_PERCENT = 80
GAS_HIGH_VALUE = 2000
WATER_FULL_PERCENT = 90
```

### Safety Conditions

| Condition | Result |
|---|---|
| Gas value above 2000 | Emergency Mode |
| Water tank 90% or more | Alert notification |
| Temperature 35°C or more | Alert notification |
| Humidity 80% or more | Alert notification |
| Motion detected in Away Mode | Emergency Mode |
| Motion detected in Comfort Mode with alarm enabled | Emergency Mode |

---

## 10. Emergency Mode Architecture

Emergency Mode is the strongest safety action in the system.

When activated:

```text
Light → 255
Fan → High
Curtain → 180°
Alarm → ON
Red LED → Blinking
Alert → EMERGENCY MODE
```

The red LED blinking is controlled every 500 ms:

```cpp
if (millis() - lastEmergencyBlink >= 500)
```

---

## 11. WebSocket Explanation

The dashboard runs inside a browser. A browser cannot directly use the normal MQTT TCP connection on port `1883`.

Because of this, the project uses **MQTT over WebSocket**.

The dashboard connects to:

```text
wss://broker.hivemq.com:8884/mqtt
```

The ESP32 connects to:

```text
broker.hivemq.com:1883
```

Both are connected to the same broker, so they can still communicate through the same MQTT topics.

```text
ESP32 MQTT TCP → Broker ← Browser MQTT WebSocket
```

This allows the user to control the ESP32 from a phone or laptop browser.

---

## 12. Why This Architecture Is Useful

This architecture is good for an IoT project because:

- It separates hardware control and user interface.
- MQTT is lightweight and suitable for IoT.
- The dashboard can be accessed from phone or computer.
- Sensor data updates in real time.
- Control commands are sent instantly.
- The project supports both manual control and automation.
- The system can react to dangerous conditions automatically.

---

## 13. Summary

The Ctrl+Home architecture combines hardware, software, and network communication into one complete IoT system.

The ESP32 handles the physical world by reading sensors and controlling outputs.  
The MQTT broker handles communication.  
The web dashboard gives the user a clean interface for monitoring and control.

Overall, the system demonstrates the main concepts of IoT:

```text
Sensing + Connectivity + Control + Automation
```
