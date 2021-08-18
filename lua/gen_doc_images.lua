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

greyscale_then_filter = utils.matrix_multiply(filter_g_b, greyscale)
utils.print_matrix(greyscale_then_filter)
m = utils.to_matrix_int(greyscale_then_filter)
i = lib.make_filled_image(image_size, image_size, utils.create_pixel(128, 128, 128, 255))
lib.write_png('../docs/pixel_matrix_greyscale_then_filter_orig.png', i)
lib.transform_pixels_matrix(i, m, 3)
lib.write_png('../docs/pixel_matrix_greyscale_then_filter_post.png', i)

-- generate inverse matrices and images
m = utils.to_matrix_d(swap_r_g)
inv_m = utils.to_matrix_d(utils.matrix())
lib.invert_matrix_d(m, inv_m)
product = utils.to_matrix_d(utils.matrix())
lib.matrix_multiply_d(m, inv_m, product)
lib.print_matrix(m); lib.print_matrix(inv_m); lib.print_matrix(product);

m_int = utils.to_matrix_int(utils.matrix())
inv_m_int = utils.to_matrix_int(utils.matrix())

lib.to_matrix_uint8_t(m, m_int)
lib.to_matrix_uint8_t(inv_m, inv_m_int)

i = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 255, 255))
lib.write_png('../docs/pixel_matrix_product_orig.png', i)
lib.transform_pixels_matrix(i, m_int, 1)
lib.write_png('../docs/pixel_matrix_product_forward.png', i)
lib.transform_pixels_matrix(i, inv_m_int, 1)
lib.write_png('../docs/pixel_matrix_product_inverse.png', i)

-- generate image from hsv
--[[ --skipping this, takes too long and too much space (and I think its buggy)
for hue = 0, 360, 30 do
    for sat = 0, 1, 0.5 do
        for value = 0, 1, 0.5 do
            p = lib.from_hsv(hue, sat, value, 255)
            i = lib.make_filled_image(image_size, image_size, p)
            f_name = string.format("./docs/pixel_from_hsv_%d_%.2f_%.2f.png", hue, sat, value)
            lib.write_png("." .. f_name, i)
            -- auto generate the image markdown table
            s = string.format("|(%d, %.2f, %.2f)|(%d, %d, %d)|![](%s)|", hue, sat, value, p.red, p.green, p.blue, f_name)
            print(s)
        end
    end
end
--]]
p = lib.from_hsv(360, 1, 1, 255)
i = lib.make_filled_image(image_size, image_size, p)
lib.write_png('../docs/pixel_from_hsv.png', i)

-- create example pam file
i = lib.make_filled_image(10, 10, utils.create_pixel(128, 128, 128, 255))
lib.write_pam('../docs/example_pam_file.pam', i)
i = lib.make_filled_image(100, 100, utils.create_pixel(128, 128, 128, 255))
lib.write_pam('../docs/example_large_pam_file.pam', i)
lib.write_png('../docs/example_large_png.png', i)

-- generate alpha blended images
function create_image(pixel, x, y)
    local image = lib.make_filled_image(100, 100, utils.create_pixel(0, 0, 0, 0))
    local to_paste = lib.make_filled_image(50, 50, pixel)
    lib.paste_to_image(to_paste, image, x, y)
    return image
end
  
i_1 = create_image(utils.create_pixel(128, 0, 0, 128), 10, 10)
i_2 = create_image(utils.create_pixel(0, 128, 0, 128), 40, 40)
lib.write_png("../docs/preblend_red.png", i_1)
lib.write_png("../docs/preblend_green.png", i_2) 

out_1 = lib.alpha_blend(i_1, i_2)
out_2 = lib.alpha_blend(i_2, i_1)

lib.write_png("../docs/blend_green_onto_red.png", out_1)
lib.write_png("../docs/blend_red_onto_green.png", out_2) 

-- generate affine transformation images
identity = utils.matrix()
identity[1][1] = 1
identity[2][2] = 1
identity[3][3] = 1
m = utils.to_matrix_d(identity)
image = utils.create_another_test_image(1)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_identity.png", x)

translate = utils.matrix()
translate[1][1] = 1; translate[1][3] = 20;
translate[2][2] = 1; translate[2][3] = 30;
translate[3][3] = 1;
m = utils.to_matrix_d(translate)
image = utils.create_another_test_image(1)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_translation.png", x)

