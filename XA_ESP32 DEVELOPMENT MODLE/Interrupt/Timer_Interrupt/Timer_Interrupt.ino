/* 
 
Timer_Interrupt Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products
 
*/

volatile int interruptCounter;  //for counting interrupt
int totalInterruptCounter;   	//total interrupt counting

hw_timer_t * timer = NULL;      //H/W timer defining (Pointer to the Structure)
void IRAM_ATTR onTimer() {      //Defining Inerrupt function with IRAM_ATTR for faster access
 interruptCounter++;
}
 
void setup() {
 Serial.begin(115200);
 timer = timerBegin(0, 80, true);           	              // timer 0, prescalar: 80, UP counting
 timerAttachInterrupt(timer, &onTimer, true); 	            // Attach interrupt
 timerAlarmWrite(timer, 2000000, true);  		                // Match value= 1000000 for 1 sec. delay.
 timerAlarmEnable(timer);           			                  // Enable Timer with interrupt (Alarm Enable)
}
 
void loop() {
 if (interruptCounter > 0) 
 {
   interruptCounter--;
   totalInterruptCounter++;         	                          //counting total interrupt
                           //Toggle LED
   Serial.print("An interrupt as occurred. Total number: ");
   Serial.println(totalInterruptCounter);
 }
}