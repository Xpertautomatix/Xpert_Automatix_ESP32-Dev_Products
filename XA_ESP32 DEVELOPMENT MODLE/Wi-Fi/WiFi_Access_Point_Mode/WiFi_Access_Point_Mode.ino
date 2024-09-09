/* 
 
WiFi_Access_Point_Mode Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
#include <WiFi.h>

//WIFI ACCESS POINT USER NAME PASSWORD
const char* AP_ssid     = "XYZ";//add ur custom ssid
const char* AP_password = ""; //add ur custom Password

//WIFI access point ip configuration 
IPAddress AP_local_IP(192, 168, 2, 1);
IPAddress AP_gateway(192, 168, 2, 1);
IPAddress AP_subnet(255, 255, 255, 0);

void setup()
{ 
  Serial.begin(115200);
  
  //clear old config
  WiFi.disconnect(true);        //disable wifi station 
  WiFi.softAPdisconnect(true);  //disable wifi access point 

  pinMode(2, OUTPUT); 
  delay(1000);                  // Some delay
  //---------------------------------------------------------------------------------//
  Serial.println("PROJECT NAME          : ESP32 WiFi HOTSPOT");
  Serial.print  ("AP/HOTSPOT SSID       : ");
  Serial.println(AP_ssid);
  Serial.print  ("AP/HOTSPOT PASSWORD   : ");
  Serial.println(AP_password);
  //--------------------------------------------------------------------------------//
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);

  WiFi_Access_point_Mode();
}

//----------------------------------------------------------------------------------------//
void loop()
{  
  //PRINT NO OF DEVICES CONNECTED

  delay(2000);
  Serial.print("NO OF DEVICES CONNECTED  : ");
  Serial.println(WiFi.softAPgetStationNum());
  
  //YOUR CODE HERE...

}

//-------------------------------------------------------------------------------------------------------------------//
//IF REQUIRED USE FOLLOWING OPTION
  //WiFi.softAP(const char* ssid, const char* password, int channel, int ssid_hidden, int max_connection)
  // ssid           : name for the access point – maximum of 63 characters;
  // password       : minimum of 8 characters; set to NULL if you want the access point to be open;
  // channel        : Wi-Fi channel number (1-13)
  // ssid_hidden    : (0 = broadcast SSID, 1 = hide SSID)
  // max_connection : maximum simultaneous connected clients (1-4)
//-------------------------------------------------------------------------------------------------------------------//
void WiFi_Access_point_Mode()
{ 
  Serial.println("Setting AP (Access Point)....");
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_local_IP, AP_gateway, AP_subnet);
  WiFi.softAP(AP_ssid, AP_password);

  digitalWrite(2,HIGH);
  delay(400);
  digitalWrite(2,LOW);

  Serial.println("WIFI__hotspot__ON");

  Serial.print("AP IP ADDRESS            : ");
  Serial.println(WiFi.softAPIP());
}