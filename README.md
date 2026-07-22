# dv_iir_filter8

A lightweight and efficient Arduino library for implementing an 8-bit IIR filter API with fixed-point internal processing.

## Description

**dv_iir_filter8** is an IIR (Infinite Impulse Response) filter optimized for microcontrollers. It accepts and returns 8-bit values (`0..255`) while using fixed-point internal arithmetic for smoother interpolation and better precision.

## Features

- 8-bit API (input/output values 0-255)
- Fixed-point internal computation (higher precision than plain 8-bit math)
- Fast linear interpolation algorithm
- Configurable smoothing parameter
- Update count tracking

## Installation

### Via Arduino Library Manager (recommended)

1. Open the Arduino IDE
2. Go to Tools > Manage Libraries...
3. Search for "dv_iir_filter8"
4. Click Install

### Manual

1. Download this repository as a ZIP file.
2. In the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library...
3. Select the downloaded ZIP file to install the library.

## Usage

```cpp
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
  // 16-bit-only approximation for a 10-bit ADC (1023 ~= 1024): raw * 100 / 1024
  uint8_t inputPercent = ((rawInput * 25) + 255) >> 8;
  uint8_t filteredPercent = filter.update(inputPercent);

  Serial.print("Input: "); Serial.print(inputPercent); Serial.print("%");
  Serial.print("\tFiltered: "); Serial.print(filteredPercent); Serial.println("%");
  delay(100);
}
```

## API

### Constructors

- `DV_IirFilter8()` : Creates a filter with default smoothing (32)
- `DV_IirFilter8(uint8_t smoothing)` : Creates a filter with custom smoothing

### Methods

- `uint8_t update(uint8_t input)` : Updates the filter with a new input value
- `void setSmoothing(uint8_t smoothing)` : Sets the smoothing parameter
- `uint8_t getSmoothing()` : Gets the current smoothing parameter
- `uint8_t getValue()` : Gets the current filtered value
- `unsigned long getCount()` : Gets the number of updates
- `void reset()` : Resets the filter

## Smoothing Parameter

The smoothing parameter controls how much the filtered output "lags behind" the input, effectively filtering out noise and rapid changes.

- **Default value:** 32
- **Range:** 0-255

### How it works

At the API level, the filter manipulates 8-bit values (`0..255`).
Internally, it keeps a fixed-point accumulator and computes updates with higher precision before converting back to 8-bit output.

Conceptually, the update behaves like:
`output = output + ((input - output) * (256 - smoothing)) / 256`

- **Value 0:** No smoothing - the output instantly follows the input
- **Value 32:** Moderate smoothing - good balance for most sensor applications
- **Value 128:** Strong smoothing - output changes slowly, noise is heavily reduced
- **Value 255:** Maximum smoothing - output changes very gradually, the filter acts like a very slow "follower"

### Choosing the right value

| Smoothing Value | Use Case |
|---|---|
| 0-15 | Highly responsive, minimal filtering (fast sensors) |
| 16-64 | Good for typical sensor noise filtering |
| 65-150 | Strong smoothing, slower response time |
| 150-255 | Very slow response, maximum noise reduction |

### Example

```cpp
// Responsive filter for button debouncing
DV_IirFilter8 responsive(10);

// Balanced filter for general sensor use
DV_IirFilter8 balanced(32);

// Heavy smoothing for very noisy sensors
DV_IirFilter8 smooth(200);
```

You can change the smoothing value at runtime using `setSmoothing()`.

## Example

`examples/01-basic/01-basic.ino`
`examples/02-mid-smoothing/02-mid-smoothing.ino`
`examples/03-strong-smoothing/03-strong-smoothing.ino`

## License

MIT