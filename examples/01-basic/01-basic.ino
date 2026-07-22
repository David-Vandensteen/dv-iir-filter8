#include <Arduino.h>
#include "dv_iir_filter8.h"

DV_IirFilter8 filter(32);

void setup() {
  Serial.begin(115200);
  Serial.println("IIR Lerp Filter Test");
}

void loop() {
  uint8_t input = analogRead(A0) >> 2; // 0..1023 -> 0..255
  uint8_t filtered = filter.update(input);
  Serial.print("Input: "); Serial.print(input);
  Serial.print("\tFiltered: "); Serial.println(filtered);
  delay(100);
}
