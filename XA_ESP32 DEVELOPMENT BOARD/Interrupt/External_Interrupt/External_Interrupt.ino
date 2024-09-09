/* 
 
External_Interrupt Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
const unsigned char InterruptPin = 12; // CONFIG PIN FOR INTERRUPT
bool Request;

void IRAM_ATTR isr() {  // INTERRUPT FUNCTION
 Request = true;
}

void setup() {
 Serial.begin(9600); // BAUD RATE
 pinMode(InterruptPin, INPUT_PULLUP); // 12 PIN INPUT_PULLUP CONFIG
 attachInterrupt(InterruptPin, isr, RISING); // USE INTERRUPT CONFIG ---> // INTERRUPT PIN // INTERRUPT FUNCTION // TYPE OF INTERRUPT //
}

void loop() {
 if (Request){
   Serial.println("Interrupt Request Received!"); // IF INTERRUPT IS CALLED THEN PRINT RESPONSE
   Request = false;
 }
}