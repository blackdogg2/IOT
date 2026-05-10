# Smart Home Monitoring and Automation System Using ESP32, MQTT, and Node-RED

**Final Year IoT Project Report**  
**Project short name:** Ctrl+Home Smart Monitoring  
**Core platform:** ESP32, MQTT broker, Node-RED, WebSocket dashboard  
**Prepared for:** University final project presentation and viva defense  
**Date:** May 2026

---

## Abstract

This project presents a smart home monitoring and automation system based on Internet of Things technology. The system uses an ESP32 microcontroller to collect environmental readings from a DHT sensor, LDR light sensor, gas sensor, water level sensor, and potentiometer. The ESP32 publishes real-time sensor data through the MQTT protocol to a broker, where Node-RED subscribes to the topics, processes the values, and visualizes them on a dashboard. The dashboard provides live monitoring, safety alerts, and remote control of home devices such as lights, fan, curtain servo, mood LEDs, and alarm buzzer.

The main purpose of the project is to improve home safety, comfort, and convenience through automatic decision-making. For example, the system can detect a dark environment and increase lighting, identify dangerous gas levels and activate an emergency warning, show water tank level as a percentage, classify room comfort from temperature, and display light and gas conditions as readable statuses. A custom HTML/CSS/JavaScript dashboard is also included to demonstrate a modern mobile-friendly interface with WebSocket-based live updates.

The prototype demonstrates how affordable IoT hardware, lightweight communication protocols, and low-code software tools can be combined to create a practical smart home solution suitable for university-level engineering study.

**Keywords:** IoT, ESP32, MQTT, Node-RED, WebSocket, smart home, automation, dashboard, sensors.

---

## 1. Introduction

Smart home technology allows household devices and environmental sensors to be connected through the internet so users can monitor and control their home remotely. Traditional home systems often require manual operation. A user must switch lights manually, check tank level manually, and respond to safety problems only after noticing them. This project solves these limitations by designing a connected monitoring and automation system that can read sensor values, make decisions, send alerts, and accept remote user commands.

The project is built around the ESP32 because it provides WiFi connectivity, enough GPIO pins, analog inputs, and strong community library support. The ESP32 reads sensor data and publishes it to an MQTT broker. MQTT is suitable for IoT because it is lightweight and works well for small messages such as temperature, humidity, gas value, and device status. Node-RED is used as a flow-based platform to subscribe to MQTT topics, process messages, build dashboards, and connect the system with a custom WebSocket interface.

The final system is designed for real-time monitoring and simple automated actions. It can show live environmental conditions, display sensor percentage indicators, control actuators remotely, and trigger safety warnings when abnormal conditions are detected.

---

## 2. Background and Significance

IoT systems are becoming increasingly important in homes, schools, offices, and industries because they provide visibility into physical environments. In a smart home, IoT can reduce energy waste, improve comfort, and detect hazards earlier than manual observation.

This project is significant because it combines monitoring and automation in one prototype:

- **Monitoring:** The user can view temperature, humidity, light intensity, gas level, water tank level, potentiometer value, mode status, and alert messages.
- **Automation:** The system can automatically respond to environmental readings, such as turning on lights in dark conditions or triggering emergency mode when gas level is too high.
- **Remote access:** MQTT and Node-RED allow readings and commands to move between the ESP32 and user dashboard over the network.
- **Low-cost implementation:** The hardware is based on common and affordable sensors, making the system practical for student implementation.
- **Scalability:** The MQTT topic structure can be expanded to additional rooms, sensors, and actuators.

The project demonstrates an engineering workflow that includes circuit design, embedded programming, communication protocol design, dashboard design, testing, and documentation.

---

## 3. Problem Statement

Many homes still rely on manual monitoring and manual control for environmental safety and comfort. Users may not notice dangerous gas levels, high room temperature, full water tanks, or poor lighting conditions immediately. They may also need to be physically present to control devices such as lights, fans, alarms, or curtains.

The problem can be summarized as follows:

- Environmental data is not always visible to the user in real time.
- Manual device control is inconvenient when the user is away from home.
- Safety issues such as gas leakage require fast alerts and automatic response.
- Water tank level and room comfort are difficult to track without a clear dashboard.
- Basic sensor projects often display raw values only, without readable status labels or practical automation.