reflect = utils.matrix()
reflect[1][1] = 1 
reflect[2][2] = -1 -- flip the y-axis values
reflect[3][3] = 1
shift = utils.matrix()
shift[1][1] = 1; shift[1][2] = 0; shift[1][3] = 0;
shift[2][1] = 0; shift[2][2] = 1; shift[2][3] = -50;
shift[3][1] = 0; shift[3][2] = 0; shift[3][3] = 1;
multi_xform = utils.matrix_multiply(reflect, shift) -- the shift is required to move all the pixels to -50 before flipping them, otherwise the end up off the image
m = utils.to_matrix_d(multi_xform)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_reflect.png", x)

rotate_90 = utils.matrix() -- some additional translation is required because the origin is weird (0, 0 is the top left corner). If its not included, pixels on the image are rotated off the image, causing nothing to be outputted
rotate_90[1][1] = 0; rotate_90[1][2] = 1; rotate_90[1][3] = 50;
rotate_90[2][1] = -1; rotate_90[2][2] = 0; rotate_90[2][3] = 50;
rotate_90[3][3] = 1
m = utils.to_matrix_d(rotate_90)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_rotate_90.png", x)

rotate_45 = utils.matrix() -- some additional translation is required because the origin is weird (0, 0 is the top left corner). If its not included, pixels on the image are rotated off the image, causing nothing to be outputted
rotate_45[1][1] = math.cos(math.pi/4); rotate_45[1][2] = -math.sin(math.pi/4); rotate_45[1][3] = 25;
rotate_45[2][1] = math.sin(math.pi/4); rotate_45[2][2] = math.cos(math.pi/4); rotate_45[2][3] = 25;
rotate_45[3][3] = 1
m = utils.to_matrix_d(rotate_45)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_rotate_45.png", x)

shear_x = utils.matrix()
shear_x[1][1] = 1; shear_x[1][2] = 1.2;
shear_x[2][2] = 1;
shear_x[3][3] = 1
m = utils.to_matrix_d(shear_x)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_shear_x.png", x)

shear_y = utils.matrix()
shear_y[1][1] = 1; shear_y[1][2] = 0;
shear_y[2][1] = 1.2; shear_y[2][2] = 1;
shear_y[3][3] = 1
m = utils.to_matrix_d(shear_y)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_shear_y.png", x)

m = utils.to_matrix_d(utils.matrix_multiply(shear_x, shear_y))
lib.print_matrix(m)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_shear_x_y.png", x)

scale_half = utils.matrix()
scale_half[1][1] = 1; scale_half[2][2] = 0.5; 
scale_half[3][3] = 1
m = utils.to_matrix_d(scale_half)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_scale_0.5y.png", x)

scale_one_point_five = utils.matrix()
scale_one_point_five[1][1] = 1.5; scale_one_point_five[2][2] = 1.5; 
scale_one_point_five[3][3] = 1
m = utils.to_matrix_d(scale_one_point_five)
x = lib.affine_transform(image, m)
lib.write_png("../docs/affine_scale_1.5x_1.5y.png", x)

-- generate transformations using the inverting affine transforms
image = utils.create_another_test_image(1)

m = utils.to_matrix_d(identity)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_identity.png", x)

m = utils.to_matrix_d(translate)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_translation.png", x)

m = utils.to_matrix_d(multi_xform)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_reflect.png", x)

m = utils.to_matrix_d(rotate_90)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_rotate_90.png", x)

m = utils.to_matrix_d(rotate_45)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_rotate_45.png", x)

m = utils.to_matrix_d(shear_x)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_shear_x.png", x)

m = utils.to_matrix_d(shear_y)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_shear_y.png", x)

m = utils.to_matrix_d(utils.matrix_multiply(shear_x, shear_y))
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_shear_x_y.png", x)

m = utils.to_matrix_d(scale_half)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_scale_0.5y.png", x)

m = utils.to_matrix_d(scale_one_point_five)
x = lib.inverting_affine_transform(image, m, lib.NEAREST_NEIGHBOR)
lib.write_png("../docs/invert_affine_scale_1.5x_1.5y.png", x)