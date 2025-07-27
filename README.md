Smart Saline Monitoring System using IoT

This project is an **IoT-based Smart Saline Monitoring System** designed to ensure continuous monitoring of IV saline levels for patients. It helps reduce the manual workload of hospital staff by providing **real-time alerts and data** via the **Blynk IoT platform**.

---

🚀 Features

- 📡 **Ultrasonic Sensor** to measure the saline bottle level
- 🌡 **DHT11 Sensor** to measure temperature and humidity
- 💡 **LED Indicator** when saline level is safe
- 🚨 **Blynk Notification** when saline level drops below 7 cm
- 🔔 **Buzzer Alert** if temperature exceeds 45°C
- 📱 **Real-time Monitoring** on Blynk app (Web + Mobile)
- 🔧 **Low-cost** and **easy-to-install** setup

---

🔧 Hardware Components

| Component         | Quantity |
|------------------|----------|
| ESP8266 NodeMCU   | 1        |
| Ultrasonic Sensor (HC-SR04) | 1 |
| DHT11 Sensor      | 1        |
| Buzzer            | 1        |
| LED               | 1        |
| Jumper Wires      | Several  |
| Breadboard        | 1        |
| 5V Power Supply   | 1        |

---

📲 Blynk Setup

1. Create a new **Template** in [Blynk IoT Console](https://blynk.io/)
2. Assign **Virtual Pins**:
   - `V0` – Temperature
   - `V1` – Humidity
   - `V2` – Saline Distance
3. Add Widgets:
   - **Gauge** for temperature, humidity, and distance
   - **Event Notification** named: `low_distance`
4. Copy the `BLYNK_TEMPLATE_ID`, `BLYNK_TEMPLATE_NAME`, and `AUTH_TOKEN` into the code

---

## 📷 How It Works

The **ultrasonic sensor** detects the distance between the sensor and the fluid level in the saline bottle. If the distance exceeds **12 cm**, the **LED turns ON**. If it falls below **7 cm**, a **Blynk notification** is sent. Meanwhile, the **DHT11 sensor** monitors temperature, triggering the **buzzer** if the environment becomes too hot (above 45°C).

---
