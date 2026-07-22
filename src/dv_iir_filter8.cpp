#include <Arduino.h>
#include <dv_iir_filter8.h>

DV_IirFilter8::DV_IirFilter8() {}

DV_IirFilter8::DV_IirFilter8(uint8_t smoothing)
  : _smoothing(smoothing) {}

void DV_IirFilter8::setSmoothing(uint8_t smoothing) {
  _smoothing = smoothing;
}

uint8_t DV_IirFilter8::getSmoothing() {
  return _smoothing;
}

uint8_t DV_IirFilter8::getValue() {
  return _value;
}

void DV_IirFilter8::reset() {
  _initialized = false;
  _count = 0;
}

unsigned long DV_IirFilter8::getCount() {
  return _count;
}

uint8_t DV_IirFilter8::update(uint8_t input) {
  if (!_initialized) {
    _value = input;
    _initialized = true;
  } else {
    _value = lerp(_value, input, _smoothing);
  }
  _count++;
  return _value;
}

static uint8_t DV_IirFilter8::lerp(uint8_t a, uint8_t b, uint8_t smoothing) {
    return a + (((int16_t)(b - a) * smoothing) >> 8);
}
