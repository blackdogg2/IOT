# Smart Home IoT Final Report

## Project Title

**Ctrl+Home — ESP32 Smart Home IoT Dashboard**

---

## 1. Background and Significance

The Internet of Things, or IoT, allows physical devices to connect to the internet, collect data, communicate, and be controlled remotely. IoT is widely used in smart homes, smart cities, healthcare, agriculture, and industrial automation.

A smart home system is a practical example of IoT because it allows users to monitor and control their home environment. Users can check temperature, humidity, light, motion, gas, and water level. They can also control lights, fans, alarms, and curtains from a smartphone or computer.

The **Ctrl+Home** project was created as a smart home IoT system using ESP32, sensors, MQTT, and a web dashboard. The system supports both remote control and autonomous intelligence.

---

## 2. Objectives

The objectives of this project are:

- To build an IoT smart home system using ESP32.
- To monitor sensor values in real time.
- To control smart home outputs from a web dashboard.
- To use MQTT for communication between ESP32 and dashboard.
- To create smart modes for different room situations.
- To detect unsafe conditions such as gas danger or motion in Away Mode.
- To display local messages using an I2C LCD.
- To create a clean and mobile-friendly web interface.

---

## 3. Scope of the Project

### Included

- ESP32 WiFi connection
- MQTT communication
- Sensor monitoring
- Web dashboard
- Manual control
- Smart modes
- Custom mood settings
- Emergency mode
- LCD display
- GitHub-ready project structure

### Not Included

- User login
- Cloud database
- Sensor history charts
- Private MQTT broker
- Real high-voltage appliance installation
- Mobile app package

---

## 4. Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main IoT controller |
| DHT11 | Temperature and humidity |
| LDR | Light detection |
| PIR Sensor | Motion detection |
| MQ-2 Sensor | Gas / smoke detection |
| Water Level Sensor | Water tank monitoring |
| Potentiometer | Manual analog input |
| Servo Motor | Curtain control |
| Buzzer | Alarm output |
| Red LED | Emergency / mood LED |
| Green LED | Mood LED |
| Yellow LED | Mood LED |
| I2C LCD 16x2 | Local display |

---

## 5. Software and Technologies

| Technology | Purpose |
|---|---|
| Arduino IDE | ESP32 programming |
| HTML | Dashboard structure |
| CSS | Dashboard design |
| JavaScript | Dashboard logic |
| MQTT.js | MQTT WebSocket connection |
| PubSubClient | ESP32 MQTT communication |
| HiveMQ Broker | Public MQTT broker for testing |

---

## 6. System Architecture

```text
Sensors → ESP32 → MQTT Broker → Web Dashboard
Web Dashboard → MQTT Broker → ESP32 → Output Devices
```

The ESP32 publishes sensor values to the MQTT broker.  
The dashboard subscribes to those topics and displays the values.  
The dashboard also publishes commands that the ESP32 receives and executes.

---

## 7. Methodology

### Step 1: Hardware Connection

Sensors and output devices were connected to the ESP32 using the assigned GPIO pins.

### Step 2: ESP32 Programming

The ESP32 was programmed in Arduino IDE. The code handles WiFi, MQTT, sensors, outputs, LCD, smart modes, and emergency logic.

### Step 3: MQTT Topic Design

A base topic was created:

```text
ctrlhome/B6737115
```

All sensor and control topics are based on this structure.

### Step 4: Dashboard Development

The dashboard was developed in:

```text
index.html
```

It is hosted using GitHub Pages:

```text
https://blackdogg2.github.io/IOT/
```

It uses HTML, CSS, JavaScript, and MQTT.js.

### Step 5: Testing

Testing was done by checking sensor values, dashboard updates, MQTT commands, output responses, and emergency mode behavior.

---

## 8. Pin Configuration

### Sensors

| Sensor | ESP32 Pin |
|---|---:|
| DHT11 | GPIO 4 |
| LDR | GPIO 34 |
| PIR | GPIO 27 |
| MQ-2 | GPIO 35 |
| Water Level Sensor | GPIO 32 |
| Potentiometer | GPIO 39 |

### Outputs

| Output | ESP32 Pin |
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

## 9. MQTT Configuration

### ESP32 MQTT

```text
Broker: broker.hivemq.com
Port: 1883
```

### Web Dashboard MQTT

```text
Broker URL: wss://broker.hivemq.com:8884/mqtt
```

### Device ID

```text
B6737115
```

