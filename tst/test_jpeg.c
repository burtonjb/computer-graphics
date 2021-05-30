#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/file_jpeg.h"

const char *FILE_PATH = "images/_test.jpg";

void test_write() {
  Image *image = make_filled_image(10, 10, &PIXEL_RED);
  write_jpeg(FILE_PATH, image, 100);

  // check if file exists
  FILE *fp = fopen(FILE_PATH, "rb");
  assert(fp != NULL);

  free(image);
  fclose(fp);
}

void test_read() {
  Image *image = read_jpeg(FILE_PATH);

  Pixel expected = (Pixel){
      254, 0, 0,
      255}; // jpeg is lossy, so read-back RGB values will be slightly different
  for (int i = 0; i < image->width; i++) {
    for (int j = 0; j < image->height; j++) {
      // print_pixel(get_pixel_from_image(image, i, j));
      assert(are_pixels_equal(&expected, get_pixel_from_image(image, i, j)));
    }
  }

  assert(remove(FILE_PATH) == 0);

  free(image);
}

int main(int argc, char *argv[]) {
  test_write();
  test_read();
  return EXIT_SUCCESS;
}