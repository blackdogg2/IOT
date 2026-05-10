# Security Policy

## Project Name

**Ctrl+Home — ESP32 Smart Home IoT Dashboard**

This document explains the security rules and precautions for this project before uploading it to GitHub.

The project includes:

```text
IOT_project(1).ino
index(3).html
README.md
Architecture_Explanation.md
Smart_Home_IoT_Final_Report.md
```

---

## 1. Important Security Notice

This project is made for **educational purposes**. It uses an ESP32, sensors, MQTT communication, and a web dashboard.

Before uploading this project to GitHub, make sure you do **not** upload private information such as:

- Real WiFi name
- Real WiFi password
- Private MQTT username
- Private MQTT password
- Private IP address
- Personal API keys
- Home address
- Personal phone number
- Private device location

---

## 2. WiFi Credential Safety

In the ESP32 code, WiFi credentials may look like this:

```cpp
const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";
```

Before uploading to GitHub, replace your real WiFi credentials with placeholders:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

Do **not** upload your real WiFi password.

---

## 3. Recommended `config.h` Method

For better security, store private credentials in a separate file named:

```text
config.h
```

Example `config.h`:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

#endif
```

Then include it in the ESP32 code:

```cpp
#include "config.h"
```

Use the variables like this:

```cpp
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
```

Do not upload `config.h` to GitHub.

---

## 4. Recommended `.gitignore`

Create a `.gitignore` file and add:

```gitignore
config.h
*.env
.env
secrets.h
credentials.h
```

This prevents private files from being uploaded accidentally.

---

## 5. MQTT Security Warning

This project uses the public HiveMQ broker for testing:

```text
broker.hivemq.com
```

The web dashboard uses:

```text
wss://broker.hivemq.com:8884/mqtt
```

The ESP32 uses:

```text
broker.hivemq.com:1883
```

A public MQTT broker is easy for testing, but it is **not secure for real home use**.

Anyone who knows the MQTT topic can publish or subscribe to the same topic.

Example topic:

```text
ctrlhome/B6737115/light/control
```

If someone knows this topic, they may be able to send commands to your device.

---

## 6. How to Make MQTT Safer

For a real project, use a private MQTT broker with:

- Username and password
- TLS encryption
- Unique topic names
- Access control rules
- Random device ID
- Private server or paid MQTT cloud service

Example safer topic:

```text
ctrlhome/user_8f29a/device_3c91/temperature
```

Avoid simple public topics like:

```text
ctrlhome/B6737115/temperature
```

for real deployment.

---

## 7. Device ID Safety

The dashboard uses a device ID such as:

```text
B6737115
```

This creates the base topic:

```text
ctrlhome/B6737115
```

For public GitHub upload, this is acceptable for a school project, but for real security, use a random device ID.

Example:

```text
ctrlhome/device_a92f7x/home_sensor
```

---

## 8. Web Dashboard Security

The file:

```text
index(3).html
```

runs in the browser and connects to MQTT using MQTT.js.

Because this is frontend code, anything written inside the HTML or JavaScript can be seen by anyone.

Do not put secret information inside:

- HTML
- JavaScript
- CSS
- Browser localStorage
- Public GitHub repository

Frontend code is public by nature.

---

## 9. Browser Notification Safety

The dashboard may ask the user for notification permission.

Only allow notifications if you trust the website location where the dashboard is hosted.

If hosted on GitHub Pages, make sure the repository does not contain private keys or passwords.

---

## 10. Hardware Safety

This project should only be used with low-voltage educational components.

Do not connect the ESP32 directly to high-voltage home appliances.

For real appliances such as AC lamps, fans, or power outlets, use proper relay modules, isolation, fuse protection, and supervision from a qualified person.

Unsafe wiring can cause:

- Electric shock
- Fire
- Device damage
- Short circuit

---

## 11. Public Repository Checklist

Before uploading to GitHub, check the following:

- [ ] WiFi SSID is removed or replaced
- [ ] WiFi password is removed or replaced
- [ ] No private MQTT username is included
- [ ] No private MQTT password is included
- [ ] No personal information is included
- [ ] `config.h` is added to `.gitignore`
- [ ] `.env` files are added to `.gitignore`
- [ ] Real home location is not included
- [ ] Screenshots do not reveal private information
- [ ] MQTT topics are okay for public demo use
- [ ] README explains that the project is for education

---

## 12. Example Safe GitHub Version

For GitHub, credentials should look like this:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";
```

Do not upload this:

```cpp
const char* ssid = "MyRealWiFi";
const char* password = "MyRealPassword123";
```

---

## 13. Reporting Security Issues

If someone finds a security issue in this project, they should not post sensitive details publicly.

Instead, they should contact the project owner privately.

Project owner:

```text
Sokvisal Leng
```

---

## 14. Supported Versions

| Version | Status |
|---|---|
| School project version | Supported |
| Public GitHub demo version | Supported |
| Real home deployment | Not recommended without security upgrades |

---

## 15. Security Summary

This project is safe for learning and demonstration if private credentials are removed before uploading.

For GitHub upload:

```text
Remove passwords
Use placeholders
Add .gitignore
Avoid private data
Use public broker only for testing
```

For real use:

```text
Use private MQTT broker
Use authentication
Use TLS
Use random topics
Protect hardware wiring
```

---

## License and Disclaimer

This project is for educational purposes only.  
The author is not responsible for damage caused by unsafe wiring, leaked credentials, or insecure deployment.
