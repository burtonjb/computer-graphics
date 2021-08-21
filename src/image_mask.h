#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "image.h"
#include "shape.h"

/* Constant defined for the max stack size/recusion depth for the create_mask
 * function. This might need to be tuned/adjusted, because I think the value is
 * a bit low (this value is only going to work for images which are less than
 * 1000 pixels, so like ~31x31 px max.
 */
#define MAX_STACK_SIZE 1000

/*
 * An image mask is a 2d array of booleans. A boolean will be set to true if the
 * corresponding pixel in the image should be selected.
 *
 * This way of representing an image mask is a bit ineffecient and also slightly
 * dangerous, but its pretty simple. One alternative is to have the mask have a
 * pointer to the source image, which makes sense to me (it seems slightly
 * suspect to share a mask across multiple images) but its not necessary and
 * doesn't really help with understanding the "mask" struct
 *
 * Other alternatives would be to have a "sparse" mask. This sparse mask would
 * be a set of (x,y) co-ordinates for pixels that are masked. The sparse mask
 * would have  asmaller memory footprint, but hashsets aren't something that's
 * built into C and it would be more complicated.
 */
typedef struct image_mask {
  uint16_t width;
  uint16_t height;
  bool is_pixel_masked[];
} ImageMask;

/* function signature for a "pixel filter" used to create an image mask
 * The (void *) type on the second argument isn't great, but based on assorted
 * research/some testing its better doing this and having all the functions that
 * match this signature all use (void *) because changing the type signature
 * makes GCC emit a lot of warnings and its probably UB. Normally I'd remove the
 * second arg and use a closure, but C doesn't support closures out-of-the-box.
 */
typedef bool (*pixel_filter)(Pixel *, void *, uint16_t x, uint16_t y);

/*
 * Creates an image mask by DepthFirstSearching through an image, checking if
 * the pixel_filter returns true. If the function returns true, then the top,
 * bottom, left and right neighbors of that pixel are added to the search and
 * the pixel is masked. If the filter is false, search will not continue for
 * that pixel.
 */
ImageMask *create_mask(const Image *image, pixel_filter filter,
                       void *filter_args, const Point initial);

/*
 * Applies a pixel operator on an image only for all pixels that are set in the
 * mask.
 */
void apply_to_mask(Image *image, const ImageMask *image_mask,
                   const pixel_op_on_pixel op, const Pixel *other);

void print_mask(const ImageMask *mask);

// -- ASSORTED TEST PIXEL FILTER FUNCTIONS. These can actually be extended in
// other files too if the function signature matches -- Returns true if pixels
// are equal (by value), false otherwise

// returns true if the pixel values (rgba) are equal. Used in the pixel filter
// function
bool pixel_equals_filter(
    Pixel *pixel,
    void *other, // other is of type pixel for this function
    uint16_t x, uint16_t y);

// The shape based masks are implemented in a dumb way.
// The initial point passed to the "create_mask" function has to be inside the
// shape, otherwise the DFS/BFS search that I do to find additional pixels won't
// work

// type definition for a rectangle, used for one of the image mask functions
typedef struct rectangle {
  uint16_t x_top_left;
  uint16_t y_top_left;
  uint16_t width;
  uint16_t height;
} Rectangle;

// returns true if the pixels are contained in the rectangle, otherwise false
bool pixel_in_rect_filter(Pixel *pixel,
                          void *other, // other is a rectangle for this function
                          uint16_t x, uint16_t y);

// returns true if the pixels are contained in a circle, false otherwise
bool pixel_in_circle_filter(Pixel *pixel,
                            void *other, // other is a circle for this function
                            uint16_t x, uint16_t y);
