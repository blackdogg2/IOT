#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ================= WIFI + MQTT =================

const char* ssid = "high";
const char* password = "00000000";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Sensor topics
const char* topic_temperature = "ctrlhome/B6737115/temperature";
const char* topic_humidity = "ctrlhome/B6737115/humidity";
const char* topic_light_sensor = "ctrlhome/B6737115/light";
const char* topic_motion = "ctrlhome/B6737115/motion";
const char* topic_gas = "ctrlhome/B6737115/gas";
const char* topic_water = "ctrlhome/B6737115/water";
const char* topic_potentiometer = "ctrlhome/B6737115/potentiometer";
const char* topic_alert = "ctrlhome/B6737115/alert";
const char* topic_currentmode = "ctrlhome/B6737115/currentmode";

// Control topics
const char* topic_mode = "ctrlhome/B6737115/mode";
const char* topic_light_control = "ctrlhome/B6737115/light/control";
const char* topic_fan_control = "ctrlhome/B6737115/fan/control";
const char* topic_curtain_control = "ctrlhome/B6737115/curtain/control";
const char* topic_alarm_control = "ctrlhome/B6737115/alarm/control";

// Custom mood topics
const char* topic_custom_brightness = "ctrlhome/B6737115/custom/brightness";
const char* topic_custom_rgb = "ctrlhome/B6737115/custom/rgb";
const char* topic_custom_fan = "ctrlhome/B6737115/custom/fan";
const char* topic_custom_curtain = "ctrlhome/B6737115/custom/curtain";
const char* topic_custom_alarm = "ctrlhome/B6737115/custom/alarm";
const char* topic_custom_temp = "ctrlhome/B6737115/custom/temp";

// Output status topics
const char* topic_status_light = "ctrlhome/B6737115/status/light";
const char* topic_status_fan = "ctrlhome/B6737115/status/fan";
const char* topic_status_curtain = "ctrlhome/B6737115/status/curtain";
const char* topic_status_rgb = "ctrlhome/B6737115/status/rgb";
const char* topic_status_alarm = "ctrlhome/B6737115/status/alarm";

// ================= THRESHOLDS =================

#define TEMP_HIGH_C 35
#define HUMIDITY_HIGH_PERCENT 80
#define GAS_HIGH_VALUE 2000
#define WATER_FULL_PERCENT 90

// ================= PINS =================

// Sensors
#define DHTPIN 4
#define DHTTYPE DHT11

#define LDR_PIN 34
#define PIR_PIN 27
#define MQ2_PIN 35
#define WATER_PIN 32
#define POT_PIN 39

// Outputs
#define LIGHT_PIN 14
#define FAN_PIN 26
#define BUZZER_PIN 25
#define SERVO_PIN 13

// Mood LEDs: Red, Green, Yellow
#define MOOD_RED_PIN 16
#define MOOD_GREEN_PIN 17
#define MOOD_YELLOW_PIN 15

// LCD I2C
#define LCD_SDA_PIN 21
#define LCD_SCL_PIN 22

// ================= OBJECTS =================

WiFiClient espClient;
PubSubClient client(espClient);

DHT dht(DHTPIN, DHTTYPE);
Servo curtainServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= STATE =================

String currentMode = "manual";

int customBrightness = 150;
int customCurtain = 90;
int customTemp = 25;
String customFan = "low";
bool customAlarm = false;

int currentRed = 0;
int currentGreen = 0;
int currentYellow = 0;
int currentFanSpeed = 0;
int currentLightBrightness = 0;
int currentCurtainPosition = 90;
bool alarmOn = false;

unsigned long lastPublish = 0;
unsigned long lastEmergencyBlink = 0;
bool emergencyBlinkState = false;

unsigned long lastSafetyAlert = 0;
String lastAlertMessage = "";

String lcdAlertMessage = "";
unsigned long lcdAlertStart = 0;
const unsigned long lcdAlertDuration = 5000;

// ================= HELPER FUNCTIONS =================

void publishText(const char* topic, String value) {
  client.publish(topic, value.c_str());
}

void publishInt(const char* topic, int value) {
  char buffer[12];
  sprintf(buffer, "%d", value);
  client.publish(topic, buffer);
}