Therefore, this project proposes an IoT-based smart home system that monitors multiple sensors, communicates through MQTT, visualizes information through Node-RED and a modern dashboard, and performs automatic actions based on defined rules.

---

## 4. Project Objectives

1. To design and develop a smart home monitoring system using IoT technology.
2. To implement real-time data communication between ESP32 and dashboard using MQTT protocol.
3. To develop an intelligent automation system capable of making autonomous decisions based on sensor readings.
4. To provide remote monitoring and control accessibility through web and mobile interfaces.
5. To improve home safety and convenience through smart environmental monitoring and alert systems.
6. To visualize sensor data in a user-friendly dashboard with real-time updates.

---

## 5. Scope of Project

The project focuses on a single smart home prototype using one ESP32 board and multiple sensors. The system is designed for monitoring, visualization, and device control.

### Included in scope

- ESP32 reads DHT temperature and humidity values.
- ESP32 reads analog LDR light intensity.
- ESP32 reads analog gas sensor value for safety monitoring.
- ESP32 reads analog water level sensor value and converts it to percentage.
- ESP32 reads potentiometer value for simulation and manual control input.
- ESP32 publishes sensor values to MQTT topics.
- ESP32 subscribes to MQTT control topics.
- Node-RED subscribes to MQTT topics and displays values on a dashboard.
- WebSocket can be used to send live data from Node-RED to a custom web dashboard.
- Dashboard displays real-time readings, statuses, charts, water tank animation, and actuator controls.
- Smart rules classify comfort, light condition, gas condition, and water level condition.
- Safety alerts are generated for dangerous conditions.

### Outside current scope

- Commercial-grade electrical relay isolation.
- Full mobile app deployment through app stores.
- Long-term cloud database storage.
- Machine learning prediction.
- Multi-user authentication and access control.
- Final enclosure and industrial PCB design.

These items are suitable future improvements after the prototype is verified.

---

## 6. Literature Review

### 6.1 Internet of Things in Smart Homes

The Internet of Things connects physical devices to digital systems through sensors, networks, and software services. In smart homes, IoT allows environmental conditions to be measured and acted upon automatically. Examples include smart lighting, climate monitoring, gas leak detection, water tank monitoring, and remote appliance control.

### 6.2 ESP32 as IoT Controller

The ESP32 is widely used in student and prototype IoT projects because it combines WiFi connectivity, digital input/output pins, analog input channels, PWM output, and sufficient processing capability. In this project, the ESP32 works as the edge controller. It directly reads sensors and controls actuators while also communicating with network services.

### 6.3 MQTT Protocol

MQTT is a lightweight messaging protocol designed for low-bandwidth and resource-constrained devices. It uses a publish and subscribe model. A device does not send a message directly to another device. Instead, it publishes a message to a topic on an MQTT broker. Any client subscribed to that topic receives the message. This makes the design flexible because ESP32, Node-RED, and dashboards can exchange messages without tightly depending on each other.

### 6.4 Node-RED

Node-RED is a visual flow-based programming tool. It is useful in IoT projects because MQTT nodes, function nodes, dashboard nodes, and WebSocket nodes can be connected graphically. This reduces development time and helps students demonstrate data flow clearly.

### 6.5 WebSocket for Live Dashboards

WebSocket is a communication method that keeps a live connection between browser and server. Unlike a normal HTTP request, where the browser asks and the server responds once, WebSocket allows continuous two-way communication. This is useful for dashboards because sensor readings can update instantly without refreshing the page.

---

## 7. Methodology

The project was developed using a staged engineering methodology.

### 7.1 Requirement Analysis

The required features were identified first:

- Monitor temperature, humidity, light, gas, water level, and potentiometer input.
- Display values in real time.
- Provide clear statuses such as Bright, Dim, Dark, Safe, Warning, Danger, and Comfort.
- Allow user control of light, fan, curtain, mood LEDs, and alarm.
- Trigger automatic rules for safety and convenience.
- Use MQTT and Node-RED for communication and visualization.

### 7.2 Hardware Design

The ESP32 was selected as the main controller. Sensors were connected to suitable digital and analog pins. Actuators were connected to output pins using PWM or digital control. The water level and gas sensors use analog input values, while the DHT sensor uses a digital data pin.

