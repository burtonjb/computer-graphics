#include "file_util.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * These are values defined in the PAM file spec found here:
 * http://manpages.ubuntu.com/manpages/bionic/man5/pam.5.html There are other
 * values, but I'm just going to be using these for my examples.
 */
const uint8_t DEPTH = 4;
const uint8_t MAXVAL = 255;
const char *TUPLTYPE = "RGB_ALPHA";

const uint8_t RED_INDEX = 0;
const uint8_t GREEN_INDEX = 1;
const uint8_t BLUE_INDEX = 2;
const uint8_t ALPHA_INDEX = 3;

const size_t BUFFER_SIZE = 1000;

void write_pam(const char *path, const Image *image) {
  FILE *fp = fopen(path, "wb");

  // Write the header to the PAM file
  fprintf(fp,
          "P7\nWIDTH %d\nHEIGHT %d\nDEPTH %d\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
          image->width, image->height, DEPTH, MAXVAL, TUPLTYPE);

  // write the image blob to the file
  uint8_t color[4];
  Pixel p;

  for (int j = 0; j < image->height; j++) {
    for (int i = 0; i < image->width; i++) {
      p = image->pixels[i + j * image->width];

      color[RED_INDEX] = p.red;
      color[GREEN_INDEX] = p.green;
      color[BLUE_INDEX] = p.blue;
      color[ALPHA_INDEX] = p.alpha;

      fwrite(color, sizeof(color), 1, fp);
    }
  }
  fclose(fp);
}

#define FIND_STRING_START(varname, haystack, needle)                           \
  char *s_##varname = strstr(haystack, needle);                                \
  if (s_##varname == NULL) {                                                   \
    printf("Failed to find %s in %s", needle, haystack);                       \
    return NULL;                                                               \
  }

Image *read_pam(const char *path) {
  FILE *fp = fopen(path, "rb");

  if (fp == NULL) {
    printf("Failed to open file %s", path);
    return NULL;
  }

  char buffer[BUFFER_SIZE];

  fread(buffer, BUFFER_SIZE, 1, fp);

  int image_width = 0;
  int image_height = 0;
  char _[BUFFER_SIZE]; // seems pretty dangerous

  FIND_STRING_START(end_header_start, buffer, "ENDHDR\n")
  size_t end_header_start = s_end_header_start - buffer;
  int header_end_location = end_header_start + strlen("ENDHDR\n");

  FIND_STRING_START(image_width_start, buffer, "WIDTH ")
  sscanf(s_image_width_start, "%s %d\n", _, &image_width);

  FIND_STRING_START(image_height_start, buffer, "HEIGHT ")
  sscanf(s_image_height_start, "%s %d\n", _, &image_height);

  // search from the begining of the file until the end of the header
  fseek(fp, header_end_location, SEEK_SET);

  Image *out = malloc(2 * sizeof(uint16_t) +
                      (image_width * image_height * sizeof(Pixel)));

  out->width = image_width;
  out->height = image_height;

  int offset = 0;

  // values to store values read from the file
  uint8_t color[4];
  Pixel p;

  while (fp != NULL) {
    int size = fread(color, sizeof(color), 1, fp);

    p.red = color[RED_INDEX];
    p.green = color[GREEN_INDEX];
    p.blue = color[BLUE_INDEX];
    p.alpha = color[ALPHA_INDEX];

    out->pixels[offset++] = p;

    if (size == 0) {
      break;
    }
  }
  return out;
}