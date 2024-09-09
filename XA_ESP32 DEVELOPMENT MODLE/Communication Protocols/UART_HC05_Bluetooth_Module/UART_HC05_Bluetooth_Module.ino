/* 
 
UART_HC05_Bluetooth_Module Test
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
char message;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    message = Serial.read();
    
    if(message == 'a')
    {
      digitalWrite(2,1);
      Serial.write(message);
    }
    else if(message == 'b')
    {
      digitalWrite(2,0);
      Serial.write(message);
    }
    else
    {
      Serial.println("Invalid Input...");
    }
  }
}

