/* 
 
ADC Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // SET BAUDRATE
  pinMode(2, INPUT); // CONFIG ADC PIN
}

void loop() {
  // put your main code here, to run repeatedly:
  int Adc_val;
  Adc_val = analogRead(2); 
  Serial.println(Adc_val); //PRINT ADC VALUE IN YOUR SERIAL MONITER
}