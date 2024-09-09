/* 
 
Led_Blink Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/

// the setup function runs once when you press reset or power the board
void setup() {
 // initialize digital pin for LED as an output.
 pinMode(0, OUTPUT);  //SET PIN & PIN MODE
 }

// the loop function runs over and over again forever
void loop() {
digitalWrite(0, HIGH); // LED ON OR PIN 2 IS HIGH
delay(1000);  // HOLD 1 SEC
digitalWrite(0, LOW); // LED OFF OR PIN 2 IS LOW
delay(1000); // HOLD 1 SEC
}
