-- this needs to be run from the ./bin folder as lua doesn't really handle modules all that well. It needs to load 'image_lib' from the root of the working dir

lib = require ('image_lib')
i = lib.make_image(10, 10, 255, 0, 0, 255)
lib.write_file("../images/lua_red.pam", i)

j = lib.make_image(10, 10, 0, 255, 0, 255)
lib.write_file("../images/lua_green.pam", j)

k = lib.make_image(10, 10, 0, 0, 255, 255)
lib.write_file("../images/lua_blue.pam", k)