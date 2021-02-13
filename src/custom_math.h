#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdint.h>

uint8_t max(uint8_t a, uint8_t b);
uint8_t min(uint8_t a, uint8_t b);

uint8_t clamp_add(uint8_t a, uint8_t b);
uint8_t clamp_sub(uint8_t a, uint8_t b);
uint8_t clamp_multi(uint8_t a, uint8_t b);
uint8_t clamp_div(uint8_t a, uint8_t b);