### 7.3 Embedded Software Design

The Arduino sketch initializes WiFi, MQTT, sensors, outputs, LCD, and servo. The ESP32 publishes sensor data approximately every 2.5 seconds. It also subscribes to control topics so the dashboard can change mode and actuator states. The callback function checks incoming MQTT commands and updates outputs.

### 7.4 Communication Design

MQTT topics are organized under:

```text
ctrlhome/B6737115/
```

This root topic keeps all project messages grouped under one device ID. Sensor topics are used for readings, control topics are used for commands, and status topics are used for output feedback.

### 7.5 Dashboard Design

Two dashboard layers are proposed:

- **Node-RED dashboard:** Fast visual dashboard using dashboard nodes, charts, gauges, switches, and alert indicators.
- **Custom modern dashboard:** A polished HTML/CSS/JavaScript interface that receives live data through WebSocket and can send commands back.

### 7.6 Testing

Each sensor and actuator is tested individually. After that, MQTT communication is tested using topic publish and subscribe. Finally, smart automation rules are tested using different sensor conditions.

---

## 8. System Architecture

The system uses a layered architecture:

1. **Sensor layer:** DHT, LDR, gas sensor, water level sensor, potentiometer, and optional motion sensor collect physical data.
2. **Edge controller layer:** ESP32 reads sensors, applies rules, controls outputs, and publishes data.
3. **Communication layer:** MQTT broker transfers messages between ESP32 and Node-RED.
4. **Processing layer:** Node-RED subscribes to sensor topics, formats readings, handles dashboard logic, and forwards live updates.
5. **Application layer:** Web dashboard and smartphone browser show live status and allow commands.
6. **Actuator layer:** Lights, fan, curtain servo, mood LEDs, buzzer, and LCD respond to rules and commands.

![System architecture](../diagrams/system_architecture.svg)

### Simple architecture explanation

The ESP32 is the brain of the hardware. Sensors send electrical signals to the ESP32. The ESP32 converts those signals into values such as temperature, humidity, gas level, and tank percentage. Then it sends those values to the MQTT broker. Node-RED listens to those MQTT topics and displays the data. When the user presses a dashboard button, Node-RED publishes a command topic back to the MQTT broker. The ESP32 receives that command and changes the output device.

---

## 9. Hardware Components

| Component | Function in project | Signal type |
|---|---|---|
| ESP32 | Main IoT controller with WiFi and GPIO | Digital, analog, PWM |
| DHT11/DHT sensor | Measures temperature and humidity | Digital |
| LDR sensor | Measures light intensity | Analog |
| MQ-2/Gas sensor | Detects gas or smoke level | Analog |
| Water level sensor | Measures tank level | Analog |
| Potentiometer | Simulates manual input or brightness control | Analog |
| PIR motion sensor | Optional motion detection included in current sketch | Digital |
| Servo motor | Simulates curtain movement | PWM signal |
| Fan output | Simulates ventilation control | PWM signal |
| LED/light output | Simulates room lighting | PWM signal |
| Mood LEDs | Red, green, yellow status lighting | PWM output |
| Buzzer | Alarm output for safety warning | Digital |
| I2C LCD | Local display for status and alert messages | I2C |

### ESP32 pin mapping used in the current sketch

| Function | ESP32 pin |
|---|---:|
| DHT sensor | GPIO 4 |
| LDR sensor | GPIO 34 |
| PIR motion sensor | GPIO 27 |
| Gas sensor | GPIO 35 |
| Water level sensor | GPIO 32 |
| Potentiometer | GPIO 39 |
| Main light output | GPIO 14 |
| Fan output | GPIO 26 |
| Buzzer output | GPIO 25 |
| Curtain servo | GPIO 13 |
| Mood red LED | GPIO 16 |
| Mood green LED | GPIO 17 |
| Mood yellow LED | GPIO 15 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

---

## 10. Software Components

| Software | Purpose |
|---|---|
| Arduino IDE / ESP32 Arduino core | Used to program the ESP32 |
| WiFi library | Connects ESP32 to wireless network |
| PubSubClient | MQTT client library for ESP32 |
| DHT library | Reads DHT temperature and humidity sensor |
| ESP32Servo library | Controls servo motor for curtain simulation |
| LiquidCrystal_I2C | Displays local messages on I2C LCD |
| MQTT broker | Receives and distributes project messages |
| Node-RED | Processes MQTT messages and builds dashboard flows |
| WebSocket | Sends live dashboard updates without page refresh |
| HTML/CSS/JavaScript | Builds the custom modern dashboard UI |

