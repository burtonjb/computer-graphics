#pragma once

#include <math.h>
#include <stdint.h>

#ifndef M_PI
// definition for PI, only defined if its not in math.h
#define M_PI 3.14159265358979323846
#endif

// helper declarations to convert from doubles to int types
#define d_to_uint8_t(arg) (uint8_t)(round(clamp_d(0, 255, arg)))
#define d_to_uint16_t(arg) (uint16_t)(round(arg))

// clamps a value between min, max
double clamp_d(double min, double max, double d);

// min and max methods
uint8_t max(uint8_t a, uint8_t b);
uint8_t min(uint8_t a, uint8_t b);

// basic arithmatic operations (+, -, *, /) but they will clamp the output value
// between the min and max values of an uint8_t (so clamped between 0 and 255)
uint8_t clamp_add(uint8_t a, uint8_t b);
uint8_t clamp_sub(uint8_t a, uint8_t b);
uint8_t clamp_multi(uint8_t a, uint8_t b);
uint8_t clamp_div(uint8_t a, uint8_t b);