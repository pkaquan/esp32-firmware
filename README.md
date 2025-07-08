# 🏠 Smart Home with ESP32 + FreeRTOS + Firebase

A real-time smart home control system using **ESP32 (with FreeRTOS)**, **Firebase (Firestore + Storage)**, and a **Flutter mobile app**. The project enables users to control multiple devices (motors, lights, relays) and monitor sensors remotely through cloud-based infrastructure.


## 🧠 Features
- 🌱 Control the irrigation pump motor and configure its customizable settings
- 💡 Controlling the on/off state of devices
- 🔔 Alarm system with gas sensor MQ2-Buzzer and start fire system
- 📡 Read temperature & humidity using DHT21
- 🎮 Display data on OLED (SH1106, I2C)
- 🔁 Multi-tasking with FreeRTOS (sensor + display + cloud task, control device + cloud task)
- ☁️ Ready for Firebase integration (for Flutter control)
- 🧱 Clean code: FreeRTOS, class-based, modular file structure

## ⚙️ Diagram
![Connection diagram](images/diagram.png)

## 📷 Demo
![Video Demo](images/IMG_0786.MOV), (images/IMG_0787.MOV)

## 🗂 Project Structure
/include
├── Device.h
├── Security.h
└── Service.h
/lib
├── Device
   ├── Control_Device.h
   ├── Display.h
   └── Sensor.h
├── Security
   ├── AESEncryption.h
   └── File_System.h
└── Service
   ├── Firebase.h
   └── WiFi_Manager.h
/src
├── Device
   ├── Control_Device.cpp
   ├── Display.cpp
   └── Sensor.cpp
├── Security
   ├── AESEncryption.cpp
   └── File_System.cpp
├── Service
   ├── Firebase.cpp
   └── WiFi_Manager.cpp
└── main.cpp // FreeRTOS task setup

## 🔧 Requirements
- ESP32-Wroom-32 (38 Pin) Dev Board
- IC 74HC595
- Module D4184 (Control pulse)
- Module Buzzer
- MQ2 Sensor
- DHT21 sensor
- LCD OLED 1.3 inch (I2C)
- Arduino framework

## 🚀 How to Run
1. Clone repo
2. Open with Arduino IDE or PlatformIO
3. Install required libraries:
   - ArduinoJson
   - U8g2
   - DHT sensor library
   - Adafruit Unified Sensor
   - NTPClient
   - Firebase Arduino Client Library for ESP8266 and ESP32
4. Upload to ESP32
5. Watch data on OLED!

## 👨‍💻 Author
Pham Khoa Anh Quan