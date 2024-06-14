<p align="center">
    <img src="https://github.com/dibyasn/Clock_Using_ESP32/assets/42934757/3cb31030-3788-45b6-8154-801c02f872de" alt="Analog Clock" style="width: 150px;">
</p>

# Analog Clock using OLED and WiFi ⏰


Welcome to the OLED WiFi Clock Project! This project uses an ESP32 board to connect to WiFi and display the current time on a 0.96" OLED display using I2C communication.

## Table of Contents
- [Analog Clock using OLED and WiFi ⏰](#analog-clock-using-oled-and-wifi-)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [🔧 Components](#-components)
  - [🔌 Circuit Diagram](#-circuit-diagram)
    - [Connections:](#connections)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Install Required Libraries](#2-install-required-libraries)
    - [3. Update WiFi Credentials](#3-update-wifi-credentials)
    - [4. Upload the Code](#4-upload-the-code)
  - [💡 Code Explanation](#-code-explanation)
    - [Main Features:](#main-features)
  - [🖥️ Usage](#️-usage)
  - [🎉 Acknowledgments](#-acknowledgments)

## 📖 Introduction
This project showcases how to create a real-time clock using an ESP32 and a 4-pin OLED display. The clock synchronizes time over WiFi using NTP (Network Time Protocol) and displays it on the OLED screen.

## 🔧 Components
- **ESP32 Board**
- **0.96" OLED Display (I2C, 4-pin)**
- **Jumper Wires**
- **Breadboard**

## 🔌 Circuit Diagram
![Circuit Diagram](https://camo.githubusercontent.com/b23818ebd638b073570b27f421cf0a09b3b120ea202192dec1477f010b936c98/68747470733a2f2f6d6963726f636f6e74726f6c6c6572736c61622e636f6d2f77702d636f6e74656e742f75706c6f6164732f323032312f30352f4f4c45442d696e746572666163696e672d776974682d45535033322e6a7067)

### Connections:
| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3V3       |
| GND      | GND       |
| SDA      | GPIO 21   |
| SCL      | GPIO 22   |

## 🚀 Setup Instructions
### 1. Clone the Repository
```sh
git clone https://github.com/dibyasn/Clock_Using_ESP32.git
```

### 2. Install Required Libraries
Ensure you have the following libraries installed in the Arduino IDE:
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) 📚
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) 📟
- [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi) 🌐

### 3. Update WiFi Credentials
Replace `REPLACE_WITH_YOUR_WIFI_SSID` and `REPLACE_WITH_YOUR_WIFI_PASSWORD` with your WiFi network's SSID and password in the code.

### 4. Upload the Code
Connect your ESP32 board to your computer, select the correct board and port in the Arduino IDE, and upload the code.

## 💡 Code Explanation
The code initializes the OLED display and WiFi connection. It fetches the current time from NTP servers and displays it on the OLED screen with a graphical clock face.

### Main Features:
- **WiFi Connection:** Connects to a WiFi network.
- **Time Synchronization:** Fetches time from NTP servers.
- **OLED Display:** Displays the current time in both analog and digital formats.

```cpp
// Sample of the main parts of the code
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <time.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "REPLACE_WITH_YOUR_WIFI_SSID";
const char* password = "REPLACE_WITH_YOUR_WIFI_PASSWORD";
int timezone = 5.5 * 3600;
int dst = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  ...
}

void loop() {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  ...
}
```

## 🖥️ Usage
Once the code is uploaded, the OLED display will show a clock face with the current time. The time is updated every second, and the display is refreshed to show the latest time.

## 🎉 Acknowledgments
This project is inspired by various IoT clock projects and leverages the powerful capabilities of the ESP32 and the OLED display. Special thanks to the developers of the Adafruit GFX and SSD1306 libraries for making display handling straightforward and efficient.

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

Feel free to contribute, report issues, or suggest enhancements. Happy coding! 🚀

<p align="center">
    <a href="https://github.com/dibyasn/Analog_clock"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>