void publishFloat(const char* topic, float value) {
  char buffer[12];
  dtostrf(value, 1, 2, buffer);
  client.publish(topic, buffer);
}

void lcdMessage(String line1, String line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1.substring(0, 16));
  lcd.setCursor(0, 1);
  lcd.print(line2.substring(0, 16));
}

String shortModeName(String mode) {
  if (mode == "sleep") return "Sleep";
  if (mode == "study") return "Study";
  if (mode == "relax") return "Relax";
  if (mode == "away") return "Away";
  if (mode == "energy") return "Energy";
  if (mode == "emergency") return "Emergency";
  if (mode == "comfort") return "Custom Mood";
  return "Manual";
}

void lcdStandby() {
  lcdMessage("Ctrl+Home Ready", "Mode: " + shortModeName(currentMode));
}

void lcdNotify(String message) {
  lcdAlertMessage = message;
  lcdAlertStart = millis();
  lcdMessage("Notification", message);
}

void updateLCD() {
  if (lcdAlertMessage != "") {
    if (millis() - lcdAlertStart >= lcdAlertDuration) {
      lcdAlertMessage = "";
      lcdStandby();
    }
  }
}

int waterPercent(int waterValue) {
  waterValue = constrain(waterValue, 0, 4095);
  return map(waterValue, 0, 4095, 0, 100);
}

String waterTankStatus(int waterValue) {
  int percent = waterPercent(waterValue);

  if (percent < 10) {
    return "Tank Empty";
  } else if (percent < 35) {
    return "Tank Low";
  } else if (percent < 70) {
    return "Tank Medium";
  } else if (percent < 90) {
    return "Tank Almost Full";
  } else {
    return "Tank Full Filled";
  }
}

// ================= OUTPUT CONTROL =================

void setMoodLights(bool redOn, bool greenOn, bool yellowOn) {
  currentRed = redOn ? 255 : 0;
  currentGreen = greenOn ? 255 : 0;
  currentYellow = yellowOn ? 255 : 0;

  analogWrite(MOOD_RED_PIN, currentRed);
  analogWrite(MOOD_GREEN_PIN, currentGreen);
  analogWrite(MOOD_YELLOW_PIN, currentYellow);

  String moodStatus = "";
  if (redOn) moodStatus += "Red ";
  if (greenOn) moodStatus += "Green ";
  if (yellowOn) moodStatus += "Yellow";
  if (moodStatus.length() == 0) moodStatus = "OFF";

  publishText(topic_status_rgb, moodStatus);

  Serial.print("Mood LEDs: ");
  Serial.println(moodStatus);
}

void setLight(int brightness) {
  currentLightBrightness = constrain(brightness, 0, 255);
  analogWrite(LIGHT_PIN, currentLightBrightness);
  publishInt(topic_status_light, currentLightBrightness);

  Serial.print("Main Light Brightness: ");
  Serial.println(currentLightBrightness);
}

void setFanSpeed(int speedValue) {
  currentFanSpeed = constrain(speedValue, 0, 255);
  analogWrite(FAN_PIN, currentFanSpeed);
  publishInt(topic_status_fan, currentFanSpeed);

  Serial.print("Fan Speed PWM: ");
  Serial.println(currentFanSpeed);
}

void setFanMode(String fanMode) {
  if (fanMode == "off") {
    setFanSpeed(0);
  } else if (fanMode == "low") {
    setFanSpeed(85);
  } else if (fanMode == "medium") {
    setFanSpeed(160);
  } else if (fanMode == "high") {
    setFanSpeed(255);
  }
}

void setCurtain(int angle) {
  currentCurtainPosition = constrain(angle, 0, 180);
  curtainServo.write(currentCurtainPosition);
  publishInt(topic_status_curtain, currentCurtainPosition);

  Serial.print("Curtain Position: ");
  Serial.println(currentCurtainPosition);
}

void setAlarm(bool state) {
  alarmOn = state;
  digitalWrite(BUZZER_PIN, alarmOn ? HIGH : LOW);
  publishText(topic_status_alarm, alarmOn ? "ON" : "OFF");

  Serial.print("Alarm: ");
  Serial.println(alarmOn ? "ON" : "OFF");
}

