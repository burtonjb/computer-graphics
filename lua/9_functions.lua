lib = require('image_lib')
utils = require('utils')
math = require('math')

-- file to demonstrate simple plotting of x->y functions

function plot(image, pixel, f, range_start, range_end, range_step) 
	x = range_start
	while x < range_end do
		y = f(x)
		lib.write_pixel_to_image(image, x, y, pixel)
		x = x + range_step
	end
end

function linear(x)
	return x
end

function quadratic(x)
	return x*x
end

function exponential(x)
	return math.exp(x)
end

image_size = 20

image = lib.make_filled_image(image_size, image_size, lib.PIXEL_WHITE)
plot(image, lib.PIXEL_GREEN, linear, 0, image_size, 1)
plot(image, lib.PIXEL_RED, quadratic, 0, image_size, 1)
plot(image, lib.PIXEL_BLUE, exponential, 0, image_size, 1)

lib.write_pam("../images/9_plotting_functions.pam", image)

