/*
 * Unique Tech - Arduino Masterclass
 * Lesson 2.2b: True CO2 with Sensirion SCD40
 * Χρήση βιβλιοθήκης Sensirion I2C SCD4x
 */

#include <Arduino.h>
#include <SensirionI2cScd4x.h>
#include <Wire.h>

SensirionI2cScd4x scd4x;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  scd4x.begin(Wire);

  // Σταμάτημα προηγούμενων μετρήσεων
  scd4x.stopPeriodicMeasurement();

  // Έναρξη μετρήσεων (κάθε 5 δευτερόλεπτα)
  uint16_t error = scd4x.startPeriodicMeasurement();
  if (error) {
    Serial.print("Error starting measurement: ");
    Serial.println(error);
  }

  Serial.println("SCD40 Initialized. Waiting for first reading...");
}

void loop() {
  uint16_t co2;
  float temperature;
  float humidity;

  // Διάβασμα δεδομένων
  uint16_t error = scd4x.readMeasurement(co2, temperature, humidity);

  if (error) {
    Serial.print("Error reading measurement: ");
  } else if (co2 == 0) {
    Serial.println("Invalid sample detected.");
  } else {
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm | Temp: ");
    Serial.print(temperature);
    Serial.print(" °C | Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(5000); // Ο SCD40 ανανεώνει κάθε 5 δευτερόλεπτα
}
