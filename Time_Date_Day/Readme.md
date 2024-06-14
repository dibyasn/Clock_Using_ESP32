<p align="center">
    <img src="https://github.com/dibyasn/Digital_Clock/assets/42934757/b221a2f2-4239-4215-8b91-4830a95bf99d" alt="Analog Clock" style="width: 150px;">
</p>


---

# ⏰ ESP32 Time, Date, and Day Display on OLED

![ESP32](https://img.shields.io/badge/ESP32-Platform-blue) ![License](https://img.shields.io/badge/License-MIT-green)

Welcome to the ESP32 Time, Date, and Day Display project! This project uses an ESP32 microcontroller to fetch the current time from the internet and display it on an SSD1306 OLED screen without RTC (Real Time Clock). Follow along to create your own stylish clock with an animated display.

## 📝 Table of Contents

- [⏰ ESP32 Time, Date, and Day Display on OLED](#-esp32-time-date-and-day-display-on-oled)
  - [📝 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [🛠️ Requirements](#️-requirements)
  - [📦 Libraries Installation](#-libraries-installation)
  - [🔌 Hardware Connections](#-hardware-connections)
  - [🚀 Getting Started](#-getting-started)
  - [📝 Code Explanation](#-code-explanation)
    - [Declaration and Bitmap Animation](#declaration-and-bitmap-animation)
    - [Display Initialization](#display-initialization)
    - [Wi-Fi Setup](#wi-fi-setup)
    - [🛜 Wifi Animation](#-wifi-animation)
    - [Time Fetching and Display](#time-fetching-and-display)
    - [Formatting and Printing in Display](#formatting-and-printing-in-display)
  - [🔧 Troubleshooting](#-troubleshooting)
  - [🙌 Acknowledgments](#-acknowledgments)

## ✨ Features

- **Wi-Fi Connectivity**: Connects to your Wi-Fi network to fetch the current time from an NTP server.
- **Real-Time Clock**: Displays the current time, date, and day of the week.
- **OLED Display**: Utilizes an SSD1306 OLED screen for clear and stylish time representation.
- **Animations**: Smooth transitions and updates to keep the display engaging.

## 🛠️ Requirements

- **Hardware**:
  - ESP32 board
  - SSD1306 OLED display (128x64 pixels)
  - Connecting wires

- **Software**:
  - Arduino IDE
  - Required Libraries:
    - WiFi.h
    - time.h
    - SPI.h
    - Wire.h
    - Adafruit_GFX.h
    - Adafruit_SSD1306.h

## 📦 Libraries Installation

Install the required libraries through the Arduino IDE Library Manager:

1. Open Arduino IDE.
2. Go to `Sketch` > `Include Library` > `Manage Libraries`.
3. Search for and install:
   - Adafruit GFX Library
   - Adafruit SSD1306
   - ESP32 board support

## 🔌 Hardware Connections

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3V3       |
| GND      | GND       |
| SCL      | GPIO 22   |
| SDA      | GPIO 21   |

![OLED Connection Diagram](https://microcontrollerslab.com/wp-content/uploads/2021/05/OLED-interfacing-with-ESP32.jpg)

## 🚀 Getting Started

1. **Clone or Download the Project**:
    ```sh
    git clone https://github.com/dibyasn/Clock_Using_ESP32.git
    ```

2. **Open the Code in Arduino IDE**:
    Open `Digital_Clock.ino` in the Arduino IDE.

3. **Configure Wi-Fi and Timezone**:
    Update the following lines with your Wi-Fi credentials and desired timezone offset:
    ```cpp
    const char* ssid = "Your_SSID";
    const char* password = "Your_PASSWORD";
    int GMTOffset = 19800;  // Offset for IST
    int daylightOffset = 0; // Daylight savings offset
    ```

4. **Upload the Code**:
    Select your ESP32 board and port from the `Tools` menu and upload the code.

## 📝 Code Explanation

### Declaration and Bitmap Animation

Let's dive into the code and understand how it works.

```cpp
#include <WiFi.h>
#include <time.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Initialize the OLED display with I2C connection
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

const char* ssid = "Your_SSID"; 
const char* password = "Your_PASSWORD";

int GMTOffset = 19800;  // Offset for GMT+5:30 (Indian Standard Time)
int daylightOffset = 0;  // No daylight saving time offset

int frame = 0;
#define FRAME_DELAY (42)
#define FRAME_WIDTH (48)
#define FRAME_HEIGHT (48)

// Animation frames data
const byte PROGMEM frames[][288] = {
  // Frame 1 data
  { /*... frame data ...*/ },
  // Frame 2 data
  { /*... frame data ...*/ },
  // Add more frames as needed
};
```

### Display Initialization

The display is initialized, and a connection status message is shown:

```cpp
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
}
display.clearDisplay();
display.setTextSize(1); 
display.setCursor(0,0);
display.setTextColor(WHITE);
```


### Wi-Fi Setup

The `setup` function initializes the Wi-Fi connection:

```cpp
void setup() { 
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to Wi-Fi!");
  configTime(GMTOffset, daylightOffset, "pool.ntp.org", "time.nist.gov");
}
```
### 🛜 Wifi Animation 

This animation shows wifi while connecting to internet:

```cpp
 display.drawBitmap(40, 8, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
```
[Animatated Icons](https://animator.wokwi.com/)

### Time Fetching and Display

In the `loop` function, the current time is fetched and displayed every second:

```cpp
void loop() {
  time_t rawtime = time(nullptr);
  struct tm* timeinfo = localtime(&rawtime);

  Serial.print("Time: ");
  Serial.print(timeinfo->tm_hour);
  Serial.print(":");
  Serial.print(timeinfo->tm_min);
  Serial.print(":");
  Serial.println(timeinfo->tm_sec);
 ///.....//
```

### Formatting and Printing in Display

Representations for Time, Date and day:

```cpp
  //.....//

  // Format time
  char timeStr[9];  // HH:MM:SS
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  
  // Time
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, 0);
  display.print(timeStr);

  // Format date
  char dateStr[12];  // DD MMM YYYY
  const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  snprintf(dateStr, sizeof(dateStr), "%02d %s %04d", timeinfo->tm_mday, months[timeinfo->tm_mon], 1900 + timeinfo->tm_year);

  // Date
  display.setTextSize(1);
  display.getTextBounds(dateStr, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, 25);
  display.print(dateStr);

  // Format day
  const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  const char* dayStr = days[timeinfo->tm_wday];

  // Day
  display.setTextSize(2);
  display.getTextBounds(dayStr, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, 50);
  display.print(dayStr);

  display.display();

  delay(1000);
}
```


## 🔧 Troubleshooting

- Ensure all connections are secure.
- Check the serial monitor for error messages.
- Verify that the correct board and port are selected in the Arduino IDE.


## 🙌 Acknowledgments

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

Feel free to contribute, report issues, or suggest enhancements. Happy coding! 🚀

<p align="center">
    <a href="https://github.com/dibyasn/Analog_clock"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>