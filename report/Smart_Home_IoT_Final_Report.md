# Smart Home IoT Final Report

## Project Title

**Ctrl+Home — ESP32 Smart Home IoT Dashboard**

---

## 1. Background and Significance

The Internet of Things, or IoT, is a technology concept where physical devices are connected to the internet so they can collect data, communicate, and be controlled remotely. IoT is commonly used in smart homes, smart cities, agriculture, healthcare, factories, and transportation.

A smart home system is one of the most practical examples of IoT. It allows users to monitor their home environment and control devices such as lights, fans, alarms, and curtains using a smartphone or web dashboard. This improves comfort, safety, and energy efficiency.

The **Ctrl+Home** project was developed as a smart home IoT system using an ESP32 microcontroller, sensors, MQTT communication, and a web dashboard. The system can monitor temperature, humidity, light level, motion, gas, water tank level, and potentiometer value. It can also control outputs such as a main light, fan, curtain servo, buzzer alarm, and mood LEDs.

This project is significant because it combines two important IoT requirements:

1. **Remote connectivity** — the user can monitor and control the system from a web dashboard.
2. **Autonomous intelligence** — the system can make automatic decisions based on sensor data.

---

## 2. Objectives

The main objectives of this project are:

- To design and build a smart home IoT system using ESP32.
- To monitor sensor data in real time using a web dashboard.
- To communicate between ESP32 and the dashboard using MQTT.
- To control home devices remotely from a browser.
- To create smart modes for different room situations.
- To implement safety alerts for gas, temperature, humidity, water level, and motion.
- To demonstrate autonomous decision-making using sensor values.
- To improve understanding of IoT system architecture, MQTT, ESP32 programming, and web dashboard design.

---

## 3. Scope of the Project

This project focuses on a small-scale smart home room controller.

### Included in the project

- ESP32 WiFi connection
- MQTT communication
- Web dashboard interface
- Real-time sensor monitoring
- Manual device control
- Smart mode selection
- Custom mood setting
- Safety alert logic
- LCD notification
- Remote access through MQTT broker

### Not included in the project

- User login system
- Cloud database storage
- Long-term data history
- Real physical home appliance wiring
- Mobile application package
- Private MQTT server security

The system is mainly designed for educational and demonstration purposes.

---

## 4. Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 | 1 | Main controller |
| DHT11 | 1 | Temperature and humidity sensing |
| LDR | 1 | Light level sensing |
| PIR Sensor | 1 | Motion detection |
| MQ-2 Sensor | 1 | Gas and smoke detection |
| Water Level Sensor | 1 | Water tank level sensing |
| Potentiometer | 1 | Manual analog input |
| Servo Motor | 1 | Curtain movement |
| Buzzer | 1 | Alarm output |
| Red LED | 1 | Mood/emergency light |
| Green LED | 1 | Mood light |
| Yellow LED | 1 | Mood light |
| I2C LCD 16x2 | 1 | Local status display |
| Breadboard | 1 | Circuit connection |
| Jumper wires | Several | Wiring |

---

## 5. Software and Tools

| Software / Tool | Purpose |
|---|---|
| Arduino IDE | Programming ESP32 |
| HTML | Dashboard structure |
| CSS | Dashboard design |
| JavaScript | Dashboard logic |
| MQTT.js | MQTT WebSocket communication |
| HiveMQ Broker | MQTT message broker |
| Browser | Runs the web dashboard |

### Arduino Libraries

The ESP32 code uses these libraries:

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

---

## 6. System Architecture

The system uses MQTT publish/subscribe communication.

```text
Sensors → ESP32 → MQTT Broker → Web Dashboard
Web Dashboard → MQTT Broker → ESP32 → Output Devices
```

The ESP32 connects to WiFi and communicates with the MQTT broker. It publishes sensor values and subscribes to command topics. The web dashboard connects to the same MQTT broker using MQTT over WebSocket.

### MQTT Broker

```text
broker.hivemq.com
```

### ESP32 MQTT Port

```text
1883
```

### Web Dashboard MQTT WebSocket URL

```text
wss://broker.hivemq.com:8884/mqtt
```

---

## 7. Pin Configuration

### Sensor Pins

| Sensor | ESP32 Pin |
|---|---:|
| DHT11 | GPIO 4 |
| LDR | GPIO 34 |
| PIR | GPIO 27 |
| MQ-2 | GPIO 35 |
| Water Level Sensor | GPIO 32 |
| Potentiometer | GPIO 39 |

### Output Pins

| Output | ESP32 Pin |
|---|---:|
| Main Light | GPIO 14 |
| Fan | GPIO 26 |
| Buzzer | GPIO 25 |
| Curtain Servo | GPIO 13 |
| Red LED | GPIO 16 |
| Green LED | GPIO 17 |
| Yellow LED | GPIO 15 |