### Base Topic

```text
ctrlhome/B6737115
```

---

## 10. MQTT Topics

### Sensor Topics

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

### Control Topics

```text
ctrlhome/B6737115/mode
ctrlhome/B6737115/light/control
ctrlhome/B6737115/fan/control
ctrlhome/B6737115/curtain/control
ctrlhome/B6737115/alarm/control
```

---

## 11. Dashboard Design

The dashboard can be accessed online through GitHub Pages:

```text
https://blackdogg2.github.io/IOT/
```

The dashboard has four main pages.

| Page | Function |
|---|---|
| Home | Shows live data and system status |
| Control | Controls light, fan, curtain, LEDs, and alarm |
| Mood | Creates custom room mood |
| Settings | Configures MQTT, device ID, notification, and theme |

---

## 12. Smart Modes

| Mode | Description |
|---|---|
| Manual | User controls outputs manually |
| Sleep | Quiet room mode |
| Study | Bright room mode |
| Relax | Soft comfort mode |
| Away | Security monitoring mode |
| Energy | Power saving mode |
| Emergency | Safety alert mode |
| Comfort | Custom mood mode |

---

## 13. Autonomous Intelligence

The system can make automatic decisions from sensor readings.

| Condition | Automatic Response |
|---|---|
| High gas value | Activates Emergency Mode |
| Motion detected in Away Mode | Activates Emergency Mode |
| High temperature | Sends alert |
| High humidity | Sends alert |
| Full water tank | Sends alert |
| No motion in Energy Mode | Saves power |
| Motion in Sleep Mode | Adjusts room condition |

---

## 14. Results and Testing

### Sensor Monitoring

The dashboard successfully displayed live values from the ESP32.

### MQTT Communication

The ESP32 and dashboard successfully communicated using the same MQTT topics.

### Manual Control

The dashboard successfully controlled:

- Main light
- Fan
- Curtain
- Mood LEDs
- Alarm

### Smart Modes

Smart modes successfully changed multiple outputs using one command.

### Emergency Mode

Emergency Mode successfully activated the alarm behavior when unsafe conditions occurred.

---

## 15. Results Analysis

The project achieved its main goal of building a complete IoT smart home system. MQTT communication worked well because it allowed the ESP32 and dashboard to exchange data in real time.

The dashboard improved usability because the system can be controlled from a phone or laptop. The smart modes made the system more practical because the user can change the whole room setup with one button.

The safety system made the project stronger because the ESP32 can react automatically without waiting for user input. This shows autonomous intelligence, which is an important part of IoT.

The main limitation is security. The project uses a public MQTT broker, which is good for testing but not recommended for real home deployment.

---

## 16. Problems and Solutions

| Problem | Solution |
|---|---|
| Browser cannot use normal MQTT TCP | Used MQTT over WebSocket |
| Raw sensor data is hard to understand | Converted values into labels and status |
| Many controls can confuse users | Separated UI into Home, Control, Mood, and Settings pages |
| Public MQTT broker is not secure | Added `SECURITY.md` warning and recommendations |
| Emergency event needs attention | Added buzzer, red LED, LCD, and dashboard alert |

---

## 17. Learning Outcomes

From this project, we learned how to:

- Program an ESP32
- Use MQTT publish and subscribe
- Connect a browser dashboard to MQTT using WebSocket
- Read analog and digital sensors
- Control outputs using ESP32
- Use an I2C LCD
- Design a mobile-friendly dashboard
- Build smart automation logic
- Create a GitHub project structure
- Write project documentation

---

## 18. Future Improvements

- Use private MQTT broker
- Add MQTT username and password
- Add TLS encryption
- Add database storage
- Add sensor history charts
- Add user login
- Add mobile app version
- Add Node-RED dashboard
- Add voice assistant control
- Improve hardware enclosure

---

## 19. Conclusion

The Ctrl+Home Smart Home IoT project successfully demonstrates a complete IoT system using ESP32, sensors, MQTT, and a web dashboard. The system can monitor sensor values, control outputs remotely, and respond automatically to unsafe conditions.

The project meets the important IoT concepts of sensing, communication, control, and automation. It is suitable as an educational smart home project and can be improved further for real-world use with better security and cloud storage.

---

## 20. References

- ESP32 Arduino Core
- PubSubClient Library
- MQTT.js Library
- HiveMQ Public Broker
- DHT Sensor Library
- ESP32Servo Library
- LiquidCrystal_I2C Library
