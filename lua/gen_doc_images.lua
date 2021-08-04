lib = require('image_lib')
utils = require('utils')

-- file to create the images used in the README

image_size = 25

-- used to generate the images for the pixel section of the readme
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 0, 0, 255))
lib.write_png('../docs/pixel_red.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 0, 255))
lib.write_png('../docs/pixel_green.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 255, 255))
lib.write_png('../docs/pixel_blue.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 255))
lib.write_png('../docs/pixel_grey.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 128))
lib.write_png('../docs/pixel_transparent_grey.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 0, 255))
lib.write_png('../docs/pixel_black.png', i)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 255, 255, 255))
lib.write_png('../docs/pixel_white.png', i)


-- used to generate the pixel operation images
p1 = utils.create_pixel(255, 0, 0, 255)
p2 = utils.create_pixel(0, 255, 0, 255)
p3 = utils.create_pixel(0, 0, 255, 255)

lib.pixel_add(p1, p2)
i = lib.make_filled_image(image_size, image_size, p1) -- r + g is yellow
lib.write_png('../docs/pixel_add_yellow.png', i)

lib.pixel_add(p1, p3)
i = lib.make_filled_image(image_size, image_size, p1)
lib.write_png('../docs/pixel_add_white.png', i)

lib.pixel_sub(p1, p2)
i = lib.make_filled_image(image_size, image_size, p1)
lib.write_png('../docs/pixel_sub_purple.png', i)

lib.pixel_div(p1, 2)
i = lib.make_filled_image(image_size, image_size, p1)
lib.write_png('../docs/pixel_div_muted_purple.png', i)


-- used to generate the pixel matrixs operation images
identity = utils.matrix()
identity[1][1] = 1; identity[2][2] = 1; identity[3][3] = 1 -- lua is 1-indexed instead of 0 indexed like most languages
m = utils.to_matrix_int(identity)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 255, 255))
lib.write_png('../docs/pixel_matrix_identity_orig.png', i)
lib.transform_pixels_matrix(i, m, 1)
lib.write_png('../docs/pixel_matrix_identity_post.png', i)

greyscale = utils.matrix()
for i=1,3 do
    for j = 1,3 do
    greyscale[i][j] = 1
    end
end
m = utils.to_matrix_int(greyscale)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 255, 255))
lib.write_png('../docs/pixel_matrix_greyscale_orig.png', i)
lib.transform_pixels_matrix(i, m, 3)
lib.write_png('../docs/pixel_matrix_greyscale_post.png', i)

swap_r_g = utils.matrix()
swap_r_g[1][2] = 1; swap_r_g[2][1] = 1; swap_r_g[3][3] = 1;
m = utils.to_matrix_int(swap_r_g)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 255, 255))
lib.write_png('../docs/pixel_matrix_swap_r_g_orig.png', i)
lib.transform_pixels_matrix(i, m, 1)
lib.write_png('../docs/pixel_matrix_swap_r_g_post.png', i)

filter_g_b = utils.matrix()
filter_g_b[2][2] = 1; filter_g_b[3][3] = 1;
m = utils.to_matrix_int(filter_g_b)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 255, 255, 255))
lib.write_png('../docs/pixel_matrix_filter_g_b_orig.png', i)
lib.transform_pixels_matrix(i, m, 1)
lib.write_png('../docs/pixel_matrix_filter_g_b_post.png', i)

rebalance = utils.matrix()
rebalance[1][1] = 1; rebalance[2][2] = 2; rebalance[3][3] = 3
m = utils.to_matrix_int(rebalance)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 255))
lib.write_png('../docs/pixel_matrix_rebalance_orig.png', i)
lib.transform_pixels_matrix(i, m, 1)
lib.write_png('../docs/pixel_matrix_rebalance_post.png', i)

filter_then_greyscale = utils.matrix_multiply(greyscale, filter_g_b)
utils.print_matrix(filter_then_greyscale)
m = utils.to_matrix_int(filter_then_greyscale)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 255))
lib.write_png('../docs/pixel_matrix_filter_then_greyscale_orig.png', i)
lib.transform_pixels_matrix(i, m, 3)
lib.write_png('../docs/pixel_matrix_filter_then_greyscale_post.png', i)

greyscale_then_filter = utils.matrix_multiply(filter_g_b, greyscale)
utils.print_matrix(greyscale_then_filter)
m = utils.to_matrix_int(greyscale_then_filter)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 255))
lib.write_png('../docs/pixel_matrix_greyscale_then_filter_orig.png', i)
lib.transform_pixels_matrix(i, m, 3)
lib.write_png('../docs/pixel_matrix_greyscale_then_filter_post.png', i)