### LCD Pins

| LCD Signal | ESP32 Pin |
|---|---:|
| SDA | GPIO 21 |
| SCL | GPIO 22 |

---

## 8. Methodology

The project was developed using the following steps.

### Step 1: Hardware Setup

The sensors and output devices were connected to the ESP32 according to the pin configuration. Analog sensors were connected to ESP32 analog input pins, and output devices were connected to PWM or digital pins.

### Step 2: ESP32 Programming

The ESP32 was programmed using Arduino IDE. The code handles:

- WiFi connection
- MQTT connection
- Sensor reading
- MQTT publishing
- MQTT subscription
- Output control
- Smart mode logic
- Safety logic
- LCD messages

### Step 3: MQTT Topic Design

A topic structure was created using the base topic:

```text
ctrlhome/B6737115
```

This keeps the project organized and allows the dashboard and ESP32 to communicate clearly.

### Step 4: Web Dashboard Development

The web dashboard was created in one HTML file:

```text
index(3).html
```

The dashboard includes four pages:

- Home
- Control
- Mood
- Settings

The dashboard connects to MQTT using MQTT.js over WebSocket.

### Step 5: Testing

The system was tested by checking:

- Sensor values on Serial Monitor
- Sensor values on the web dashboard
- MQTT publishing and subscribing
- Manual controls
- Smart modes
- Emergency safety logic
- LCD notification messages

---

## 9. MQTT Topics

### Sensor Topics

| Topic | Description |
|---|---|
| `ctrlhome/B6737115/temperature` | Temperature value |
| `ctrlhome/B6737115/humidity` | Humidity value |
| `ctrlhome/B6737115/light` | LDR value |
| `ctrlhome/B6737115/motion` | Motion status |
| `ctrlhome/B6737115/gas` | Gas value |
| `ctrlhome/B6737115/water` | Water tank status |
| `ctrlhome/B6737115/potentiometer` | Potentiometer value |
| `ctrlhome/B6737115/alert` | Alert message |
| `ctrlhome/B6737115/currentmode` | Current mode |

### Control Topics

| Topic | Description |
|---|---|
| `ctrlhome/B6737115/mode` | Smart mode command |
| `ctrlhome/B6737115/light/control` | Light brightness command |
| `ctrlhome/B6737115/fan/control` | Fan speed command |
| `ctrlhome/B6737115/curtain/control` | Curtain angle command |
| `ctrlhome/B6737115/alarm/control` | Alarm command |

### Status Topics

| Topic | Description |
|---|---|
| `ctrlhome/B6737115/status/light` | Current light status |
| `ctrlhome/B6737115/status/fan` | Current fan status |
| `ctrlhome/B6737115/status/curtain` | Current curtain position |
| `ctrlhome/B6737115/status/rgb` | Current LED status |
| `ctrlhome/B6737115/status/alarm` | Current alarm status |

---

## 10. Web Dashboard Description

The dashboard is designed as a mobile-friendly smart home controller.

### Home Page

The Home page shows:

- Current mode
- Temperature
- Humidity
- Alert message
- Live readings
- Output status

### Control Page

The Control page allows manual control of:

- Main light
- Fan
- Curtain
- Mood LEDs
- Alarm

### Mood Page

The Mood page allows the user to create a custom mood using:

- Brightness
- LED colors
- Fan speed
- Curtain position
- Preferred temperature
- Alarm monitoring

### Settings Page

The Settings page allows the user to change:

- MQTT broker URL
- Device ID
- Notification setting
- Theme setting

---

## 11. Smart Mode Functions

The project includes several smart modes.

| Mode | Description |
|---|---|
| Sleep | Turns off main light, uses low fan, closes curtain, and uses yellow LED |
| Study | Sets bright light, medium fan, opens curtain, and turns on all mood LEDs |
| Relax | Uses soft light, low fan, medium curtain position, and green/yellow LEDs |
| Away | Turns off devices and waits for motion detection |
| Energy | Saves power by reducing light and fan usage |
| Emergency | Turns on alarm, full light, high fan, open curtain, and blinking red LED |
| Comfort | Uses custom settings selected by the user |

---

## 12. Autonomous Intelligence

The autonomous intelligence of this project means the system can make decisions without the user pressing buttons.

### Examples

| Condition | Automatic Action |
|---|---|
| Gas value is too high | Activates Emergency Mode |
| Motion detected in Away Mode | Activates Emergency Mode |
| Temperature is too high | Sends alert |
| Humidity is too high | Sends alert |
| Water tank is full | Sends alert |
| Energy Mode with no motion | Turns off light and fan |
| Sleep Mode with motion | Turns on dim light |

