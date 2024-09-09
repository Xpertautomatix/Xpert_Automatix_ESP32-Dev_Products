/* 
 
LCD_8Bit_Mode Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/
#include<LiquidCrystal.h>

const int RS=2,EN=4,d0=5,d1=18,d2=19,d3=21,d4=13,d5=12,d6=14,d7=27;  // CONFIG 8 DATA PINS & RS &EN
LiquidCrystal lcd(RS,EN,d0,d1,d2,d3,d4,d5,d6,d7); 
void setup()
{
  lcd.begin(16,2);    // col , row
  lcd.setCursor(0,0); // col , row
  lcd.print("Hello World!"); 
}

void loop()
{
  lcd.setCursor(0,1); // col , row
  lcd.print("Xpert Automatix");
}

