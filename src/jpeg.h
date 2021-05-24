#pragma once

#include <jpeglib.h>

#include "common.h"
#include "image.h"

void write_jpeg(const char *path, const Image *image, int quality);

Image *read_jpeg(const char *path);
