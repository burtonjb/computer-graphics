#pragma once

#include <jpeglib.h>
#include <stdbool.h>
#include <stdint.h>

#include "image.h"

// write an image to a file using jpeg encoding. Quality is a value in [0, 100]
void write_jpeg(const char *path, const Image *image, int quality);

// read a jpeg from a file into memory
Image *read_jpeg(const char *path);
