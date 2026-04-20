/*
 * Unique Tech - Arduino Masterclass
 * Lesson 2.2: Air Quality Monitoring (MQ-135)
 * * Περιγραφή: Μέτρηση ποιότητας αέρα και κατηγοριοποίηση επιπέδων ρύπανσης.
 * Για περισσότερα: https://uniquetech-robotics.blogspot.com/
 */

// Ορισμός Pin
const int MQ135_PIN = A0; 

// Ρυθμίσεις Βαθμονόμησης (Calibration)
const int CLEAN_AIR_THRESHOLD = 200;
const int POLLUTION_THRESHOLD = 500;

void setup() {
  Serial.begin(9600);
  
  // Χρόνος προθέρμανσης αισθητήρα
  Serial.println(F("--- Unique Tech Air Monitor v1.0 ---"));
  Serial.println(F("Προθέρμανση αισθητήρα (Warm-up)..."));
  delay(3000); 
}

void loop() {
  // Λήψη μέσου όρου από 10 μετρήσεις για σταθερότητα (Smoothing)
  long sum = 0;
  for(int i = 0; i < 10; i++) {
    sum += analogRead(MQ135_PIN);
    delay(10);
  }
  int averageValue = sum / 10;

  // Εμφάνιση αποτελεσμάτων
  Serial.print(F("Air Quality Index: "));
  Serial.print(averageValue);
  
  displayAirStatus(averageValue);

  delay(2000); // Μέτρηση κάθε 2 δευτερόλεπτα
}

void displayAirStatus(int value) {
  if (value < CLEAN_AIR_THRESHOLD) {
    Serial.println(F(" | Status: EXCELLENT ✨"));
  } 
  else if (value < POLLUTION_THRESHOLD) {
    Serial.println(F(" | Status: MODERATE ⚠️"));
  } 
  else {
    Serial.println(F(" | Status: HIGH POLLUTION 🚨"));
  }
}
