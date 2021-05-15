#include <assert.h>
#include <stdio.h>

#include "../src/image.h"
#include "../src/pixel.h"
#include "../src/shape.h"

void test_horizontal_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {0, 1, 10, 1};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_diagonal_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {0, 0, 10, 10};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_vertical_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {1, 0, 1, 10};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_horizontal_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {10, 1, 0, 1};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_diagonal_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {10, 10, 0, 0};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_vertical_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {1, 10, 1, 0};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_point() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {5, 5, 5, 5};

  rasterize_line_simple(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 5 && j == 5) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_horizontal_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {0, 1, 10, 1};

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      assert(are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
    }
  }

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_diagonal_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {0, 0, 10, 10};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_vertical_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {1, 0, 1, 10};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_horizontal_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {10, 1, 0, 1};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_diagonal_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {10, 10, 0, 0};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == i) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_vertical_backwards_line() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {1, 10, 1, 0};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 1) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

void test_bresenham_point() {
  Image *image = make_filled_image(10, 10, &PIXEL_WHITE);
  Line line = {5, 5, 5, 5};

  rasterize_line_bresenham(image, &line, &PIXEL_BLACK);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == 5 && j == 5) {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_BLACK));
      } else {
        assert(
            are_pixels_equal(get_pixel_from_image(image, i, j), &PIXEL_WHITE));
      }
    }
  }
}

int main(int argc, char *argv[]) {
  test_horizontal_line();
  test_diagonal_line();
  test_vertical_line();
  test_horizontal_backwards_line();
  test_diagonal_backwards_line();
  test_vertical_backwards_line();
  test_point();
  test_bresenham_horizontal_line();
  test_bresenham_diagonal_line();
  test_bresenham_vertical_line();
  test_bresenham_horizontal_backwards_line();
  test_bresenham_diagonal_backwards_line();
  test_bresenham_vertical_backwards_line();
  test_bresenham_point();
  return 0;
}
