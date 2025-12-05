# FSO_Digital_Communication
#  Optical Digital Communication System (FSO)
## Free-Space Optical (FSO) Link via LED and Photodiode

### Project Summary
This is a low-cost, robust **Free-Space Optical (FSO) communication system**  designed to transmit ASCII data reliably between microcontrollers.

The core challenge addressed was **photodiode saturation** from ambient light (sunlight, room lights).

**Solution:** We created a **hybrid analog-digital design**  that uses:
1.  **Analog Front-End (AFE):** To clean and amplify the signal.
2.  **Embedded Software:** To intelligently decode the data.

---

##  Hardware Design (The Analog Circuit)

The receiver uses a multi-stage OpAmp circuit to process the light signal.

* **TIA (Transimpedance Amplifier):** Converts the weak current from the photodiode into a strong voltage signal[cite: 36, 40].
* **AC Coupling:** A capacitor ($C_2$) **blocks the DC signal** caused by constant ambient light, allowing only the fast data pulses (AC) to pass through[cite: 9, 42]. This is the key to immunity!
* **Active Low-Pass Filter:** This second OpAmp stage boosts the signal ($\approx 6.5x$) and removes high-frequency noise to clean the data pulses[cite: 43, 47].



---

##  Software & Decoding

The system's intelligence is in the Arduino code, which handles communication timing and signal interpretation[cite: 20].

* **RZ-like Protocol:** A custom timing protocol ensures that the data pulses stay intact through the AC-coupled circuit[cite: 27].
* **Adaptive Thresholding:** Instead of a fixed hardware threshold, the software dynamically **calibrates itself** by measuring the ambient noise floor ($avg\_val$)[cite: 72].
    * Data is detected when the signal is clearly above the current noise floor ($ADC > avg\_val + THRESHOLD$)[cite: 74].
    * This ensures **stable operation** even when room lighting changes[cite: 76].
* **Performance:** Achieved reliable transmission at $15\,ms/bit$ ($\approx 66$ baud)[cite: 88].

---

### 📂 Project Files
* **Full Report:** [Link to Documentation/Report with Physical Setup.pdf]
* **Schematics:** [Link to Hardware/receiver.png] and [Link to Hardware/transmitter.png.png]
* **Code:** Arduino files in `Software/`
