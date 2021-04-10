-- lua util functions
local utils = {}

lib = require('image_lib')

function utils.create_pixel(r, g, b, a)
    pixel = lib.Pixel()
    pixel.red = r
    pixel.green = g
    pixel.blue = b
    pixel.alpha = a
    return pixel
end

return utils
