/*
 * Optical Communication System - Receiver
 * -----------------------------------------
 * Implements Adaptive Thresholding and custom timing recovery.
 *
 * Components:
 * - SENSOR_PIN (Analog A0): Connected to the output of the Active Filter OpAmp.
 */

const int SENSOR_PIN = A0;
const int BIT_PERIOD = 15;      // Must match the transmitter's BIT_PERIOD (15 ms)
const int THRESHOLD_OFFSET = 6; // THRESHOLD value from the report 

int avg_val = 0; // Ambient noise floor baseline 

void setup() {
  Serial.begin(9600);
  Serial.println("Receiver Ready (Calibrating...)");

  // Baseline Calibration: Average 100 samples to determine the ambient noise floor.
  long sum = 0;
  for(int i=0; i<100; i++) {
    sum += analogRead(SENSOR_PIN);
    delay(2); // Small delay for stable readings
  }
  avg_val = sum / 100;
  
  Serial.print("Baseline Calibrated (avg_val): ");
  Serial.println(avg_val);
}

// Simple filter to print only visible ASCII characters
bool isValidASCII(char c) {
  return (c >= 32 && c <= 126) || c == '\n' || c == '\r';
}

void loop() {
  int current_val = analogRead(SENSOR_PIN);
  
  // Adaptive Threshold Detection: Check for Start Bit.
  // Logic "1" is detected when ADC > avg_val + THRESHOLD.
  if (current_val > avg_val + THRESHOLD_OFFSET) {
    
    // Timing Alignment: Wait 1.5 bit periods to sample at the optimal midpoint 
    // of the first data bit after Start Bit detection[cite: 75].
    delay(BIT_PERIOD + (BIT_PERIOD / 2)); 
    
    char receivedChar = readByte();
    
    if (isValidASCII(receivedChar)) {
      Serial.write(receivedChar);
    }
    
    // Wait for the Stop Bit period to complete
    delay(BIT_PERIOD); 
  }
}

// Function to read 8 data bits
char readByte() {
  char myData = 0;
  // Read 8 bits, sampling at each bit's midpoint[cite: 66].
  for (int i = 0; i < 8; i++) {
    int reading = analogRead(SENSOR_PIN);
    
    // Apply Adaptive Thresholding
    if (reading > avg_val + THRESHOLD_OFFSET) {
      bitWrite(myData, i, 1);
    } else {
      bitWrite(myData, i, 0);
    }
    
    // Wait for the next bit period
    delay(BIT_PERIOD);
  }
  return myData;
}
