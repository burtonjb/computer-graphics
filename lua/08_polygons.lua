lib = require('image_lib')
utils = require('utils')

-- file to demonstrate drawing a couple simple polygons

image = lib.make_filled_image(50, 50, lib.PIXEL_GREEN);

triangle = lib.create_triangle(utils.create_point(0, 0), utils.create_point(10, 10), utils.create_point(0, 10));
square = lib.create_rectangle(utils.create_point(5, 5), utils.create_point(25, 25));

lib.draw_polygon(image, triangle, lib.PIXEL_RED);
lib.draw_polygon(image, square, lib.PIXEL_BLUE);

lib.write_pam("../images/08_polygons.pam", image);
