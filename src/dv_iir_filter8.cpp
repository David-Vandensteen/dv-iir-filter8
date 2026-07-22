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
  return _value >> 8;
}

void DV_IirFilter8::reset() {
  _initialized = false;
  _count = 0;
  _value = 0;
}

unsigned long DV_IirFilter8::getCount() {
  return _count;
}

uint8_t DV_IirFilter8::update(uint8_t input) {
  if (!_initialized) {
    _value = (uint16_t)input << 8;
    _initialized = true;
  } else {
    int32_t target = (uint16_t)input << 8;
    int32_t delta = target - _value;
    _value += (delta * (256 - _smoothing)) >> 8;
  }
  _count++;
  return _value >> 8;
}