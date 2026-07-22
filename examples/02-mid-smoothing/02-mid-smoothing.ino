#include <Arduino.h>
#include <dv_iir_filter8.h>

DV_IirFilter8 filter(128);

uint8_t inputPercent = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("IIR Percentage Filter Test");
}

void loop() {
  uint8_t filteredPercent = filter.update(inputPercent);

  Serial.print("Input:");
  Serial.print(inputPercent);
  Serial.print(",Getter:");
  Serial.print(filter.getValue());
  Serial.print(",Filtered:");
  Serial.println(filteredPercent);

  delay(50);

  static uint16_t count = 0;
  count++;

  if (count >= 10) {
    count = 0;
    inputPercent = (inputPercent == 0) ? 100 : 0;
  }
}