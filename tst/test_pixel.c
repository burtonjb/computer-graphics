#include "../src/pixel.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void check_pixel(Pixel *pixel, uint8_t red, uint8_t green, uint8_t blue) {
  // checks that the pixel has the expected colors
  assert(pixel->red == red);
  assert(pixel->green == green);
  assert(pixel->blue == blue);
}

void test_from_hsv() {
  check_pixel(from_hsv(0, 0, 0, 255), 0, 0, 0);       // black
  check_pixel(from_hsv(0, 1, 1, 255), 255, 0, 0);     // red
  check_pixel(from_hsv(120, 1, 1, 255), 0, 255, 0);   // green
  check_pixel(from_hsv(240, 1, 1, 255), 0, 0, 255);   // blue
  check_pixel(from_hsv(0, 0, 1, 255), 255, 255, 255); // white
  // FIXME: include case for non-primary colors
}

int main(int argc, char *argv[]) {
  test_from_hsv();
  return 0;
}