---

## 11. Circuit Explanation

The ESP32 is powered through USB during development. The DHT sensor data pin is connected to GPIO 4. Analog sensors are connected to ADC-capable pins. The LDR, gas sensor, water level sensor, and potentiometer produce analog voltages that the ESP32 reads as values from 0 to 4095.

The main light, fan, mood LEDs, and buzzer are connected to output pins. PWM outputs are used where variable intensity or speed is needed. For example, the main light brightness is controlled with a value from 0 to 255. The fan can be set to off, low, medium, or high by mapping these modes to PWM values. The curtain is represented by a servo motor connected to GPIO 13, with movement from 0 to 180 degrees.

The I2C LCD uses SDA on GPIO 21 and SCL on GPIO 22. It displays standby mode, notifications, and safety messages. In a real home installation, output devices such as AC lights or fans should use proper relay modules, opto-isolation, external power supply, fuses, and safe enclosure design. For a university prototype, LEDs, small DC fan, buzzer, and servo are safer demonstration loads.

---

## 12. MQTT Communication Explanation

### 12.1 What MQTT means in simple words

MQTT is like a message post office for IoT devices. The ESP32 does not need to know exactly where the dashboard is. It only sends messages to a topic, such as:

```text
ctrlhome/B6737115/temperature
```

The MQTT broker receives the message. Any client that subscribes to the same topic receives the value. Node-RED and the dashboard can subscribe to the topic and display it immediately.

### 12.2 MQTT broker

The current sketch uses:

```text
broker.hivemq.com
port 1883
```

For demonstration, a public broker is convenient. For production or private deployment, a private MQTT broker with authentication should be used.

### 12.3 MQTT data flow

![MQTT data flow](../diagrams/mqtt_data_flow.svg)

### 12.4 Sensor publish topics

| Topic | Direction | Payload example | Purpose |
|---|---|---|---|
| `ctrlhome/B6737115/temperature` | ESP32 to broker | `28.40` | Room temperature |
| `ctrlhome/B6737115/humidity` | ESP32 to broker | `61.00` | Room humidity |
| `ctrlhome/B6737115/light` | ESP32 to broker | `1460` | LDR analog value |
| `ctrlhome/B6737115/motion` | ESP32 to broker | `Motion Detected` | PIR status |
| `ctrlhome/B6737115/gas` | ESP32 to broker | `650` | Gas sensor analog value |
| `ctrlhome/B6737115/water` | ESP32 to broker | `Tank Medium (68% filled)` | Water tank status |
| `ctrlhome/B6737115/potentiometer` | ESP32 to broker | `2200` | Simulation input |
| `ctrlhome/B6737115/alert` | ESP32 to broker | `All sensors normal` | Safety alert text |
| `ctrlhome/B6737115/currentmode` | ESP32 to broker | `manual` | Current mode |

### 12.5 Control subscribe topics

| Topic | Direction | Payload example | ESP32 action |
|---|---|---|---|
| `ctrlhome/B6737115/mode` | Dashboard to ESP32 | `study` | Apply smart mode |
| `ctrlhome/B6737115/light/control` | Dashboard to ESP32 | `255` or `ON` | Change light brightness |
| `ctrlhome/B6737115/fan/control` | Dashboard to ESP32 | `medium` | Change fan speed |
| `ctrlhome/B6737115/curtain/control` | Dashboard to ESP32 | `140` | Move servo curtain |
| `ctrlhome/B6737115/alarm/control` | Dashboard to ESP32 | `ON` | Turn buzzer alarm on |
| `ctrlhome/B6737115/custom/brightness` | Dashboard to ESP32 | `150` | Custom comfort brightness |
| `ctrlhome/B6737115/custom/rgb` | Dashboard to ESP32 | `255,0,0` | Mood LED command |
| `ctrlhome/B6737115/custom/fan` | Dashboard to ESP32 | `low` | Custom comfort fan |
| `ctrlhome/B6737115/custom/curtain` | Dashboard to ESP32 | `90` | Custom curtain angle |
| `ctrlhome/B6737115/custom/alarm` | Dashboard to ESP32 | `ON` | Custom alarm setting |
| `ctrlhome/B6737115/custom/temp` | Dashboard to ESP32 | `25` | Custom target temperature |

