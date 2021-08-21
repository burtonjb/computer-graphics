#pragma once

// TODO: include compiler flags to optionally compile this file / link with
// libpng

#include <png.h>
#include <stdbool.h>
#include <stdint.h>

#include "image.h"

// write an image to a file using png encoding
void write_png(const char *path, const Image *image);

// read a png from a file into memory
Image *read_png(const char *path);
