# Communication Using QAM Modulation

## Aim
Build a complete QAM-based modem chain from MATLAB to embedded interface using electrode signal paths.

## Workflow
- BPSK/QAM signal modeling in MATLAB
- Generate bitstream and upsample
- Transmit waveform via electrode
- Demodulate and filter signal on RX MCU
- Compare received bits to original

## Explanation
QAM modulation is implemented with noise injection and symbol timing errors simulated. A digital baseband is converted to analog and transmitted. The receiver synchronizes, demodulates, and computes BER and SNR.

## Technologies Used
- MATLAB (simulation and signal generation)
- Embedded C
- Electrode coupling
- Low-pass filters (Butterworth)

## Tools
- MATLAB
- Arduino/Feather MCU
- Oscilloscope
- Python (for SNR and BER plotting)

## Methodology
- Bitstream modulated at baseband
- Filtered and DAC-converted to analog
- ADC samples signal and performs demodulation
- Symbol synchronization via correlation

## Observations
- System is sensitive to phase drift in analog domain
- BER significantly improved by synchronization

## Results
- BER: approximately 10⁻³ at SNR = -10 dB, bitrate 5 kbps
