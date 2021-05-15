lib = require('image_lib')
utils = require('utils')

-- file to demonstrate simple shapes, e.g. lines and circles. 
-- other polygons (rectangles, triangles) can be drawn with lines and I'll include function somewhere to demonstrate it

line_image = lib.make_filled_image(50, 50, utils.create_pixel(0, 255, 0, 255));
line1 = utils.create_line(0, 0, 25, 25);
line2 = utils.create_line(25, 30, 0, 5);
line3 = utils.create_line(0, 0, 0, 25);
line4 = utils.create_line(25, 25, 25, 35);
line5 = utils.create_line(0, 0, 25, 0);

lib.rasterize_line_simple(line_image, line1, lib.PIXEL_BLUE);
lib.rasterize_line_simple(line_image, line2, lib.PIXEL_RED);
lib.rasterize_line_simple(line_image, line3, lib.PIXEL_WHITE);
lib.rasterize_line_bresenham(line_image, line4, lib.PIXEL_BLACK);
lib.rasterize_line_bresenham(line_image, line5, utils.create_pixel(255, 255, 0, 255)) -- hex for yellow

lib.write_pam("../images/7_lines.pam", line_image);

circle_image = lib.make_filled_image(50, 50, lib.PIXEL_GREEN);
circle_1 = utils.create_circle(25, 25, 10);
circle_2 = utils.create_circle(15, 15, 10);
circle_3 = utils.create_circle(35, 35, 10);

lib.rasterize_circle_simple(circle_image, circle_1, lib.PIXEL_RED, 0.001);
lib.rasterize_circle_midpoint(circle_image, circle_2, lib.PIXEL_BLUE);
lib.rasterize_circle_bresenham(circle_image, circle_3, lib.PIXEL_BLACK);

lib.write_pam("../images/7_circles.pam", circle_image);
