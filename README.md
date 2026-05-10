# Ctrl+Home Smart Home IoT Project

Ctrl+Home is an ESP32 based smart home controller with a mobile web dashboard. The system reads room and safety sensors, publishes live readings through MQTT, and controls home outputs such as a light, fan, curtain servo, buzzer alarm, LCD, and mood LEDs.

## Main Features

- Live dashboard for temperature, humidity, light level, motion, gas/smoke, water tank level, potentiometer level, LCD state, and output status.
- MQTT control through the topic namespace `ctrlhome/B6737115/...`.
- Smart modes: Manual, Sleep, Study, Relax, Away, Energy, Emergency, and Custom Mood.
- Demo mode in the web app for presentations without hardware.
- Exportable app snapshot as JSON for output evidence.
- Phone/browser notifications for safety alerts.
- ESP32 availability topic with MQTT Last Will so the dashboard can detect when the board goes offline.
- Non-blocking WiFi/MQTT reconnect behavior in the ESP32 loop.

## Project Files

| File | Purpose |
| --- | --- |
| `ctrlhome_FINAL_sensor_display_fixed_light.html` | Mobile web app dashboard and controller |
| `IOT_project/IOT_project.ino` | ESP32 firmware |
| `IoT-diagram.png` | Existing architecture or wiring diagram |
| `deliverables/CtrlHome_Project_Report.md` | Full project report |
| `deliverables/CtrlHome_Presentation_Slides.md` | Slide content for presentation |
| `deliverables/Contribution_Form.md` | Fillable contribution form |
| `deliverables/App_Output_and_Test_Evidence.md` | Demo outputs and test evidence |
| `deliverables/MQTT_Topic_Map.md` | MQTT topic reference |
| `deliverables/ESP32_Firmware_Guide.md` | Firmware setup and behavior guide |

## Hardware

- ESP32 development board
- DHT11 temperature and humidity sensor
- LDR light sensor
- PIR motion sensor
- MQ-2 gas/smoke sensor
- Water level sensor
- Potentiometer
- Servo motor for curtain
- DC fan module or fan driver
- Main light LED or relay driver
- Red, green, and yellow mood LEDs
- Buzzer
- 16x2 I2C LCD

## Quick Start

1. Open `IOT_project/IOT_project.ino` in the Arduino IDE.
2. Install the libraries: `PubSubClient`, `DHT sensor library`, `ESP32Servo`, and `LiquidCrystal_I2C`.
3. Update `ssid` and `password` in the firmware to match your WiFi.
4. Upload the sketch to the ESP32.
5. Open `ctrlhome_FINAL_sensor_display_fixed_light.html` in a browser.
6. Keep the default broker as `wss://broker.hivemq.com:8884/mqtt` and the device ID as `B6737115`.
7. Use Demo mode if the ESP32 is not available during presentation.
