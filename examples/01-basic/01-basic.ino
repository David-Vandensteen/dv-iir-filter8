#include <Arduino.h>
#include <dv_iir_filter8.h>

#define ADC_RESOLUTION 10 // bits

DV_IirFilter8 filter;

void setup() {
  Serial.begin(115200);
  Serial.println("IIR Percentage Filter Test");
}

void loop() {
  uint16_t rawInput = analogRead(A0);
  uint8_t inputPercent = (rawInput * 100) >> ADC_RESOLUTION;
  uint8_t filteredPercent = filter.update(inputPercent);

  Serial.print("Input:"); Serial.print(inputPercent);
  Serial.println();
  Serial.print("Filtered:"); Serial.print(filteredPercent);
  Serial.println();
  delay(100);
}
