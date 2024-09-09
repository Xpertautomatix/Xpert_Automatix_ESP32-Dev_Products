/* 
 
Xpert Automatix Default code 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>  // Replace SPIFFS with LittleFS
#include <DNSServer.h> // Include DNSServer library for Captive Portal

// Define the ADC and LDR pins
const int adcPin = 32;
const int ldrPin = 34;
const int ledPin = 0; 
const int Button = 16; 
bool ledState = false;
int adcValues[10];
unsigned long previousMillis = 0;
const long interval = 1000;  

// Define static IP configuration
IPAddress localIP(192, 168, 4, 1); // Static IP address
IPAddress gateway(192, 168, 4, 1); // Gateway address (same as static IP)
IPAddress subnet(255, 255, 255, 0); // Subnet mask

// Create an instance of the web server
WebServer server(80);

// Create an instance of the DNS server
DNSServer dnsServer;

// DNS server port
const byte DNS_PORT = 53;

// Function to update ADC values
void updateADCValues() {
    // Shift values to the left, discarding the oldest value
    for (int i = 0; i < 9; i++) {
        adcValues[i] = adcValues[i + 1];
    }
    // Add the latest ADC value
    adcValues[9] = analogRead(ldrPin);
}
void handleLDR() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        updateADCValues();  // Update ADC values every second
    }

    String html = "<html><head><meta http-equiv='refresh' content='1'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; background-color: #eaeaea; margin: 0; padding: 20px; color: #333; }";
    html += "h1 { text-align: center; color: #262262; font-size: 2.2rem; margin-bottom: 20px; }";
    html += ".container { max-width: 800px; margin: auto; padding: 30px; background-color: #fff; border-radius: 10px; box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1); }";
     html += "p { text-align: center; font-size: 1.2rem; color: #444; margin-bottom: 20px; }";
    html += ".button { background-color: #ed1c24; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 1rem; text-decoration: none; }";
    html += ".button:hover { background-color: #b8151a; }";
    html += "svg { display: block; margin: 20px auto; }";
    html += "line, circle { transition: all 0.3s ease; }";
    html += "</style></head><body>";
    
    html += "<div class='container'>";
   
    html += "<h1>ADC Sensor Values</h1>";
    html += "<p>Current ADC Value: " + String(adcValues[9]) + "</p>";

    // Create the SVG graph
    html += "<svg width='750' height='400' xmlns='http://www.w3.org/2000/svg' style='background-color:#fafafa; border-radius: 8px; box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);'>";
    html += "<line x1='50' y1='350' x2='700' y2='350' style='stroke:#333;stroke-width:2' />";  // X-axis
    html += "<line x1='50' y1='50' x2='50' y2='350' style='stroke:#333;stroke-width:2' />";    // Y-axis

    // Labels for X-axis and Y-axis
    html += "<text x='340' y='380' font-family='Arial' font-size='14' fill='#333'>Time (s)</text>";
    html += "<text x='30' y='200' font-family='Arial' font-size='14' fill='#333' transform='rotate(-90 30,200)'>ADC Value</text>";

    // Plot the points for the ADC values
    int xPos = 50;
    int yScale = 300;  // Height of the graph area (300px)
    for (int i = 0; i < 10; i++) {
        int adcY = 350 - map(adcValues[i], 0, 4095, 0, yScale);  // Scale ADC value to graph height
        html += "<circle cx='" + String(xPos) + "' cy='" + String(adcY) + "' r='4' fill='#ff5722' />";
        if (i > 0) {
            int prevX = xPos - 65;
            int prevY = 350 - map(adcValues[i - 1], 0, 4095, 0, yScale);
            html += "<line x1='" + String(prevX) + "' y1='" + String(prevY) + "' x2='" + String(xPos) + "' y2='" + String(adcY) + "' style='stroke:#ff5722;stroke-width:2' />";
        }
        xPos += 65;
    }

    html += "</svg>";

    html += "<p><a href='/' class='button'>Back to Home Page</a></p>";
    html += "</div></body></html>";

    server.send(200, "text/html", html);  // Send the constructed HTML response
}


// Handler for Home page

void handleHome() {
    int adcValue = analogRead(adcPin);  // Read ADC value to display on the home page
    String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><style>";
    html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; margin: 0; padding: 0px;  }";
    html += "h1 { text-align: center; color: #262262; font-size: 2rem; }";  // Responsive font size
    html += ".container { max-width: auto; width: 100%; margin-left: auto; margin-right: auto; padding: 20px; background-color: #fff; border-radius: 8px; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); }";
   html += "p { text-align: center; font-size: 1.2rem; }";
    html += "a { display: block; text-align: center; font-size: 1rem; padding: 10px; margin: 10px; background-color: #ed1c24; color: white; text-decoration: none; border-radius: 5px; }";
    html += "a:hover { background-color: #b8151a; }";
    html += ".light { width: 100px; height: 100px; background-color: #ed1c24; margin: 20px auto; border-radius: 50%; box-shadow: 0 0 50px rgba(255, 255, 255, 0); }";  // Light element
    html += "</style></head><body>";
    
    html += "<div class='container'>";
     // Logo remains responsive
    html += "<h1>Xpert Automatix ESP32 Home Page</h1>";
    
    // Display ADC Value dynamically
    html += "<h2>LDR Adc Value: <span id='adcValue'>" + String(adcValue) + "</span></h2>";  // ADC value displayed here
    
    // Light that changes brightness based on ADC value
    html += "<div class='light' id='light'></div>";
    
    html += "<script>";
    html += "function updateLight(adcValue) {";
    html += "  let intensity = Math.floor((adcValue / 4095) * 100);";  // Calculate intensity as a percentage
   html += "  var lightElement = document.getElementById('light');";
html += "  lightElement.style.backgroundColor = 'rgba(255, 215, 0, ' + (intensity / 100) + ')';";  // Change circle to yellow
html += "  lightElement.style.boxShadow = '0 0 ' + (intensity * 0.5) + 'px rgba(255, 215, 0, ' + (intensity / 100) + ')';";  // Yellow glow effect // Adjust the shadow (brightness)
    html += "}";
    html += "setInterval(function() {";
    html += "  fetch('/getAdcValue').then(response => response.text()).then(data => {";
    html += "    document.getElementById('adcValue').innerText = data;";
    html += "    updateLight(parseInt(data));";  // Update light intensity based on ADC value
    html += "  });";
    html += "}, 300);";  // Fetch ADC value every second
    html += "</script>";
    
    html += "<a href='/ldr'>ADC Display</a>";
    html += "<a href='/led'>LED Control</a>";
    html += "</div></body></html>";

    server.send(200, "text/html", html);
}

// Handler for LED Control page
void handleLED() {
    // Page to control and view LED state
    String html = "<html><head>";
    html += "<meta charset='UTF-8'>";
    html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<meta http-equiv='refresh' content='2;url=/led' />";  // Refresh the page without toggling LED
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; margin: 0; padding-right: 10px; padding-left:10px }";
    html += "h1 { text-align: center; color: #262262; font-size: 2rem; }";  
    html += ".container { max-width: 600px; width: 100%; margin: auto; padding: 20px; background-color: #fff; border-radius: 8px; box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); }";
    html += "p { text-align: center; font-size: 1.2rem; }";
    html += ".button-on { background-color: #ed1c24; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 1rem; text-decoration: none; }"; 
    html += ".button { background-color: #ed1c24; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 1rem; text-decoration: none; }"; 
    html += ".button-off { background-color: #262261; color: white; padding: 10px 20px; border: none; border-radius: 5px; cursor: pointer; font-size: 1rem; text-decoration: none; }";
    html += ".button:hover { background-color: #b8151a; }";
    html += ".gap { margin-top: 20px; }";  // Add margin for spacing
    html += "@media (max-width: 600px) { h1 { font-size: 1.5rem; } p { font-size: 1rem; } .button { font-size: 0.9rem; padding: 8px 16px; } }";
    html += "</style></head><body>";
    html += "<div class='container'>";
   
    html += "<h1>LED Control</h1>";
    
    // Show the current state of the LED
    if (ledState) {
        html += "<p>LED is currently <strong>ON</strong></p>";
        html += "<p><a href='/led/toggle' class='button-off'>Turn LED OFF</a></p>";  // Button to turn off the LED
    } else {
        html += "<p>LED is currently <strong>OFF</strong></p>";
        html += "<p><a href='/led/toggle' class='button-on'>Turn LED ON</a></p>";  // Button to turn on the LED
    }

    // Add some gap before the "Back to Home Page" button
    html += "<p class='gap'><a href='/' class='button'>Back to Home Page</a></p>";
    html += "</div></body></html>";
    
    server.send(200, "text/html", html);
}

// Handler to toggle LED state
void handleLEDToggle() {
    // Toggle the LED state
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    // Redirect back to the LED control page
    server.sendHeader("Location", "/led");
    server.send(303);
}

// Handler to get ADC value (for Home page AJAX)
void handleGetAdcValue() {
    int adcValue = analogRead(adcPin);
    server.send(200, "text/plain", String(adcValue));  // Send the ADC value as plain text
}

// Handler for physical button (optional)
void handleLEDbuttton() {
    if(digitalRead(Button) == LOW) {
        ledState = !ledState; // Toggle the LED state
        digitalWrite(ledPin, ledState ? HIGH : LOW); // Set the LED based on the state
    }
}

// Handler for DNS requests (Captive Portal)
void handleDNS() {
    // This function is handled by the DNSServer library
    // No additional code needed here
}

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Initialize LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("An error has occurred while mounting LittleFS");
        return;
    }

    // Initialize ADC values
    for (int i = 0; i < 10; i++) {
        adcValues[i] = 0;
    }

    // Initialize ADC and LED pins
    analogReadResolution(12); // 12-bit resolution
    pinMode(ledPin, OUTPUT);
    pinMode(ldrPin, INPUT);
    pinMode(adcPin, INPUT);
    pinMode(Button, INPUT_PULLUP);
    digitalWrite(ledPin, LOW); // Ensure LED is OFF initially

    // Setup WiFi as Access Point with Static IP
    WiFi.softAPConfig(localIP, gateway, subnet);
    WiFi.softAP("Xpert Automatix-ESP  32", "12345678"); // SSID and Password

    // Print the IP address
    Serial.println("Access Point IP address: ");
    Serial.println(localIP);

    // Start the DNS server for Captive Portal
    dnsServer.start(DNS_PORT, "*", localIP);
    Serial.println("DNS server started");

    // Serve static files (e.g., logo.png) from LittleFS
    server.serveStatic("/logo.png", LittleFS, "/logo.png");

    // Define routes
    server.on("/", handleHome);
    server.on("/ldr", handleLDR);
    server.on("/getAdcValue", handleGetAdcValue);  // Route for fetching ADC value
    server.on("/led", handleLED);
    server.on("/led/toggle", handleLEDToggle);

    // Optionally, catch all other routes and redirect to the home page
    server.onNotFound([]() {
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plain", "");
    });

    // Start the web server
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    // Handle DNS requests for Captive Portal
    dnsServer.processNextRequest();

    // Handle client requests for web server
    server.handleClient();

    // Handle physical button (optional)
    handleLEDbuttton();
}
