#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_png.h"
#include "image.h"

void write_png(const char *path, const Image *image) {

  FILE *fp = fopen(path, "wb");
  if (fp == NULL) {
    printf("Error: failed to open %s for writing png", path);
    return;
  }

  // FIXME: add in error handling for these calls
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info = png_create_info_struct(png);

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(png, info, image->width, image->height, 8, PNG_COLOR_TYPE_RGBA,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);

  png_bytep png_row = malloc(sizeof(png_byte) * image->width * 4);
  for (int y = 0; y < image->height; y++) {
    for (int x = 0; x < image->width; x++) {
      Pixel *p = get_pixel_from_image(image, x, y);
      png_row[x * 4] = p->red;
      png_row[x * 4 + 1] = p->green;
      png_row[x * 4 + 2] = p->blue;
      png_row[x * 4 + 3] = p->alpha;
    }
    png_write_row(png, png_row);
  }

  png_write_end(png, info);

  fclose(fp);
  free(png_row);
  png_destroy_write_struct(&png, &info);
}

Image *read_png(const char *path) {
  FILE *fp = fopen(path, "rb");

  if (fp == NULL) {
    printf("Error: failed to read %s in read_png", path);
    return NULL;
  }

  // FIXME: add in error handling
  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  png_infop info = png_create_info_struct(png);

  png_init_io(png, fp);

  png_read_info(png, info);

  uint16_t width = png_get_image_width(png, info);
  uint16_t height = png_get_image_height(png, info);
  uint16_t color_type = png_get_color_type(png, info);
  uint16_t bit_depth = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if (bit_depth == 16)
    png_set_strip_16(png);

  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  // TODO: I haven't actually tested this on other pngs, only ones generated
  // with the write_png method
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if (png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if (color_type == PNG_COLOR_TYPE_GRAY ||
      color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  png_bytep row_pointers = malloc(sizeof(png_bytep) * width);
  Image *image = make_filled_image(width, height, &PIXEL_CLEAR);

  Pixel p;
  for (int y = 0; y < image->height; y++) {
    png_read_row(png, row_pointers, row_pointers);
    for (int x = 0; x < image->width; x++) {
      p.red = row_pointers[x * 4 + 0];
      p.green = row_pointers[x * 4 + 1];
      p.blue = row_pointers[x * 4 + 2];
      p.alpha = row_pointers[x * 4 + 3];
      write_pixel_to_image(image, x, y, &p);
    }
  }

  fclose(fp);

  png_destroy_read_struct(&png, &info, NULL);

  free(row_pointers);

  return image;
}
