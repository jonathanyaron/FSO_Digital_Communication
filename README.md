# FSO_Digital_Communication
# 🚀 Optical Digital Communication System (FSO)
## Free-Space Optical (FSO) Link via LED and Photodiode

### 🎓 **Abstract & Core Competencies**
[cite_start]This is a complete **Free-Space Optical (FSO) communication link** designed and implemented for reliable ASCII-data transmission between microcontrollers[cite: 8]. [cite_start]The system addresses the classical problem of **photodiode saturation** under ambient illumination [cite: 9] [cite_start]by combining an **AC-coupled Analog Front-End (AFE)** with a software-defined **RZ-like modulation protocol**[cite: 9].

* [cite_start]**Core Skills Demonstrated:** Mixed-Signal Circuit Design, Embedded C++, Analog Filtering, Timing-Critical Protocols, and Adaptive Signal Processing[cite: 92].

---

## 🛠️ **Hardware Design: The Analog Front-End (AFE)**
[cite_start]The receiver architecture is a multi-stage OpAmp AFE engineered to overcome the limitations of resistor-only photodiode circuits[cite: 35].

### 1. Transmitter Stage
* [cite_start]**Driver:** A high-intensity LED is driven by an NPN transistor for isolation and controlled switching[cite: 24].
* [cite_start]**Modulation:** **RZ-like modulation** is used, where Logic "1" is encoded using a short pulse[cite: 25, 27]. [cite_start]This approach is **essential** for AC-coupled receivers, as static levels decay through coupling capacitors[cite: 26].

### 2. Receiver AFE Stages
* [cite_start]**Stage A - Transimpedance Amplifier (TIA):** Provides high sensitivity and linearity[cite: 40]. [cite_start]It converts the photodiode's current to a proportional voltage[cite: 19].
    * [cite_start]**Gain:** Set by the feedback resistor $R_3$ at **$100\,k\Omega$**[cite: 38].
* **Stage B - AC Coupling + Active Filtering:**
    * [cite_start]**AC-Coupling:** Capacitor $C_2 (0.1\,\mu F)$ **blocks DC offsets** caused by ambient illumination[cite: 42].
    * [cite_start]**Active Low-Pass Filter (OpAmp U2):** Suppresses high-frequency noise and improves the Signal-to-Noise Ratio (SNR)[cite: 47].
        * [cite_start]**Gain:** $\approx 6.5x$ using a $220\,k\Omega/34\,k\Omega$ network[cite: 43].
        * **Cutoff Frequency ($f_c$):** Calculated using the formula:
        $$f_c = \frac{1}{2\pi R_5 C_3}$$
[cite_start] [cite: 44, 46]

---

## 🧠 **Software & Signal Processing (Decoding Layer)**
[cite_start]The decoding layer is fully implemented in the microcontroller, shifting complexity from hardware to adaptive signal processing[cite: 15, 20].

* [cite_start]**Protocol:** A custom **bit-banging protocol** replaces standard UART timing to support the AC-coupled design[cite: 64].
* [cite_start]**Synchronization:** Includes a **Start Bit** for wake-up and synchronization, and a **Stop Bit**[cite: 65, 67].
* [cite_start]**Inter-Byte Guard Time:** A **$60\,ms$ silent period** is implemented to prevent **baseline drift** and **Inter-Symbol Interference (ISI)** by allowing coupling capacitors to discharge[cite: 68].
* [cite_start]**Adaptive Thresholding:** Software-based bit discrimination replaces a hardware comparator[cite: 71].
    * [cite_start]**Baseline Calibration:** On boot, **100 samples are averaged** to determine the ambient noise floor ($avg\_val$)[cite: 72].
    * [cite_start]**Detection:** Logical "1" is detected when $ADC > avg\_val + THRESHOLD$[cite: 73, 74]. [cite_start]This provides **robustness** across widely varying lighting conditions[cite: 76, 86].
* [cite_start]**Performance:** Reliable ASCII transmission was achieved at **$15\,ms/bit$ ($\approx 66$ baud)**[cite: 88].
