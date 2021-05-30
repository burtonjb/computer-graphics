#pragma once

// TODO: include compiler flags to optionally compile this file / link with
// libjpeg

#include <jpeglib.h>
#include <stdbool.h>
#include <stdint.h>

#include "image.h"

void write_jpeg(const char *path, const Image *image, int quality);

Image *read_jpeg(const char *path);
