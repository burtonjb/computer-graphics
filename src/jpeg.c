#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "jpeg.h"

void write_jpeg(const char *path, const Image *image, int quality) {

  // create JPG compression object
  struct jpeg_error_mgr
      jerr; // FIXME: this should actually be passed in, because having it here
            // is just ignoring error messages
  struct jpeg_compress_struct cinfo;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  FILE *fp = fopen(path, "wb");
  if (fp == NULL) {
    printf("Error: failed to open %s\n", path);
    return;
  }

  // specify destination data
  jpeg_stdio_dest(&cinfo, fp);

  // set up jpeg parameters
  cinfo.image_width = image->width;
  cinfo.image_height = image->height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, quality, TRUE);

  // start compression
  jpeg_start_compress(&cinfo, TRUE);

  uint16_t row_num = 0;
  // convert from image pixel representation to array representation
  JSAMPLE *color = malloc(sizeof(unsigned char) * 3 * image->width);

  // scan lines
  while (cinfo.next_scanline < cinfo.image_height) {
    for (int i = 0; i < image->width; i++) {
      color[i * 3 + 0] = image->pixels[row_num * image->width + i].red;
      color[i * 3 + 1] = image->pixels[row_num * image->width + i].green;
      color[i * 3 + 2] = image->pixels[row_num * image->width + i].blue;
    }
    jpeg_write_scanlines(&cinfo, &color, 1);
    row_num++;
  }

  // finish compression
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  fclose(fp);

  free(color);
  return;
}

Image *read_jpeg(const char *path) {
  // create a jpeg decompression object
  struct jpeg_error_mgr
      jerr; // FIXME: this should actually be passed in, because having it here
            // is just ignoring error messages
  struct jpeg_decompress_struct cinfo;
  jpeg_create_decompress(&cinfo);
  cinfo.err = jpeg_std_error(&jerr);

  FILE *fp = fopen(path, "rb");
  if (fp == NULL) {
    printf("Error: failed to open %s\n", path);
    return NULL;
  }

  // specify the source data
  jpeg_stdio_src(&cinfo, fp);

  // read the jpeg header
  jpeg_read_header(&cinfo, TRUE);

  // set parameters
  // Don't need to do this!

  // start decompression
  jpeg_start_decompress(&cinfo);

  const uint32_t row_stride = cinfo.output_width * cinfo.output_components;
  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo,
                                                 JPOOL_IMAGE, row_stride, 1);

  Image *out =
      make_filled_image(cinfo.output_width, cinfo.output_height, &PIXEL_CLEAR);

  // scan lines
  Pixel p;
  p.alpha = 255; // jpeg didn't support alpha when I tested it in paint.net, so
                 // hardcode alpha to 255 (fully opaque)
  while (cinfo.output_scanline < cinfo.output_height) {
    jpeg_read_scanlines(&cinfo, buffer, 1);
    for (int i = 0; i < out->width; i++) {
      p.red = (*buffer)[i * 3 + 0];
      p.green = (*buffer)[i * 3 + 1];
      p.blue = (*buffer)[i * 3 + 2];
      write_pixel_to_image(out, i, cinfo.output_scanline - 1, &p);
    }
  }

  // finish decompression
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(fp);

  return out;
}
