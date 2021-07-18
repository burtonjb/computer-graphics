/*
See header file for why I have this slightly hacky file.
*/

#include "swig_wrappers.h"

#define PIXEL_OP_FPTR_IMPL(return_type, method_name)                           \
  return_type fptr_##method_name() { return method_name; }

PIXEL_OP_FPTR_IMPL(int_op_on_pixel, pixel_multi);
PIXEL_OP_FPTR_IMPL(int_op_on_pixel, pixel_div);
PIXEL_OP_FPTR_IMPL(pixel_op_on_pixel, pixel_add);
PIXEL_OP_FPTR_IMPL(pixel_op_on_pixel, pixel_sub);
PIXEL_OP_FPTR_IMPL(pixel_op_on_pixel, pixel_set);
PIXEL_OP_FPTR_IMPL(pixel_filter, pixel_equals_filter);
PIXEL_OP_FPTR_IMPL(pixel_filter, pixel_in_circle_filter);
PIXEL_OP_FPTR_IMPL(pixel_filter, pixel_in_rect_filter);

#undef PIXEL_OP_FPTR_IMPL
