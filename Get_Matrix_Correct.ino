#include <Wire.h>
#include "VL53L1X.h"

const int NUM_SENSORS = 256; // Number of sensors

VL53L1X sensors[NUM_SENSORS]; // Array to hold all the sensors

void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(400000);

  // Initialize all sensors
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Failed to initialize sensor ");
      Serial.println(i);
      while (1)
        ;
    }
    sensors[i].setDistanceMode(VL53L1X::Short);
    sensors[i].startContinuous(10); //10ms
    sensors[i].setMeasurementTimingBudget(30); //20ms
    sensors[i].setROISize(4, 16); // Set the ROI size to 7x16
  }
}

void loop() {
  // Reading distances from all sensors
  float distances[NUM_SENSORS];
  for (int i = 0; i < NUM_SENSORS; i++) {
    distances[i] = sensors[i].read() ; // In mm
    // Serial.print("Obtaining sensor :");
    Serial.print(distances[i]);
    Serial.print(",");
    // if (i % 16 == 0) {
    //   // The number is divisible by 16
    //   Serial.println();
    // } 
  }
  Serial.println();
  // // Displaying distances in a 16x16 matrix
  // for (int row = 0; row < 16; row++) {
  //   for (int col = 0; col < 16; col++) {
  //     int sensorIndex = row * 16 + col;
  //     Serial.print(distances[sensorIndex], 2); // Print with 2 decimal places
  //     Serial.print(",");      
  //     Serial.print("\t"); // Tab space for formatting
  //   }
  //   Serial.println(); // Move to the next line for the next row
  // }

  // // Serial.print("SPAD printed");
  // Serial.println();
  // // Wait for a short delay to prevent overflow of the serial buffer
  // delay(100);
  // for(int i = 0; i < 2; i++) {
  //   Serial.print("Delaying : ");
  //   Serial.print(i);
  //   Serial.print(" seconds...");
  //   Serial.println();
  //   delay(900);
  // }
  // Wait for 5 seconds before getting data again
   // Adjusted delay to account for the time spent in the loop
}
