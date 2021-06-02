#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/file_png.h"

const char *FILE_PATH = "images/_test.png";

void test_write() {
  Image *image = make_filled_image(10, 10, &PIXEL_BLUE);
  write_png(FILE_PATH, image);

  // check if file exists
  FILE *fp = fopen(FILE_PATH, "rb");
  assert(fp != NULL);

  free(image);
  fclose(fp);
}

void test_read() {
  Image *image = read_png(FILE_PATH);

  assert(image->width == 10);
  assert(image->height == 10);

  Pixel expected = PIXEL_BLUE;
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      // print_pixel(get_pixel_from_image(image, i, j));
      assert(are_pixels_equal(&expected, get_pixel_from_image(image, i, j)));
    }
  }

  // assert(remove(FILE_PATH) == 0);

  free(image);
}

int main(int argc, char *argv[]) {
  test_write();
  test_read();
  return EXIT_SUCCESS;
}