#include <Arduino.h>
#include <arm_math.h>
#include <arm_const_structs.h>

#define ADC_PIN A1
#define FFT_SIZE 512
#define SAMPLE_RATE 1000000
#define SAMPLES_PER_SYMBOL 100  // Approx. 1MSPS / 10kbps
#define SYMBOLS 100

float adc_buffer[FFT_SIZE];
float signal[FFT_SIZE];
float filtered[FFT_SIZE];
float fir_state[FFT_SIZE + 30];

// Example Raised Cosine Filter Coefficients (truncated)
float fir_coeffs[31] = {
  -0.0001, -0.0003, -0.0007, -0.0012, -0.0017, -0.0022, -0.0025, -0.0026,
  -0.0022, -0.0012,  0.0006,  0.0031,  0.0063,  0.0098,  0.0135,  0.0170,
   0.0200,  0.0222,  0.0232,  0.0229,  0.0213,  0.0186,  0.0150,  0.0109,
   0.0065,  0.0023, -0.0012, -0.0037, -0.0051, -0.0053, -0.0042
};
arm_fir_instance_f32 fir;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  arm_fir_init_f32(&fir, 31, fir_coeffs, fir_state, FFT_SIZE);
}

void loop() {
  for (int i = 0; i < FFT_SIZE; i++) {
    adc_buffer[i] = analogRead(ADC_PIN);
    delayMicroseconds(1000000 / SAMPLE_RATE);
  }

  float mean = 0;
  for (int i = 0; i < FFT_SIZE; i++) mean += adc_buffer[i];
  mean /= FFT_SIZE;
  for (int i = 0; i < FFT_SIZE; i++) signal[i] = adc_buffer[i] - mean;

  arm_fir_f32(&fir, signal, filtered, FFT_SIZE);

  // Symbol sample + demod (naive, threshold-based)
  for (int i = 0; i < SYMBOLS; i++) {
    int idx = i * SAMPLES_PER_SYMBOL;
    if (idx + 1 >= FFT_SIZE) break;

    float I = filtered[idx];
    float Q = filtered[idx + 1];
    int decoded = 2 * (I > 0) + (Q > 0);
    Serial.println(decoded); // 0–3 QAM symbol
  }

  delay(500);
}
