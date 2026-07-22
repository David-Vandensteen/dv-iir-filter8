#ifndef DV_IIR_FILTER8_H
#define DV_IIR_FILTER8_H
#include <Arduino.h>

class DV_IirFilter8 {
public:
  explicit DV_IirFilter8();
  explicit DV_IirFilter8(uint8_t smoothing);
  void setSmoothing(uint8_t smoothing);
  uint8_t getSmoothing();
  uint8_t getValue();
  unsigned long getCount();
  void reset();
  uint8_t update(uint8_t input);

private:
  uint8_t _smoothing = 32;
  uint8_t _value;
  bool _initialized = false;
  unsigned long _count = 0;
  static uint8_t lerp(uint8_t a, uint8_t b, uint8_t smoothing);
};
#endif
