#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "Hotspot";
const char* password = "87654321";
int timezone = 5.5 * 3600;
int dst = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  
  display.clearDisplay();
  display.display();
  delay(1000);

  configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
    Serial.print("*");
    delay(1000);
  }
  Serial.println("\nTime response....OK");
}

void loop() {
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.println(p_tm);
  int r = 30;

  // Now draw the clock face
  display.drawCircle(display.width() / 2, display.height() / 2, 2, WHITE);

  // Hour ticks
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(64, -2);
  display.print("12");
  display.setCursor(79, 2);
  display.print("1");
  display.setCursor(89, 13);
  display.print("2");
  display.setCursor(94, 28);
  display.print("3");
  display.setCursor(89, 43);
  display.print("4");
  display.setCursor(79, 53);
  display.print("5");
  display.setCursor(63, 58);
  display.print("6");
  display.setCursor(49, 53);
  display.print("7");
  display.setCursor(38, 42);
  display.print("8");
  display.setCursor(34, 28);
  display.print("9");
  display.setCursor(38, 13);
  display.print("10");
  display.setCursor(48, 2);
  display.print("11");

  // Display second hand
  float angle = p_tm->tm_sec * 6;
  angle = (angle / 57.29577951); // Convert degrees to radians
  int x3 = (64 + (sin(angle) * (r)));
  int y3 = (32 - (cos(angle) * (r)));
  display.drawLine(64, 32, x3, y3, WHITE);

  // Display minute hand
  angle = p_tm->tm_min * 6;
  angle = (angle / 57.29577951); // Convert degrees to radians
  x3 = (64 + (sin(angle) * (r - 3)));
  y3 = (32 - (cos(angle) * (r - 3)));
  display.drawLine(64, 32, x3, y3, WHITE);

  // Display hour hand
  angle = p_tm->tm_hour * 30 + int((p_tm->tm_min / 12) * 6);
  angle = (angle / 57.29577951); // Convert degrees to radians
  x3 = (64 + (sin(angle) * (r - 11)));
  y3 = (32 - (cos(angle) * (r - 11)));
  display.drawLine(64, 32, x3, y3, WHITE);

  display.setCursor(0, 0);
  String monthname[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  display.print(monthname[p_tm->tm_mon]);
  display.print(" ");
  display.print(p_tm->tm_mday);

  display.setCursor(100, 0);
  String dayname[7] = {"MON", "TUE", "WED", "THUR", "FRI", "SAT", "SUN"};
  display.print(dayname[p_tm->tm_wday - 1]);

  // Update display with all data
  display.display();
  delay(100);
  display.clearDisplay();
}
