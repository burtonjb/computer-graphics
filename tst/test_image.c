#include "../src/image.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_filled_image() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  assert(to_test->width == 10);
  assert(to_test->height == 10);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      assert(to_test->pixels[i + j * to_test->width].red == 255);
      assert(to_test->pixels[i + j * to_test->width].green == 0);
      assert(to_test->pixels[i + j * to_test->width].blue == 0);
      assert(to_test->pixels[i + j * to_test->width].alpha == 255);
    }
  }

  free(to_test);
}

void test_copy_image() {
  Image *orig = make_filled_image(10, 10, &PIXEL_RED);
  Image *to_test = copy_image(to_test);
  assert(to_test->width == 10);
  assert(to_test->height == 10);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      assert(to_test->pixels[i + j * to_test->width].red == 255);
      assert(to_test->pixels[i + j * to_test->width].green == 0);
      assert(to_test->pixels[i + j * to_test->width].blue == 0);
      assert(to_test->pixels[i + j * to_test->width].alpha == 255);
    }
  }

  free(to_test);
  free(orig);
}

void test_paste_to_image() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  Image *new = make_filled_image(5, 5, &PIXEL_BLUE);
  paste_to_image(new, to_test, 5, 5);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i < 5 || j < 5) {
        assert(to_test->pixels[i + j * to_test->width].red == 255);
        assert(to_test->pixels[i + j * to_test->width].blue == 0);
      } else {
        assert(to_test->pixels[i + j * to_test->width].red == 0);
        assert(to_test->pixels[i + j * to_test->width].blue == 255);
      }
      assert(to_test->pixels[i + j * to_test->width].green == 0);
      assert(to_test->pixels[i + j * to_test->width].alpha == 255);
    }
  }

  free(to_test);
  free(new);
}

void test_copy_from_image() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  Image *new = make_filled_image(5, 5, &PIXEL_BLUE);
  paste_to_image(new, to_test, 5, 5);
  Image *from = copy_from_image(to_test, 4, 4, 10, 10);

  assert(from->width == 6);
  assert(from->height == 6);

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i < 1 || j < 1) {
        assert(to_test->pixels[i + j * to_test->width].red == 255);
        assert(to_test->pixels[i + j * to_test->width].blue == 0);
      } else {
        assert(from->pixels[i + j * from->width].red == 0);
        assert(from->pixels[i + j * from->width].blue == 255);
      }
      assert(from->pixels[i + j * from->width].green == 0);
      assert(from->pixels[i + j * from->width].alpha == 255);
    }
  }

  free(to_test);
  free(new);
  free(from);
}

void test_pixel_transforms() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  Image *add = copy_image(to_test);
  Image *mult = copy_image(to_test);
  Image *matrix = copy_image(to_test);

  transform_pixels_constant(mult, pixel_div, 2);
  assert(mult->pixels[0].red == 255 / 2);

  transform_pixels_other(add, pixel_add, &PIXEL_GREEN);
  assert(add->pixels[0].red == 255);
  assert(add->pixels[0].green == 255);
  assert(add->pixels[0].blue == 0);

  Matrix3_uint8 A = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};
  transform_pixels_matrix(matrix, &A);
  assert(matrix->pixels[0].red == 0);
  assert(matrix->pixels[0].green == 0);
  assert(matrix->pixels[0].blue == 255);

  free(to_test);
  free(add);
  free(mult);
  free(matrix);
}

void test_affine_transform() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  Image *new = make_filled_image(1, 1, &PIXEL_GREEN);
  paste_to_image(new, to_test, 3, 3);

  assert(to_test->pixels[3 + 3 * 10].green == 255);

  Matrix3_d A = {{1, 0, 2}, {0, 1, 1}, {0, 0, 1}}; // matrix to translate (2, 1)

  Image *t = affine_transform(to_test, &A);

  assert(t->pixels[3 + 3 * 10].green == 0);
  assert(t->pixels[5 + 4 * 10].green == 255);

  free(to_test);
  free(new);
  free(t);
}

void test_kernel_transform() {
  Image *to_test = make_filled_image(10, 10, &PIXEL_RED);
  Image *new = make_filled_image(1, 1, &PIXEL_GREEN);
  paste_to_image(new, to_test, 3, 3);

  Matrix3_d A = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0}}; // Identity kernel, just check that it doesn't segfault

  Image *t = kernel_transform(to_test, &A);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      Pixel p = t->pixels[i + j * 10];

      if (i == 3 && j == 3) {
        assert(p.red == 0);
        assert(p.green == 255);
      } else {
        assert(p.red == 255);
        assert(p.green == 0);
      }
      assert(p.blue == 0);
    }
  }

  free(to_test);
  free(new);
  free(t);
}

void test_alpha_blend() {
  Image *red = make_filled_image(1, 1, &(Pixel){128, 3, 0, 128});
  Image *blue = make_filled_image(1, 1, &(Pixel){0, 7, 128, 128});

  Image *red_blue = alpha_blend(red, blue);
  Image *blue_red = alpha_blend(blue, red);

  assert(red_blue->pixels[0].red == 43);
  assert(red_blue->pixels[0].green == 6);
  assert(red_blue->pixels[0].blue == 85);
  assert(red_blue->pixels[0].alpha == 192);

  assert(blue_red->pixels[0].red == 85);
  assert(blue_red->pixels[0].green == 4);
  assert(blue_red->pixels[0].blue == 43);
  assert(blue_red->pixels[0].alpha == 192);
}

int main(int argc, char *argv[]) {
  test_filled_image();
  test_copy_image();
  test_paste_to_image();
  test_copy_from_image();
  test_pixel_transforms();
  test_affine_transform();
  test_kernel_transform();
  test_alpha_blend();
  return 0;
}