void normalAlert(String message) {
  publishText(topic_alert, message);
  lcdNotify(message);

  Serial.print("Alert: ");
  Serial.println(message);
}

// ================= MODE LOGIC =================

void applyMode(String mode) {
  currentMode = mode;
  publishText(topic_currentmode, currentMode);

  Serial.println();
  Serial.print("Applying Mode: ");
  Serial.println(mode);

  if (mode == "sleep") {
    setAlarm(false);
    setLight(0);
    setMoodLights(false, false, true);
    setFanMode("low");
    setCurtain(0);
    normalAlert("Sleep Mode ON");
  }

  else if (mode == "study") {
    setAlarm(false);
    setLight(255);
    setMoodLights(true, true, true);
    setFanMode("medium");
    setCurtain(140);
    normalAlert("Study Mode ON");
  }

  else if (mode == "relax") {
    setAlarm(false);
    setLight(100);
    setMoodLights(false, true, true);
    setFanMode("low");
    setCurtain(60);
    normalAlert("Relax Mode ON");
  }

  else if (mode == "away") {
    setAlarm(false);
    setLight(0);
    setMoodLights(false, false, false);
    setFanMode("off");
    setCurtain(0);
    normalAlert("Away Mode ON");
  }

  else if (mode == "energy") {
    setAlarm(false);
    setLight(60);
    setMoodLights(false, true, false);
    setFanMode("low");
    setCurtain(140);
    normalAlert("Energy Mode ON");
  }

  else if (mode == "emergency") {
    setLight(255);
    setMoodLights(true, false, false);
    emergencyBlinkState = true;
    lastEmergencyBlink = millis();
    setFanMode("high");
    setCurtain(180);
    setAlarm(true);
    normalAlert("EMERGENCY MODE");
  }

  else if (mode == "comfort") {
    setAlarm(false);
    setLight(customBrightness);
    setFanMode(customFan);
    setCurtain(customCurtain);
    normalAlert("Custom Mood ON");
  }

  else if (mode == "manual") {
    normalAlert("Manual Mode ON");
  }
}

void handleEmergencyBlink() {
  if (currentMode != "emergency") {
    return;
  }

  if (millis() - lastEmergencyBlink >= 500) {
    lastEmergencyBlink = millis();
    emergencyBlinkState = !emergencyBlinkState;

    if (emergencyBlinkState) {
      setMoodLights(true, false, false);
    } else {
      setMoodLights(false, false, false);
    }
  }
}

void handleMoodLedMessage(String message) {
  int firstComma = message.indexOf(',');
  int secondComma = message.indexOf(',', firstComma + 1);

  if (firstComma > 0 && secondComma > firstComma) {
    int redValue = message.substring(0, firstComma).toInt();
    int greenValue = message.substring(firstComma + 1, secondComma).toInt();
    int yellowValue = message.substring(secondComma + 1).toInt();

    setMoodLights(redValue > 0, greenValue > 0, yellowValue > 0);
  }
}

// ================= MQTT CALLBACK =================

void callback(char* topic, byte* payload, unsigned int length) {
  String topicName = String(topic);
  String message = "";

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.println();
  Serial.print("MQTT Command | ");
  Serial.print(topicName);
  Serial.print(" = ");
  Serial.println(message);

  if (topicName == topic_mode) {
    applyMode(message);
  }

  else if (topicName == topic_light_control) {
    currentMode = "manual";
    publishText(topic_currentmode, currentMode);
    lcdStandby();

    if (message == "ON") setLight(255);
    else if (message == "OFF") setLight(0);
    else setLight(message.toInt());
  }

  else if (topicName == topic_fan_control) {
    currentMode = "manual";
    publishText(topic_currentmode, currentMode);
    lcdStandby();

    if (message == "ON") setFanMode("medium");
    else if (message == "OFF") setFanMode("off");
    else setFanMode(message);
  }

  else if (topicName == topic_curtain_control) {
    currentMode = "manual";
    publishText(topic_currentmode, currentMode);
    lcdStandby();
    setCurtain(message.toInt());
  }

  else if (topicName == topic_alarm_control) {
    currentMode = "manual";
    publishText(topic_currentmode, currentMode);
    lcdStandby();
    setAlarm(message == "ON");
  }

  else if (topicName == topic_custom_brightness) {
    customBrightness = constrain(message.toInt(), 0, 255);
    if (currentMode == "comfort") setLight(customBrightness);
  }

  else if (topicName == topic_custom_rgb) {
    handleMoodLedMessage(message);
  }

  else if (topicName == topic_custom_fan) {
    customFan = message;
    if (currentMode == "comfort") setFanMode(customFan);
  }

  else if (topicName == topic_custom_curtain) {
    customCurtain = constrain(message.toInt(), 0, 180);
    if (currentMode == "comfort") setCurtain(customCurtain);
  }

  else if (topicName == topic_custom_alarm) {
    customAlarm = message == "ON";
    if (currentMode == "comfort") {
      normalAlert(customAlarm ? "Custom Alarm ON" : "Custom Alarm OFF");
    }
  }

  else if (topicName == topic_custom_temp) {
    customTemp = constrain(message.toInt(), 18, 35);
  }
}

