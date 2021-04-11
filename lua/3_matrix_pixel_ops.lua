lib = require('image_lib')
utils = require('utils')

-- file to demonstrate some of the pixel transformations options that you can do with a matrix

image = utils.create_test_image(0.2)
lib.write_pam("../images/pixels_start.pam", image)

-- identity transform image (doing nothing)
identity = utils.matrix()
identity[1][1] = 1
identity[2][2] = 1
identity[3][3] = 1
m = utils.to_matrix_int(identity)
x = lib.copy_image(image)
lib.transform_pixels_matrix(x, m, 1)
lib.write_pam("../images/pixels_identity_transform.pam", x)

-- pass through only the red/green channels (filtering the blue channel)
red_green_only = utils.matrix()
red_green_only[1][1] = 1
red_green_only[2][2] = 1
m = utils.to_matrix_int(red_green_only)
x = lib.copy_image(image)
lib.transform_pixels_matrix(x, m, 1)
lib.write_pam('../images/r_g_filtered_image.pam', x)

-- convert image to grey scale by adding all channel values (due to how poorly I implemented it in the C code, you can't use fractional values)
grey_scale = utils.matrix()
grey_scale[1][1] = 1;
grey_scale[1][2] = 1;
grey_scale[1][3] = 1
grey_scale[2][1] = 1;
grey_scale[2][2] = 1;
grey_scale[2][3] = 1
grey_scale[3][1] = 1;
grey_scale[3][2] = 1;
grey_scale[3][3] = 1
m = utils.to_matrix_int(grey_scale)
x = lib.copy_image(image)
lib.transform_pixels_matrix(x, m, 1)
lib.write_pam('../images/greyscale_image.pam', x)

-- swap the red and blue color channels (leaving green alone). Taking the red value and pasting it in blue, and the reverse. 
swap = utils.matrix()
swap[1][3] = 1
swap[2][2] = 1
swap[3][1] = 1
m = utils.to_matrix_int(swap)
x = lib.copy_image(image)
lib.transform_pixels_matrix(x, m, 1)
lib.write_pam('../images/swapped_color_channels.pam', x)