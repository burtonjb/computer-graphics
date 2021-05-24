%module image_lib
%{
#include "../../src/custom_math.h"
#include "../../src/linear_algebra.h"
#include "../../src/file_util.h"
#include "../../src/pixel.h"
#include "../../src/image.h"
#include "../../src/shape.h"
#include "../../src/polygon.h"
#include "../../src/jpeg.h"
#include "../../src/swig_wrappers.h"
%}

%include <typemaps.i>
%include <stdint.i>

%include "../src/linear_algebra.h"
%include "../src/file_util.h"
%include "../src/pixel.h"
%include "../src/image.h"
%include "../src/shape.h"
%include "../src/polygon.h"
%include "../src/jpeg.h"
%include "../src/swig_wrappers.h"