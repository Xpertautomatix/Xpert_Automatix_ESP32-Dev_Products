/* 
 
PWM_Led_Fade Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT); //SET PWM PIN IS OUTPUT CONNECTED TO LED
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<256 ; i++) // LIGHT INTENSITY INCREASE 0 - 255 DUTY CYCLE 
  {
    analogWrite(2, i); 
    delay(20);
  }
  delay(200);
  for(int i=255; i>=0 ; i--) // LIGHT INTENSITY DECREASE 255 - 0 DUTY CYCLE 
  {
    analogWrite(2, i);
    delay(20);
  }
  delay(200);
}

