#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "custom_math.h"
#include "file_jpeg.h"
#include "file_pam.h"
#include "file_png.h"
#include "image.h"
#include "image_mask.h"
#include "polygon.h"
#include "shape.h"

/*
 * Entry point to the application. Called on program start.
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv; // remove "unused parameter" compiler warnings

  Image *image = make_filled_image(10, 10, &PIXEL_RED);

  Point bottom_left = (Point){1, 1};
  Point top_right = (Point){5, 5};

  Polygon *poly = create_rectangle(&bottom_left, &top_right);

  draw_polygon(image, poly, &PIXEL_BLACK);

  ImageMask *mask = create_mask(image, pixel_equals_filter, (void *)&PIXEL_RED,
                                (Point){4, 4});

  print_mask(mask);

  write_pam("images/before_mask_op.pam", image);

  write_png("images/write_png_test.png", image);

  apply_to_mask(image, mask, pixel_set, &PIXEL_BLUE);

  write_pam("images/post_mask_op.pam", image);

  ImageMask *mask2 = create_mask(image, pixel_in_circle_filter,
                                 (void *)&(Circle){6, 6, 2.5}, (Point){6, 6});

  print_mask(mask2);

  apply_to_mask(image, mask2, pixel_set, &PIXEL_WHITE);

  write_pam("images/post_mask_op_2.pam", image);

  printf("Done!\n");

  free(poly);
  free(mask);
  free(image);
  return EXIT_SUCCESS;
}
