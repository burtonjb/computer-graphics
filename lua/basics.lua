-- this needs to be run from the ./bin folder as lua doesn't really handle modules all that well. It needs to load 'image_lib' from the root of the working dir
-- I've created a shell script - run_lua_scripts.sh in the root folder for running all scripts if needed
lib = require('image_lib')
utils = require('utils')

image_size = 100

i = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 0, 0, 255))
lib.write_pam("../images/lua_red.pam", i)

j = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 255, 0, 255))
lib.write_pam("../images/lua_green.pam", j)

k = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 255, 255))
lib.write_pam("../images/lua_blue.pam", k)

x = lib.make_filled_image(image_size, image_size, utils.create_pixel(0, 0, 0, 255))
p = utils.create_pixel(255, 255, 255, 255)
lib.write_pixel_to_image(x, 5, 5, p)

pp = lib.get_pixel_from_image(x, 0, 0)
lib.print_pixel(pp)
print("")

lib.write_pam("../images/write_pixel.pam", x)
