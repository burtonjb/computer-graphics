#include <stdlib.h>

#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {

  Image *image = make_filled_image(100, 100, &PIXEL_RED);
  Image *image_copy = copy_image(image);

  fill_section(image, 50, 50,
               &PIXEL_BLUE); // fills the bottom left corner of the image
                             // with blue pixels

  write_pam("images/hello_world.pam", image);
  write_pam("images/copy.pam", image_copy);

  // while not 100% needed (the os will 'eventually' clean on exit) valgrind will not like it
  // if I leave these lying around
  free(image);
  free(image_copy);

  return EXIT_SUCCESS;
}