#pragma once

#include "image.h"

/*
 * Function to write to an image file in the PAM file format
 */
void write_pam(const char *path, const Image *image);

/*
 * Reads a pam file into memory (into an image struct).
 *
 * This method only supports pams created with the write pam method.
 * Definately unsafe.
 *  1. because I'm using strstr, which assumes null terminated strings, so can
 * probably cause a big-bang with special files.
 *  2. because I wrote it at 12AM
 *
 * USE AT YOUR OWN RISK, ONLY WITH FILES YOU CREATED.
 */
Image *read_pam(const char *path);