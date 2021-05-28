lib = require('image_lib')
utils = require('utils')

-- file to demonstrate image masking functionss

image = lib.make_filled_image(10, 10, lib.PIXEL_RED)

bottom_left = utils.create_point(1, 1)
top_right = utils.create_point(5, 5)

rect = lib.create_rectangle(bottom_left, top_right)

lib.draw_polygon(image, rect, lib.PIXEL_BLACK)

mask = lib.create_mask(image, lib.fptr_pixel_equals_filter(), lib.PIXEL_RED, utils.create_point(4,4))

lib.write_pam("../images/11_before_mask_op.pam", image)

lib.apply_to_mask(image, mask, lib.fptr_pixel_set(), lib.PIXEL_BLUE);

lib.write_pam("../images/11_post_mask_op.pam", image)

mask2 = lib.create_mask(image, lib.fptr_pixel_in_circle_filter(), utils.create_circle(6, 6, 2.5), utils.create_point(6, 6))

lib.apply_to_mask(image, mask2, lib.fptr_pixel_set(), lib.PIXEL_WHITE)

lib.write_pam("../images/post_mask_op_2.pam", image)