---

## 13. Node-RED Explanation

Node-RED acts as the visual logic and dashboard layer. It can be explained simply as a flow chart that actually runs.

The typical Node-RED flow is:

1. MQTT input nodes subscribe to ESP32 sensor topics.
2. Function nodes convert raw payloads into clean dashboard values.
3. Dashboard gauge and chart nodes show the readings.
4. Function nodes classify statuses such as Safe, Warning, Danger, Bright, Dim, and Dark.
5. WebSocket output node forwards live JSON data to the modern dashboard.
6. Dashboard buttons or WebSocket input nodes receive user commands.
7. MQTT output nodes publish command messages back to ESP32.

![Node-RED workflow](../diagrams/node_red_workflow.svg)

### Recommended Node-RED dashboard widgets

| Widget | Data |
|---|---|
| Gauge | Temperature, humidity, gas percentage, water tank percentage |
| Text status | Light condition, gas condition, room comfort, current mode |
| Chart | Temperature and gas history |
| Switch | Light, fan, alarm |
| Slider | Light brightness, curtain angle |
| Notification | Safety alert messages |

---

## 14. WebSocket Explanation

WebSocket is used for the modern dashboard because it allows the browser and Node-RED to stay connected continuously. With normal web requests, the browser must repeatedly ask for new data. With WebSocket, Node-RED can push new readings to the dashboard immediately when they arrive.

### Simple WebSocket workflow

1. Browser dashboard opens.
2. Dashboard connects to Node-RED WebSocket endpoint, for example:

```text
ws://localhost:1880/ws/smart-home
```

3. Node-RED sends JSON messages such as:

```json
{
  "temperature": 28.4,
  "humidity": 61,
  "light": 1460,
  "gas": 650,
  "waterPercent": 68,
  "mode": "manual",
  "alert": "All sensors normal"
}
```

4. Dashboard updates cards, charts, badges, and water tank animation.
5. When the user controls a device, the dashboard sends a command message back to Node-RED.
6. Node-RED converts the command into an MQTT publish message for ESP32.

---

## 15. Dashboard UI Explanation

The dashboard is designed to be professional, modern, and readable during a viva presentation. It uses a dark engineering style with blue accents for live data and red accents for danger states.

Main dashboard sections:

- **System summary:** Shows overall system health, current mode, and latest alert.
- **Sensor cards:** Shows temperature, humidity, light, gas, water tank, and potentiometer readings.
- **Percentage indicators:** Humidity, gas, water, and potentiometer values are visualized as bars or rings.
- **Water tank animation:** The tank fill height changes based on water percentage.
- **Condition badges:** Temperature comfort, light condition, gas condition, and tank status are shown as readable labels.
- **Control center:** Allows changing smart mode, light brightness, fan speed, curtain position, and alarm state.
- **Live chart:** Displays recent temperature and gas trends.
- **Activity log:** Shows dashboard events, commands, and WebSocket status.

The dashboard is mobile-friendly and works in demo mode even without Node-RED. This makes it suitable for presentation if hardware is not connected at the exact time of demonstration.

Dashboard file:

```text
deliverables/dashboard/ctrlhome_dashboard.html
```

---

## 16. Smart Automation Logic

![Automation flow](../diagrams/automation_flow.svg)

### 16.1 Safety thresholds used in the current sketch

| Condition | Threshold | Action |
|---|---:|---|
| High temperature | `>= 35 deg C` | Publish high temperature alert |
| High humidity | `>= 80%` | Publish humidity warning |
| Gas danger | `> 2000 ADC` | Emergency mode, alarm, warning lights |
| Water tank full | `>= 90%` | Publish water full notification |
| Dark environment in energy mode | `< 1200 ADC` | Increase light brightness |

### 16.2 Mode behavior

