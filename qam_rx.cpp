#include <Arduino.h>
#include <arm_math.h>
#include <arm_const_structs.h>

#define ADC_PIN A1
#define FFT_SIZE 256
#define SAMPLE_RATE 1000000

float adc_buffer[FFT_SIZE];
float input_signal[FFT_SIZE];
float filtered[FFT_SIZE];

// low-pass FIR filter coefficients
float fir_coeffs[5] = {0.1, 0.15, 0.5, 0.15, 0.1};
float fir_state[FFT_SIZE + 4];
arm_fir_instance_f32 fir;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  arm_fir_init_f32(&fir, 5, fir_coeffs, fir_state, FFT_SIZE);
}

void loop() {
  for (int i = 0; i < FFT_SIZE; i++) {
    adc_buffer[i] = analogRead(ADC_PIN);
    delayMicroseconds(1000000 / SAMPLE_RATE);
  }

  float mean = 0;
  for (int i = 0; i < FFT_SIZE; i++) mean += adc_buffer[i];
  mean /= FFT_SIZE;
  for (int i = 0; i < FFT_SIZE; i++) input_signal[i] = adc_buffer[i] - mean;

  // FIR filter to remove noise
  arm_fir_f32(&fir, input_signal, filtered, FFT_SIZE);

  for (int i = 0; i < FFT_SIZE; i++) {
    Serial.println(filtered[i]);  

  delay(500);
}
