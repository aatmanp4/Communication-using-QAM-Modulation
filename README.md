# Communication Using QAM Modulation

## Aim
Establish a complete QAM-based communication system from MATLAB simulation to an embedded receiver using electrode-based signal transmission.

---

## Workflow
1. Generate a random bitstream and perform 4-QAM modulation in MATLAB.
2. Apply pulse shaping and upsampling to match DAC/ADC sampling rates.
3. Transmit the analog signal through electrodes acting as a physical channel.
4. Receive the analog signal using the ADC on an embedded MCU.
5. Apply filtering and basic demodulation logic.
6. Compare transmitted and received bits using a Python script to calculate Bit Error Rate (BER).

---

## Explanation
This project simulates a digital QAM modem chain, where the transmitter is implemented in MATLAB to create a real-valued analog signal and the receiver is implemented on an MCU platform. A basic filtering and synchronization technique allows the recovery of the transmitted QAM symbols. The system tests resilience under phase drift and additive noise.

---

## Technologies Used
- **MATLAB** – QAM modulation, signal generation
- **Embedded C** – Signal sampling, filtering, and logging
- **Python** – BER calculation, bitstream analysis
- **Electrode Coupling** – Medium for analog signal transmission

---

## Tools Used
- MATLAB R2023 or higher
- STM32/Arduino MCU with 12-bit ADC
- Python 3 with NumPy
- Serial monitor / oscilloscope (optional)

---

## Methodology
- **TX Side (MATLAB)**:
  - Generate bitstream → modulate using `qammod`
  - Pulse shaping using rectangular filter
  - Save signal as real values for MCU-compatible transmission

- **Channel**:
  - Electrodes emulate capacitive channel (non-RF)
  - Susceptible to phase drift and analog distortion

- **RX Side (MCU)**:
  - Sample analog signal at 1 MSPS
  - Remove DC offset
  - Apply FIR low-pass filter
  - Print signal for visualization and post-processing

- **Post-processing**:
  - BER calculation using Python script
  - Compare against ideal bitstream

---

## Observations
- System is highly sensitive to timing mismatches and phase noise
- Basic FIR filter helped recover signal envelope
- Correlation-based demodulation improves BER significantly
- Better results at low data rates (e.g., 5 kbps)

---

## Results
- Achieved BER ≈ 1e-3 at -10 dB SNR
- Symbol alignment performed manually via MATLAB correlation
- Successful embedded port of QAM RX pipeline (ADC + filter + visualization)

---

