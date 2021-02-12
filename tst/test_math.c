#include "../src/math.h"
#include <assert.h>
#include <stdio.h>

void add_test_cases() {
  // add test cases.
  assert(clamp_add(10, 0) == 10);
  assert(clamp_add(0, 10) == 10);
  assert(clamp_add(10, 10) == 20);

  assert(clamp_add(20, 10) == 30);
  assert(clamp_add(10, 20) == 30);

  assert(clamp_add(255, 0) == 255);
  assert(clamp_add(0, 255) == 255);
  assert(clamp_add(255, 255) == 255);
  assert(clamp_add(255, 254) == 255);
  assert(clamp_add(254, 255) == 255);

  assert(clamp_add(130, 100) == 230);
  assert(clamp_add(100, 130) == 230);
  assert(clamp_add(130, 130) == 255);

  assert(clamp_add(160, 100) == 255);
  assert(clamp_add(100, 160) == 255);
}

void sub_test_cases() {
  // sub test cases.
  assert(clamp_sub(10, 0) == 10);
  assert(clamp_sub(0, 10) == 0);
  assert(clamp_sub(10, 10) == 0);

  assert(clamp_sub(20, 10) == 10);
  assert(clamp_sub(10, 20) == 0);

  assert(clamp_sub(255, 0) == 255);
  assert(clamp_sub(0, 255) == 0);
  assert(clamp_sub(255, 255) == 0);
  assert(clamp_sub(255, 254) == 1);
  assert(clamp_sub(254, 255) == 0);

  assert(clamp_sub(130, 100) == 30);
  assert(clamp_sub(100, 130) == 0);
  assert(clamp_sub(130, 130) == 0);

  assert(clamp_sub(160, 100) == 60);
  assert(clamp_sub(100, 160) == 0);
}

void multi_test_cases() {
  // sub test cases.
  assert(clamp_multi(10, 0) == 0);
  assert(clamp_multi(0, 10) == 0);
  assert(clamp_multi(10, 10) == 100);

  assert(clamp_multi(20, 10) == 200);
  assert(clamp_multi(10, 20) == 200);

  assert(clamp_multi(20, 4) == 80);
  assert(clamp_multi(4, 20) == 80);

  assert(clamp_multi(100, 4) == 255);
  assert(clamp_multi(4, 100) == 255);

  assert(clamp_multi(255, 0) == 0);
  assert(clamp_multi(0, 255) == 0);
  assert(clamp_multi(255, 255) == 255);
  assert(clamp_multi(255, 254) == 255);
  assert(clamp_multi(254, 255) == 255);
}

void div_test_cases() {
  // sub test cases.
  assert(clamp_div(10, 1) == 10);
  assert(clamp_div(0, 10) == 0);
  assert(clamp_div(10, 10) == 1);

  assert(clamp_div(20, 10) == 2);
  assert(clamp_div(10, 20) == 0);

  assert(clamp_div(20, 4) == 5);
  assert(clamp_div(4, 20) == 0);

  assert(clamp_div(100, 4) == 25);
  assert(clamp_div(4, 100) == 0);

  assert(clamp_div(255, 1) == 255);
  assert(clamp_div(0, 255) == 0);
  assert(clamp_div(255, 255) == 1);
  assert(clamp_div(255, 254) == 1);
  assert(clamp_div(254, 255) == 0);
}

/*
 * Entry point for the math test cases
 */
int main(int argc, char *argv[]) {
  add_test_cases();
  sub_test_cases();
  multi_test_cases();
  div_test_cases();
}