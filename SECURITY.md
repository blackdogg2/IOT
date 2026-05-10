# Security Policy

## 1. Important Warning

This project is for **education and demonstration**.

Before uploading to GitHub, make sure you do not upload private information such as:

- Real WiFi name
- Real WiFi password
- Private MQTT username
- Private MQTT password
- API keys
- Home address
- Private IP address
- Personal phone number
- Personal location
- Screenshots showing private data

---

## 2. WiFi Credentials

In `IOT_project.ino`, WiFi credentials should not contain your real information.

Use placeholders:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

Do not upload this:

```cpp
const char* ssid = "MyRealWiFi";
const char* password = "MyRealPassword123";
```

---

## 3. Recommended `.gitignore`

Create a `.gitignore` file in the root folder:

```gitignore
config.h
secrets.h
credentials.h
.env
*.env
.DS_Store
```

This helps prevent private files from being uploaded.

---

## 4. Safer Credential Method

For better security, private credentials can be stored in a separate file:

```text
config.h
```

Example:

```cpp
#ifndef CONFIG_H
#define CONFIG_H

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

#endif
```

Then include it in `IOT_project.ino`:

```cpp
#include "config.h"
```

Do not upload `config.h`.

---

## 5. MQTT Security

This project uses the public HiveMQ broker:

```text
broker.hivemq.com
```

ESP32 MQTT:

```text
broker.hivemq.com:1883
```

Dashboard MQTT WebSocket:

```text
wss://broker.hivemq.com:8884/mqtt
```

A public MQTT broker is good for testing, but it is not secure for real home use.

Anyone who knows your topic can publish or subscribe.

Example public topic:

```text
ctrlhome/B6737115/light/control
```

---

## 6. Safer MQTT Recommendations

For real deployment, use:

- Private MQTT broker
- Username and password
- TLS encryption
- Random device ID
- Access control list
- Private topics
- Broker authentication

Safer topic example:

```text
ctrlhome/device_a92f7x/home/temperature
```

---

## 7. Dashboard Security

The dashboard file is:

```text
index.html
```

Anything inside HTML, CSS, or JavaScript can be seen by users.

Do not put secrets in:

- `index.html`
- JavaScript variables
- Browser localStorage
- GitHub Pages frontend code

---

## 8. Screenshot Safety

Before uploading screenshots, check that they do not show:

- WiFi password
- Personal messages
- Private location
- Private broker credentials
- Personal accounts

---

## 9. Hardware Safety

This project should only use low-voltage educational components.

Do not connect ESP32 directly to high-voltage home appliances.

For real AC appliances, use:

- Proper relay module
- Electrical isolation
- Fuse protection
- Correct enclosure
- Supervision from a qualified person

Unsafe wiring can cause electric shock, fire, or device damage.

---

## 10. Public GitHub Checklist

Before pushing to GitHub:

- [ ] WiFi name is removed or replaced
- [ ] WiFi password is removed or replaced
- [ ] No private MQTT password is included
- [ ] No API key is included
- [ ] No private IP address is included
- [ ] No home address is included
- [ ] Screenshots are safe
- [ ] `.gitignore` exists
- [ ] Public broker is clearly described as testing only
- [ ] `README.md` explains project usage
- [ ] Report files do not contain private data

---

## 11. Supported Use

| Use Case | Status |
|---|---|
| Classroom demonstration | Supported |
| GitHub portfolio | Supported |
| Public MQTT testing | Supported with caution |
| Real home deployment | Not recommended without security upgrades |

---

## 12. Security Summary

For GitHub:

```text
Remove secrets
Use placeholders
Add .gitignore
Check screenshots
Use public broker only for demo
```

For real use:

```text
Use private MQTT broker
Use authentication
Use TLS
Use random topics
Protect hardware safely
```

---

## Disclaimer

This project is for educational purposes only.  
The author is not responsible for damage caused by unsafe wiring, leaked credentials, or insecure deployment.
