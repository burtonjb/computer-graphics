%module image_lib
%{
#include "../../src/file_util.h"
#include "../../src/pixel.h"
#include "../../src/image.h"
%}

%include "stdint.i"

%include "../src/file_util.h"
%include "../src/pixel.h"
%include "../src/image.h"