| Mode | Behavior |
|---|---|
| Manual | User controls outputs directly. Potentiometer can map to light brightness. |
| Sleep | Light off or dim on motion, fan low or medium depending on temperature. |
| Study | Bright light, medium fan, curtain opened for study environment. |
| Relax | Lower light, low fan, partial curtain position. |
| Away | Outputs off, curtain closed, motion can trigger security alert. |
| Energy | Saves energy by adjusting light and fan based on motion and environment. |
| Emergency | Alarm on, fan high, curtain open, warning lights active. |
| Comfort | Uses custom brightness, fan, curtain, alarm, and target temperature settings. |

### 16.3 Automation decision explanation

The automation logic is rule-based. This means the ESP32 checks conditions using `if` statements. For example:

- If gas value is greater than the danger threshold, the ESP32 activates emergency mode.
- If water tank percentage is 90 percent or higher, the ESP32 sends a water full notification.
- If temperature is high, the dashboard shows a warning and the fan can increase speed.
- If light value indicates darkness, smart mode can increase brightness.

This approach is simple, reliable, and easy to explain during a viva defense.

---

## 17. Flowcharts

The project includes two useful flowchart views:

1. **Detailed existing project flowchart:** `deliverables/assets/existing-flowchart.png`
2. **Presentation automation flow:** `deliverables/diagrams/automation_flow.svg`

The system starts by powering on the ESP32, initializing sensors and outputs, connecting to WiFi, connecting to MQTT, subscribing to control topics, then continuously reading sensor values and checking safety conditions. If a user command arrives, the MQTT callback function runs and applies the requested output change.

---

## 18. Results and Testing

### 18.1 Test cases

| Test case | Procedure | Expected result | Status |
|---|---|---|---|
| WiFi connection | Power ESP32 with correct SSID and password | ESP32 connects and prints IP address | Passed in design |
| MQTT connection | Connect to broker and subscribe to topics | Broker connection success and subscriptions active | Passed in design |
| Temperature reading | Read DHT sensor | Temperature published to MQTT | Passed in design |
| Humidity reading | Read DHT sensor | Humidity published to MQTT | Passed in design |
| Light condition | Cover and uncover LDR | Dashboard changes Dark, Dim, Bright | Passed in design |
| Gas warning | Simulate high gas analog value | Alert and emergency mode trigger | Passed in design |
| Water tank level | Change water sensor value | Animated water bar and tank status update | Passed in design |
| Light control | Send MQTT light command | Light PWM changes | Passed in design |
| Fan control | Send fan mode command | Fan PWM changes | Passed in design |
| Curtain control | Send servo angle | Servo moves to requested position | Passed in design |
| Alarm control | Send ON/OFF command | Buzzer changes state | Passed in design |
| WebSocket dashboard | Send JSON data from Node-RED | Browser dashboard updates live | Passed in UI logic |

### 18.2 Sample expected dashboard values

| Reading | Example value | Dashboard status |
|---|---:|---|
| Temperature | 28.4 deg C | Comfort |
| Humidity | 61% | Normal |
| LDR | 1460 ADC | Dim |
| Gas | 650 ADC | Safe |
| Water tank | 68% | Medium |
| Potentiometer | 2200 ADC | Input level |

### 18.3 Expected safety result

When gas value exceeds 2000 ADC:

- ESP32 publishes `Gas/Smoke High`.
- Current mode becomes emergency.
- Alarm buzzer turns on.
- Fan switches to high.
- Warning lights activate.
- Dashboard shows danger status.
- LCD shows alert message.

---

## 19. Discussion and Analysis

The project successfully demonstrates the relationship between embedded hardware, IoT communication, and dashboard software. The ESP32 performs important work locally, which is useful because safety decisions should not depend entirely on a remote dashboard. If gas danger is detected, the ESP32 can immediately activate alarm behavior.

MQTT improves system flexibility because each component only needs to know the topic names. Node-RED can be replaced or extended without changing the core sensor code, as long as the topics remain consistent. Similarly, a mobile web dashboard can be added by subscribing to the same data stream.

The rule-based automation is suitable for a university final project because it is understandable, testable, and predictable. Although it is not artificial intelligence in the machine learning sense, it is intelligent decision-making because the system autonomously chooses actions based on sensor values.

The modern dashboard improves presentation quality by converting raw data into meaningful information. Instead of showing only `650` for gas or `1460` for light, it shows Safe or Dim. This makes the system easier for non-technical users to understand.

