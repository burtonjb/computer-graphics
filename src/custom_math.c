#include "custom_math.h"

double clamp_d(double min, double max, double d) {
  if (d < min) {
    return min;
  } else if (d > max) {
    return max;
  } else {
    return d;
  }
}

uint8_t max(uint8_t a, uint8_t b) { return a > b ? a : b; }

uint8_t min(uint8_t a, uint8_t b) { return a < b ? a : b; }

uint8_t clamp_add(uint8_t a, uint8_t b) {
  // check for overflow
  if (a > UINT8_MAX - b || b > UINT8_MAX - a) {
    return UINT8_MAX;
  }
  return a + b;
}

uint8_t clamp_sub(uint8_t a, uint8_t b) {
  if (a < b) {
    return 0;
  }
  return a - b;
}

uint8_t clamp_multi(uint8_t a, uint8_t b) {
  if (a == 0 || b == 0) {
    return 0;
  }
  if (a > UINT8_MAX / b || b > UINT8_MAX / a) {
    return UINT8_MAX;
  }
  return a * b;
}

uint8_t clamp_div(uint8_t a, uint8_t b) {
  return a / b; // super easy, this can't underflow!
}