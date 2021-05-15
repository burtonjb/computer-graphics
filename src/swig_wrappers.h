/*
 * File used to define some additional bindings to be used by swig. Mostly just
 * used to typematch for function pointers for now
 */

#include "../src/pixel.h"

/*
 * This macro is to automatically generate the pixel fptr operations.
 * method name is fptr_METHOD_NAME
 */
#define PIXEL_OP_FPTR_HANDLE(return_type, method_name)                         \
  return_type fptr_##method_name()

/*
 * Function pointer wrappers to work with swig. Not very clean, but easy to do
 */
PIXEL_OP_FPTR_HANDLE(int_op_on_pixel, pixel_multi);
PIXEL_OP_FPTR_HANDLE(int_op_on_pixel, pixel_div);
PIXEL_OP_FPTR_HANDLE(pixel_op_on_pixel, pixel_add);
PIXEL_OP_FPTR_HANDLE(pixel_op_on_pixel, pixel_sub);

#undef PIXEL_OP_FPTR_HANDL