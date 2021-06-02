#pragma once

// TODO: include compiler flags to optionally compile this file / link with
// libpng

#include <png.h>
#include <stdbool.h>
#include <stdint.h>

#include "image.h"

void write_png(const char *path, const Image *image);

Image *read_png(const char *path);
