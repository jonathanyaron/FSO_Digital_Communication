/*
 * Optical Communication System - Transmitter
 * -------------------------------------------
 * Implements RZ-like modulation suitable for AC-coupled receivers.
 *
 * Components:
 * - LED_PIN (Digital 12): Connected to the NPN transistor base (or gate).
 */

const int LED_PIN = 12;
const int BIT_PERIOD = 15;      // 15 ms/bit (approx. 66 baud) [cite: 88]
const int HALF_PERIOD = 7;      // Pulse width for '1' (approx. half the bit period)

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Ensure LED is off initially
  Serial.println("Transmitter Ready. Type a message:");
}

void loop() {
  if (Serial.available() > 0) {
    char myChar = Serial.read();
    sendByte(myChar);
    // Inter-Byte Guard Time (60ms) to allow receiver capacitors to discharge 
    // and prevent Inter-Symbol Interference (ISI)[cite: 68].
    delay(60); 
  }
}

// Function to transmit a Logic '1' using a short pulse (RZ-like)
void sendOneWave() {
  // Pulse HIGH
  digitalWrite(LED_PIN, HIGH);
  delay(HALF_PERIOD);
  
  // Return to LOW (Return-to-Zero)
  digitalWrite(LED_PIN, LOW);
  delay(BIT_PERIOD - HALF_PERIOD); // Wait the remaining time of the bit period
}

// Function to transmit a Logic '0' using silence
void sendZero() {
  digitalWrite(LED_PIN, LOW);
  delay(BIT_PERIOD);
}

// Main function to transmit one ASCII character
void sendByte(char myData) {
  // 1. Start Bit: Wake-up pulse for synchronization[cite: 65].
  sendOneWave(); 
  
  // 2. Data Bits: Transmit 8 bits, LSB first.
  for (int i = 0; i < 8; i++) {
    if (bitRead(myData, i) == 1) {
      sendOneWave();
    } else {
      sendZero();
    }
  }
  
  // 3. Stop Bit: Silent period[cite: 67].
  sendZero(); 
}
