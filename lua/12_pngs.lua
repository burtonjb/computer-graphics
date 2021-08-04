lib = require('image_lib')
utils = require('utils')

-- file to demonstrate reading and writing pngs files

image = utils.create_test_image(50);

lib.write_png("../images/12_initial.png", image) -- save as a png
lib.write_pam("../images/12_initial.pam", image) -- save as a pam (to compare)

image2 = lib.read_png("../images/12_initial.png"); -- load the jpeg back into memory

lib.write_pixel_to_image(image2, 10, 10, lib.PIXEL_BLACK); -- change the image a bit

lib.write_png("../images/12_post_read_and_modifications.png", image2); -- save it back