// ================= SAFETY ALERT LOGIC =================

void sendSafetyAlert(String message, bool emergency) {
  unsigned long now = millis();

  if (message != lastAlertMessage || now - lastSafetyAlert > 8000) {
    lastSafetyAlert = now;
    lastAlertMessage = message;
    publishText(topic_alert, message);
    lcdNotify(message);

    Serial.print("SAFETY NOTIFICATION: ");
    Serial.println(message);
  }

  if (emergency && currentMode != "emergency") {
    applyMode("emergency");
  }
}

void checkEmergencyLogic(float temperature, float humidity, int gasValue, int waterValue, int motionValue) {
  int tankPercent = waterPercent(waterValue);

  bool gasDanger = gasValue > GAS_HIGH_VALUE;
  bool tankFull = tankPercent >= WATER_FULL_PERCENT;
  bool tempDanger = !isnan(temperature) && temperature >= TEMP_HIGH_C;
  bool humidityWarning = !isnan(humidity) && humidity >= HUMIDITY_HIGH_PERCENT;
  bool awayIntrusion = currentMode == "away" && motionValue == HIGH;
  bool customAlarmMotion = currentMode == "comfort" && customAlarm && motionValue == HIGH;

  if (gasDanger) {
    sendSafetyAlert("Gas/Smoke High", true);
  } else if (tankFull) {
    sendSafetyAlert("Water Tank Full", false);
  } else if (tempDanger) {
    sendSafetyAlert("High Temp " + String(temperature, 1) + "C", false);
  } else if (humidityWarning) {
    sendSafetyAlert("High Humid " + String(humidity, 1) + "%", false);
  } else if (awayIntrusion) {
    sendSafetyAlert("Motion in Away", true);
  } else if (customAlarmMotion) {
    sendSafetyAlert("Motion Alarm", true);
  } else if (currentMode != "emergency") {
    publishText(topic_alert, "All sensors normal");
    lastAlertMessage = "All sensors normal";
  }
}

void autoModeAdjustments(float temperature, int lightValue, int motionValue) {
  if (currentMode == "energy") {
    if (motionValue == LOW) {
      setLight(0);
      setFanMode("off");
    } else {
      if (lightValue < 1200) setLight(100);
      else setLight(30);

      if (!isnan(temperature) && temperature > 30) setFanMode("medium");
      else setFanMode("low");
    }
  }

  if (currentMode == "sleep") {
    if (motionValue == HIGH) setLight(35);
    else setLight(0);

    if (!isnan(temperature) && temperature > 30) setFanMode("medium");
    else setFanMode("low");
  }

  if (currentMode == "comfort") {
    if (!isnan(temperature) && temperature > customTemp + 2) {
      setFanMode("high");
    }
  }

  if (currentMode == "manual") {
    int potValue = analogRead(POT_PIN);
    int brightnessFromPot = map(potValue, 0, 4095, 0, 255);
    setLight(brightnessFromPot);
  }
}

// ================= WIFI + MQTT =================

