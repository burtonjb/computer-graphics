#include "pam.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

void write_pam(char *path, int width, int height) {
  FILE *fp = fopen(path, "wb");

  // Write the header to the PAM file
  fprintf(fp,
          "P7\nWIDTH %d\nHEIGHT %d\nDEPTH %d\nMAXVAL %d\nTUPLTYPE %s\nENDHDR\n",
          width, height, DEPTH, MAXVAL, TUPLTYPE);

  // write the image blob to the file
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      // static is to hackily re-use the allocated color array
      static uint8_t color[3];

      color[RED_INDEX] = i % (MAXVAL + 1);     /* red */
      color[GREEN_INDEX] = j % (MAXVAL + 1);   /* green */
      color[BLUE_INDEX] = 0 % (MAXVAL + 1);    /* blue */
      color[ALPHA_INDEX] = 255 % (MAXVAL + 1); /* alpha */

      fwrite(color, 1, 4, fp);
    }
  }
  fclose(fp);
}