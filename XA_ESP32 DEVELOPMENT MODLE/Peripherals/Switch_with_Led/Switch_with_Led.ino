/* 
 
Switch_with_Led Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
void setup() {
  // put your setup code here, to run once:
  pinMode(15, INPUT_PULLUP); // CONFIGURE PIN FOR SWITCH
  pinMode(2, OUTPUT); // CONFIGURE PIN FOR LED
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(15)==0)      // CHECK SWITCH IS PRESS OR NOT
  {                           // IF SWITCH IS PRESSED
    digitalWrite(2, HIGH);    // LED IS ON
    delay(1000);              
  }
  else                        // IF SWITCH IS NOT PRESSED 
  {
    digitalWrite(2, LOW);     // LED IS OFF
  }
}