---

## 20. Challenges Faced

1. **Sensor calibration:** Analog sensors such as gas, water, and LDR can produce different ranges depending on wiring, lighting, and environment. Thresholds must be adjusted during testing.
2. **WiFi reliability:** IoT systems depend on network stability. Reconnection logic is required when WiFi or MQTT disconnects.
3. **MQTT topic organization:** A clear topic structure is important so sensor data and commands do not become confusing.
4. **Dashboard readability:** Raw sensor values need to be converted into user-friendly statuses.
5. **Safety response timing:** Gas or emergency alerts must be handled quickly and should not wait for manual dashboard action.
6. **Power and wiring stability:** Multiple sensors and outputs require clean wiring and stable power during demonstration.
7. **Mobile-friendly design:** Dashboard layout must remain readable on smaller screens.

---

## 21. Future Improvements

- Add user login and authentication for secure remote access.
- Use a private MQTT broker with username, password, and TLS encryption.
- Store historical readings in a database such as InfluxDB, Firebase, or SQLite.
- Add predictive maintenance or anomaly detection using machine learning.
- Add mobile push notifications for gas and security alerts.
- Add relay modules with proper isolation for real appliances.
- Design a custom PCB and enclosure.
- Add camera module integration for security monitoring.
- Add voice assistant support.
- Expand the system to multiple rooms using separate MQTT device IDs.
- Add over-the-air firmware updates for easier maintenance.

---

## 22. Conclusion

The Smart Home Monitoring and Automation System using ESP32, MQTT, and Node-RED provides a complete IoT prototype for real-time home monitoring and remote device control. The ESP32 reads multiple sensors, publishes data to MQTT, receives control commands, and performs autonomous safety actions. Node-RED provides flow-based processing and dashboard integration, while the custom WebSocket dashboard offers a modern and mobile-friendly user interface.

The project meets the main objectives by demonstrating sensor monitoring, MQTT communication, intelligent automation, remote access, safety alerts, and real-time visualization. It is practical, scalable, and suitable for a final year engineering presentation because it includes hardware, software, communication protocol, dashboard design, and automation logic.

---

## 23. Viva Defense Notes

### What is MQTT?

MQTT is a lightweight messaging protocol. The ESP32 publishes messages to topic names, and Node-RED or the dashboard subscribes to those topic names. It is useful for IoT because it sends small messages efficiently.

### What is Node-RED?

Node-RED is a visual programming tool. It connects nodes together to receive MQTT data, process values, show dashboard widgets, and publish commands back to ESP32.

### Why use WebSocket?

WebSocket keeps a live connection between the browser dashboard and Node-RED. This allows sensor values to update immediately without refreshing the page.

### How does ESP32 communicate with Node-RED?

ESP32 connects to WiFi, then connects to the MQTT broker. It publishes sensor readings to MQTT topics. Node-RED subscribes to those topics. When the user sends a command, Node-RED publishes a command topic and ESP32 receives it.

### How do automation decisions work?

The ESP32 compares sensor values with thresholds. If gas value is high, emergency mode is triggered. If the room is dark in smart mode, lights turn on. If temperature is high, the fan can increase speed. These are rule-based decisions.

### What happens from sensor to dashboard?

Sensor value goes to ESP32, ESP32 publishes MQTT message, MQTT broker forwards it to Node-RED, Node-RED formats it, and the dashboard displays it as live cards, charts, and status labels.

---

## 24. References

1. Espressif Systems, ESP32 product and documentation portal: https://www.espressif.com/en/products/socs/esp32
2. OASIS, MQTT Version 3.1.1 Standard: https://docs.oasis-open.org/mqtt/mqtt/v3.1.1/
3. MQTT.org, MQTT protocol overview: https://mqtt.org/
4. Node-RED official documentation: https://nodered.org/docs/
5. Node-RED Cookbook, MQTT examples: https://cookbook.nodered.org/mqtt/
6. MDN Web Docs, WebSocket API: https://developer.mozilla.org/en-US/docs/Web/API/WebSocket
7. Arduino ESP32 documentation: https://docs.espressif.com/projects/arduino-esp32/
8. PubSubClient library documentation: https://pubsubclient.knolleary.net/

