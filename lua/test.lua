-- this needs to be run from the ./bin folder as lua doesn't really handle modules all that well. It needs to load 'image_lib' from the root of the working dir
-- I've created a shell script - run_lua_scripts.sh in the root folder for running all scripts if needed

lib = require ('image_lib')

function create_pixel(r, g, b, a) 
  pixel = lib.Pixel()
  pixel.red = r
  pixel.green = g
  pixel.blue = b
  pixel.alpha = a
  return pixel
end

i = lib.make_filled_image(10, 10, create_pixel(255, 0, 0, 255))
lib.write_pam("../images/lua_red.pam", i)

j = lib.make_filled_image(10, 10, create_pixel(0, 255, 0, 255))
lib.write_pam("../images/lua_green.pam", j)

k = lib.make_filled_image(10, 10,create_pixel(0, 0, 255, 255))
lib.write_pam("../images/lua_blue.pam", k)

x = lib.make_filled_image(10, 10, create_pixel(0, 0, 0, 255))
p = create_pixel(255, 255, 255, 255)
lib.write_pixel_to_image(x, 5, 5, p)
lib.write_pam("../images/write_pixel.pam", x)