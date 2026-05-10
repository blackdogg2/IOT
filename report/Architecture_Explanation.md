# Architecture Explanation — Ctrl+Home Smart Home IoT System

## 1. Architecture Overview

Ctrl+Home uses a publish/subscribe IoT architecture.

```text
Sensors → ESP32 → MQTT Broker → Web Dashboard
Web Dashboard → MQTT Broker → ESP32 → Output Devices
```

The ESP32 reads data from sensors and publishes it to the MQTT broker.  
The dashboard subscribes to the sensor topics and updates the user interface.  
When the user controls a device from the dashboard, the dashboard publishes a command to MQTT, and the ESP32 receives it.

---

## 2. Main System Diagram

```md
![IoT Diagram](../diagrams/IoT-diagram.png)
```

---

## 3. Architecture Flow

```text
+---------------------------+
|        Sensors            |
|---------------------------|
| DHT11                     |
| LDR                       |
| PIR                       |
| MQ-2                      |
| Water Level Sensor        |
| Potentiometer             |
+-------------+-------------+
              |
              v
+---------------------------+
|          ESP32            |
|---------------------------|
| Reads sensor values       |
| Processes safety logic    |
| Controls outputs          |
| Publishes MQTT data       |
| Receives MQTT commands    |
+-------------+-------------+
              |
              | MQTT TCP 1883
              v
+---------------------------+
|       MQTT Broker         |
|---------------------------|
| broker.hivemq.com         |
| Routes messages by topic  |
+-------------+-------------+
              ^
              | MQTT WebSocket
              | wss://broker.hivemq.com:8884/mqtt
              |
+-------------+-------------+
|      Web Dashboard        |
|---------------------------|
| index.html                |
| HTML/CSS/JavaScript       |
| MQTT.js                   |
+---------------------------+
```

---

## 4. ESP32 Layer

The ESP32 is responsible for:

- Connecting to WiFi
- Connecting to MQTT broker
- Reading sensor data
- Publishing sensor data
- Receiving dashboard commands
- Controlling output devices
- Applying smart modes
- Running emergency logic
- Updating the LCD display

---

## 5. Web Dashboard Layer

The dashboard is responsible for:

- Connecting to MQTT using WebSocket
- Showing live sensor values
- Sending control commands
- Changing smart modes
- Saving custom mood settings
- Showing alerts
- Allowing device ID configuration

The dashboard uses MQTT.js:

```html
<script src="https://unpkg.com/mqtt/dist/mqtt.min.js"></script>
```

---

## 6. MQTT Broker Layer

Broker used:

```text
broker.hivemq.com
```

The ESP32 connects using:

```text
MQTT TCP port 1883
```

The browser dashboard connects using:

```text
MQTT WebSocket wss://broker.hivemq.com:8884/mqtt
```

The broker allows both devices to communicate even though they use different connection types.

```text
ESP32 MQTT TCP → HiveMQ Broker ← Browser MQTT WebSocket
```

---

## 7. MQTT Topic Design

Default device ID:

```text
B6737115
```

Base topic:

```text
ctrlhome/B6737115
```

All MQTT topics are created using this base topic.

---

## 8. Sensor Data Topics

```text
ctrlhome/B6737115/temperature
ctrlhome/B6737115/humidity
ctrlhome/B6737115/light
ctrlhome/B6737115/motion
ctrlhome/B6737115/gas
ctrlhome/B6737115/water
ctrlhome/B6737115/potentiometer
ctrlhome/B6737115/alert
ctrlhome/B6737115/currentmode
```

Example data flow:

```text
DHT11 → ESP32 → ctrlhome/B6737115/temperature → Dashboard
```

---

## 9. Control Command Topics

```text
ctrlhome/B6737115/mode
ctrlhome/B6737115/light/control
ctrlhome/B6737115/fan/control
ctrlhome/B6737115/curtain/control
ctrlhome/B6737115/alarm/control
```

Example control flow:

```text
Dashboard Fan Button → ctrlhome/B6737115/fan/control → ESP32 → Fan Output
```

---

## 10. Output Status Topics

```text
ctrlhome/B6737115/status/light
ctrlhome/B6737115/status/fan
ctrlhome/B6737115/status/curtain
ctrlhome/B6737115/status/rgb
ctrlhome/B6737115/status/alarm
```

These topics allow the ESP32 to confirm output states back to the dashboard.

---

## 11. Hardware Architecture

### Sensor Inputs

| Component | ESP32 Pin |
|---|---:|
| DHT11 | GPIO 4 |
| LDR | GPIO 34 |
| PIR Sensor | GPIO 27 |
| MQ-2 Gas Sensor | GPIO 35 |
| Water Level Sensor | GPIO 32 |
| Potentiometer | GPIO 39 |

### Output Devices

| Component | ESP32 Pin |
|---|---:|
| Main Light | GPIO 14 |
| Fan | GPIO 26 |
| Buzzer | GPIO 25 |
| Servo Curtain | GPIO 13 |
| Red LED | GPIO 16 |
| Green LED | GPIO 17 |
| Yellow LED | GPIO 15 |

### LCD

| LCD Signal | ESP32 Pin |
|---|---:|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 12. Smart Mode Logic

The project supports these smart modes:

| Mode | Function |
|---|---|
| Manual | Direct user control |
| Sleep | Quiet and dim room setup |
| Study | Bright room setup |
| Relax | Soft comfort setup |
| Away | Security monitoring |
| Energy | Reduced energy usage |
| Emergency | Safety alert mode |
| Comfort | Custom user mood |

---

## 13. Emergency Logic

Emergency mode can be triggered by:

- High gas value
- Motion detected in Away Mode
- Motion detected while custom alarm monitoring is enabled

Emergency behavior:

```text
Light → Full brightness
Fan → High
Curtain → Open
Buzzer → ON
Red LED → Blinking
Dashboard → Alert message
LCD → Emergency message
```

---

## 14. Why WebSocket Is Used

The ESP32 can connect to MQTT directly using TCP port `1883`.

However, a browser cannot normally connect using raw MQTT TCP.  
Because of this, the dashboard uses **MQTT over WebSocket**.

```text
ESP32: MQTT TCP
Browser: MQTT WebSocket
Broker: Routes both sides
```

This lets the web dashboard control the ESP32 from a phone or laptop browser.

---

## 15. Summary

The Ctrl+Home architecture demonstrates the main parts of an IoT system:

```text
Sensing + Connectivity + Control + Automation + User Interface
```

The ESP32 handles the hardware side.  
The MQTT broker handles communication.  
The web dashboard provides remote monitoring and control.
