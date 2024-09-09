/* 
 
I2C_LCD
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup() {
  // put your setup code here, to run once:
  lcd.init();                       // initialize the lcd 
  lcd.backlight();                  // backlight on
  lcd.setCursor(0,0);               // col , row
  lcd.print("Hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);               // col , row
  lcd.print("Xpert Automaticx");    
}