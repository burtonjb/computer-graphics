#pragma once

#include "image.h"

/*
 * Function to write to an image file.
 * Eventually will take in an object to draw, but for now only writes a
 * hardcoded file
 */
void write_pam(const char *path, const Image *image);