This makes the project more than just a remote control system. It can respond intelligently to the environment.

---

## 13. Sensor Thresholds

The project uses these threshold values:

| Parameter | Threshold |
|---|---:|
| High temperature | 35°C |
| High humidity | 80% |
| High gas value | 2000 |
| Full water tank | 90% |

---

## 14. Results and Testing

### Temperature and Humidity Test

The DHT11 sensor successfully measured temperature and humidity. The values were published to MQTT and displayed on the dashboard.

### Light Sensor Test

The LDR sensor successfully detected light level changes. The dashboard converted the analog value into readable labels:

- Bright
- Dim
- Dark

### Gas Sensor Test

The MQ-2 sensor value was displayed on the dashboard as:

- Safe
- Warning
- Danger

When the gas value exceeded the dangerous threshold, the ESP32 activated Emergency Mode.

### Water Level Test

The water sensor value was converted into percentage and shown as a water tank status. The dashboard displayed the tank level as a loading bar.

### Potentiometer Test

The potentiometer value was converted into a percentage on the dashboard. In Manual Mode, the potentiometer was used to control light brightness.

### Manual Control Test

The dashboard successfully sent MQTT commands to control:

- Light brightness
- Fan speed
- Curtain angle
- Alarm
- Mood LEDs

### Smart Mode Test

Each smart mode successfully changed multiple outputs at the same time.

### Emergency Mode Test

Emergency Mode successfully:

- Turned on the main light
- Set fan to high
- Opened curtain
- Turned on buzzer
- Blinked red LED
- Sent emergency alert to dashboard and LCD

---

## 15. Results Analysis

The project successfully demonstrates a working IoT smart home system. The MQTT communication allowed real-time data transfer between ESP32 and the web dashboard. The dashboard made the project easier to use because the user can monitor and control the system from a phone or laptop browser.

The smart mode system improved the project because one command can control multiple outputs. For example, Study Mode adjusts light, fan, curtain, and LEDs automatically. Emergency Mode is important because it shows how IoT can be used for safety.

The system also shows the difference between remote connectivity and autonomous intelligence. Remote connectivity allows the user to control the device from the dashboard. Autonomous intelligence allows the ESP32 to react by itself when sensor values reach unsafe conditions.

The main limitation is that the project uses a public MQTT broker. This is good for testing, but a real product should use a private broker with authentication for better security. Another limitation is that sensor values are not saved in a database, so the system does not show history charts.

---

## 16. Problems and Solutions

| Problem | Solution |
|---|---|
| Browser cannot connect to normal MQTT TCP | Used MQTT over WebSocket |
| Need same topic names on ESP32 and dashboard | Used common base topic `ctrlhome/B6737115` |
| Sensor values are difficult to understand | Converted raw values into labels such as Safe, Warning, Danger, Bright, Dim, Dark |
| Too many controls can confuse user | Organized dashboard into Home, Control, Mood, and Settings pages |
| Emergency alert must be noticeable | Used buzzer, blinking red LED, LCD, and dashboard alert |
| Manual and automatic control can conflict | Control commands switch system back to Manual Mode |

---

## 17. Learning Outcomes

From this project, we learned how to:

- Program ESP32 using Arduino IDE
- Connect ESP32 to WiFi
- Use MQTT publish and subscribe communication
- Connect a web dashboard to MQTT using WebSocket
- Read analog and digital sensors
- Control PWM outputs
- Control a servo motor
- Display information on an I2C LCD
- Create a mobile-friendly dashboard using HTML, CSS, and JavaScript
- Build smart mode automation
- Implement safety alert logic

---

## 18. Future Improvements

The project can be improved by adding:

- User login system
- Private MQTT broker
- Sensor history database
- Real-time charts
- Push notifications
- Cloud hosting
- Node-RED dashboard integration
- Mobile app version
- Voice assistant control
- Better enclosure for hardware
- More sensors such as flame, sound, or dust sensor

---

## 19. Conclusion

The Ctrl+Home Smart Home IoT project successfully demonstrates a complete IoT system using ESP32, MQTT, sensors, output devices, and a web dashboard. The system can monitor environmental data in real time, allow remote control, and make automatic decisions based on sensor readings.

The project meets the important requirements of an IoT system: sensing, connectivity, control, and automation. It also shows how IoT can improve home comfort, safety, and energy efficiency.

Overall, Ctrl+Home is a practical educational project that combines hardware and software into one working smart home system.

---

## 20. References

- ESP32 Arduino Core
- PubSubClient MQTT Library
- MQTT.js Library
- HiveMQ Public MQTT Broker
- Arduino DHT Sensor Library
- ESP32Servo Library
- LiquidCrystal_I2C Library
