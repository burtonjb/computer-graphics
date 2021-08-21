lib = require('image_lib')
utils = require('utils')

-- file to demonstrate reading and writing jpeg files

image = utils.create_test_image(50);

lib.write_jpeg("../images/10_initial.jpeg", image, 100) -- save as a jpeg
lib.write_pam("../images/10_initial.pam", image) -- save as a pam (to compare)

image2 = lib.read_jpeg("../images/10_initial.jpeg"); -- load the jpeg back into memory

lib.write_pixel_to_image(image2, 10, 10, lib.PIXEL_BLACK); -- change the image a bit

lib.write_jpeg("../images/10_post_read_and_modifications.jpeg", image2, 100); -- save it back

