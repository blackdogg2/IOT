# Architecture Explanation

Project: **Smart Home Monitoring and Automation System Using ESP32, MQTT, and Node-RED**

## One-minute explanation

The system is divided into hardware, communication, processing, and dashboard layers. Sensors measure the home environment and send values to the ESP32. The ESP32 publishes those readings to an MQTT broker. Node-RED subscribes to the MQTT topics, formats the data, and displays it on a dashboard. The custom web dashboard can also receive live readings through WebSocket. When the user changes a device setting from the dashboard, Node-RED publishes a command topic back to the broker, and the ESP32 receives the command and updates the output device.

## Layered architecture

![System architecture](../diagrams/system_architecture.svg)

| Layer | Role | Example |
|---|---|---|
| Sensor layer | Measures physical conditions | DHT, LDR, gas, water, potentiometer |
| Edge layer | Reads values and makes immediate decisions | ESP32 automation logic |
| Network layer | Moves messages between devices | WiFi and MQTT broker |
| Processing layer | Formats values and routes commands | Node-RED flows |
| Application layer | Shows data and accepts user actions | Node-RED dashboard and custom HTML dashboard |
| Actuator layer | Performs physical response | Light, fan, curtain servo, buzzer, LCD |

## Data flow from sensor to dashboard

1. The DHT sensor measures temperature and humidity.
2. The LDR, gas sensor, water level sensor, and potentiometer send analog readings to ESP32 ADC pins.
3. ESP32 converts readings into MQTT payloads.
4. ESP32 publishes the payloads to MQTT topics such as `ctrlhome/B6737115/temperature`.
5. MQTT broker receives the message and forwards it to every subscriber.
6. Node-RED receives the message and converts it to dashboard-friendly data.
7. Dashboard updates the card, gauge, chart, status badge, and alert section.

## Control flow from user to device

1. User presses a dashboard button or changes a slider.
2. Dashboard sends a command to Node-RED through WebSocket or a Node-RED UI widget.
3. Node-RED publishes an MQTT command topic such as `ctrlhome/B6737115/light/control`.
4. ESP32 receives the command in its MQTT callback function.
5. ESP32 changes the output pin using PWM, digital output, or servo control.
6. ESP32 publishes output status so the dashboard can show feedback.

## Automation flow

![Automation flow](../diagrams/automation_flow.svg)

The automation is rule-based. This is easy to test and easy to explain:

- If gas value is above 2000, emergency mode starts.
- If water level is 90 percent or higher, the system sends a tank full notification.
- If temperature is high, the dashboard shows warning and fan speed can increase.
- If light level is low, the system can increase lighting in smart mode.
- If the user selects a mode, ESP32 applies a predefined output pattern.

## MQTT flow

![MQTT communication](../diagrams/mqtt_data_flow.svg)

MQTT separates the sender and receiver. ESP32 publishes to a topic. Node-RED subscribes to the topic. This makes the system flexible because more dashboards, databases, or mobile apps can subscribe later without changing the ESP32 sensor code.

## Node-RED workflow

![Node-RED workflow](../diagrams/node_red_workflow.svg)

Node-RED is responsible for:

- Receiving MQTT sensor topics.
- Parsing and formatting payloads.
- Displaying gauges, charts, and alerts.
- Sending live WebSocket updates to the custom dashboard.
- Receiving dashboard commands.
- Publishing MQTT control topics back to ESP32.

## Why this architecture is suitable

- It keeps urgent safety logic on the ESP32.
- MQTT keeps communication lightweight.
- Node-RED makes the system easy to demonstrate and modify.
- WebSocket gives the dashboard live updates.
- The topic structure can be expanded to additional rooms or devices.