void setup_wifi() {
  Serial.println();
  Serial.println("========================================");
  Serial.println("Ctrl+Home FINAL LCD SYSTEM Starting");
  Serial.println("========================================");

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected successfully");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void reconnect_mqtt() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker... ");

    String clientId = "CtrlHome_LCD_B6737115_" + String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      client.subscribe(topic_mode);
      client.subscribe(topic_light_control);
      client.subscribe(topic_fan_control);
      client.subscribe(topic_curtain_control);
      client.subscribe(topic_alarm_control);

      client.subscribe(topic_custom_brightness);
      client.subscribe(topic_custom_rgb);
      client.subscribe(topic_custom_fan);
      client.subscribe(topic_custom_curtain);
      client.subscribe(topic_custom_alarm);
      client.subscribe(topic_custom_temp);

      publishText(topic_currentmode, currentMode);
      normalAlert("Ctrl+Home ready");

      Serial.println("Subscribed to all control topics.");
      Serial.println("----------------------------------------");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" | retrying in 2 seconds");
      delay(2000);
    }
  }
}

// ================= SETUP + LOOP =================

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();

  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(POT_PIN, INPUT);

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MOOD_RED_PIN, OUTPUT);
  pinMode(MOOD_GREEN_PIN, OUTPUT);
  pinMode(MOOD_YELLOW_PIN, OUTPUT);

  curtainServo.attach(SERVO_PIN);

  Wire.begin(LCD_SDA_PIN, LCD_SCL_PIN);
  lcd.init();
  lcd.backlight();
  lcdMessage("Ctrl+Home", "Starting...");

  setLight(0);
  setFanMode("off");
  setCurtain(90);
  setMoodLights(false, false, false);
  setAlarm(false);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  lcdStandby();
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }

  client.loop();
  handleEmergencyBlink();
  updateLCD();

  if (millis() - lastPublish >= 2500) {
    lastPublish = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    int lightValue = analogRead(LDR_PIN);
    int motionValue = digitalRead(PIR_PIN);
    int gasValue = analogRead(MQ2_PIN);
    int waterValue = analogRead(WATER_PIN);
    int potValue = analogRead(POT_PIN);

    Serial.println();
    Serial.println("============== Ctrl+Home Data ==============");

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("DHT Sensor: Failed to read");
      publishText(topic_alert, "DHT read failed");
      lcdNotify("DHT read failed");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");

      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");

      publishFloat(topic_temperature, temperature);
      publishFloat(topic_humidity, humidity);
    }

    Serial.print("LDR Light Value: ");
    Serial.println(lightValue);

    Serial.print("PIR Motion: ");
    Serial.println(motionValue == HIGH ? "Motion Detected" : "No Motion");

    Serial.print("MQ-2 Gas Value: ");
    Serial.println(gasValue);

    Serial.print("Water Level Value: ");
    Serial.print(waterValue);
    Serial.print(" | Tank Status: ");
    Serial.print(waterTankStatus(waterValue));
    Serial.print(" | Tank Filled: ");
    Serial.print(waterPercent(waterValue));
    Serial.println("% filled");

    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);

    Serial.print("Current Mode: ");
    Serial.println(currentMode);

    publishInt(topic_light_sensor, lightValue);
    publishText(topic_motion, motionValue == HIGH ? "Motion Detected" : "No Motion");
    publishInt(topic_gas, gasValue);
    publishText(topic_water, waterTankStatus(waterValue) + " (" + String(waterPercent(waterValue)) + "% filled)");
    publishInt(topic_potentiometer, potValue);
    publishText(topic_currentmode, currentMode);

    publishInt(topic_status_light, currentLightBrightness);
    publishInt(topic_status_fan, currentFanSpeed);
    publishInt(topic_status_curtain, currentCurtainPosition);

    String moodStatus = "";
    if (currentRed > 0) moodStatus += "Red ";
    if (currentGreen > 0) moodStatus += "Green ";
    if (currentYellow > 0) moodStatus += "Yellow";
    if (moodStatus.length() == 0) moodStatus = "OFF";
    publishText(topic_status_rgb, moodStatus);

    publishText(topic_status_alarm, alarmOn ? "ON" : "OFF");

    checkEmergencyLogic(temperature, humidity, gasValue, waterValue, motionValue);

    if (currentMode != "emergency") {
      autoModeAdjustments(temperature, lightValue, motionValue);
    }

    Serial.println("============================================");
  }
}
