#include <ESP8266WiFi.h>

const char *ssid = "XpertAutomatix";  // Hotspot name
const char *password = "12345678";    // Hotspot password (min. 8 characters)

void setup() {
  Serial.begin(115200);
  
  // Initialize Wi-Fi access point
  WiFi.softAP(ssid, password);

  // Print the IP address
  Serial.print("Access Point Created. IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Your code here (e.g., serve web pages, handle requests)
}
