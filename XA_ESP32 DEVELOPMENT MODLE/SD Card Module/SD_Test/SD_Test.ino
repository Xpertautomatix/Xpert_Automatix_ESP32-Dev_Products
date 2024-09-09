/* 
 
SD_Test Test
 
 
For the Xpert Automatix ESP32 Development Board.
 
created Sep 2024
by XpertAutomatix
 
This example code is in the public domain.
 
 https://github.com/Xpertautomatix/Products

---------------------------------------------------------------------------------
   * MOSI - PIN 23
  * MISO - PIN 19
  * SCK - PIN 18
  * SDA(CS) - PIN 15 OR 5 
*/

  #include <SPI.h>
  #include <SD.h>

  File myFile;

  void setup() {
    // Open serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("Initializing SD card...");

    // Use GPIO 15 as CS (Chip Select)
    if (!SD.begin(15)) {
      Serial.println("initialization failed!");
      while (1);
    }
    Serial.println("initialization done.");

    delay(100);  // Add delay before accessing SD card

    // Open the file. Only one file can be open at a time.
    myFile = SD.open("/test.txt", FILE_WRITE);

    // If the file opened, write to it
    if (myFile) {
      Serial.print("Writing to test.txt...");
      myFile.println("testing 1, 2, 3.");
      // Close the file:
      myFile.close();
      Serial.println("done.");
    } else {
      // If the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }

    // Re-open the file for reading:
    myFile = SD.open("/test.txt");
    if (myFile) {
      Serial.println("test.txt:");

      // Read from the file until there's nothing else in it:
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      // Close the file:
      myFile.close();
    } else {
      // If the file didn't open, print an error:
      Serial.println("error opening test.txt");
    }
  }

  void loop() {
    // Nothing happens after setup
  }
