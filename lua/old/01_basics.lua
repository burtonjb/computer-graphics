lib = require('image_lib')
utils = require('utils')

-- lua file to demonstrate the basics of creating images with the image library

image_size = 100

i = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 0, 0, 255))
lib.write_pam("../images/01_lua_red.pam", i)

j = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 0, 255))
lib.write_pam("../images/01_lua_green.pam", j)

k = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 255, 255))
lib.write_pam("../images/01_lua_blue.pam", k)

x = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 0, 255))
p = utils.create_pixel(255, 255, 255, 255)
lib.write_pixel_to_image(x, 5, 5, p)

pp = lib.get_pixel_from_image(x, 0, 0)
lib.print_pixel(pp)
print("")

lib.write_pam("../images/01_write_pixel.pam", x)

-- demonstrate reading from a pam file
read_after_write = lib.read_pam("../images/01_write_pixel.pam")

print(lib.are_images_equal(x, read_after_write) == 1);
