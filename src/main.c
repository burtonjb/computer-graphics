#include <math.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_util.h"
#include "image.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  Pixel background_color = {0, 0, 0, 128};

  Image *red_i = make_filled_image(100, 100, &background_color);
  Image *red = make_filled_image(40, 40, &(Pixel){128, 0, 0, 128});
  paste_to_image(red, red_i, 10, 10);

  Image *green_i = make_filled_image(100, 100, &background_color);
  Image *green = make_filled_image(40, 40, &(Pixel){0, 128, 0, 128});
  paste_to_image(green, green_i, 30, 30);

  Image *out = alpha_blend(red_i, green_i);
  Image *out2 = alpha_blend(green_i, red_i);

  write_pam("images/preblend_red.pam", red_i);
  write_pam("images/preblend_green.pam", green_i);

  write_pam("images/blend_green_onto_red.pam", out);
  write_pam("images/blend_red_onto_green.pam", out2);

  free(red_i);
  free(red);
  free(green_i);
  free(green);
  free(out);
  free(out2);

  return EXIT_SUCCESS;
}