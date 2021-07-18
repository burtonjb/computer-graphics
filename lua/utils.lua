-- lua util functions
local utils = {}

local lib = require('image_lib')

function utils.create_pixel(r, g, b, a)
    local pixel = lib.Pixel()
    pixel.red = r
    pixel.green = g
    pixel.blue = b
    pixel.alpha = a
    return pixel
end

function utils.create_line(x0, y0, x1, y1)
    local line = lib.Line()
    line.x0 = x0
    line.y0 = y0
    line.x1 = x1
    line.y1 = y1
    return line
end

function utils.create_circle(x, y, r)
    local circle = lib.Circle()
    circle.x = x
    circle.y = y
    circle.radius = r
    return circle
end

function utils.create_rectangle(x, y, width, height) -- x, y denote the top-left corner
    local rect = lib.Rectangle()
    rect.x_top_left = x
    rect.y_top_left = y
    rect.width = width
    rect.height = height
    return rect
end

function utils.create_point(x, y)
    local point = lib.Point()
    point.x = x
    point.y = y
    return point
end

function utils.matrix()
    local out = {}
    for i = 1, 3 do
        out[i] = {}
        for j = 1, 3 do
            out[i][j] = 0
        end
    end
    return out
end

function utils.matrix_multiply(m1, m2)
    local out = utils.matrix()
    for i = 1, 3 do
        for j = 1, 3 do
            local num = 0
            for k = 1, 3 do
                num = num + m1[i][k] * m2[k][j]
            end
            out[i][j] = num
        end
    end
    return out
end

-- pass this a 3x3 grid to make a 3x3 c matrix
function utils.to_matrix_int(m)
    local out = lib.identity_matrix_uint8_t()
    for i = 1, 3 do
        for j = 1, 3 do
            lib.set_matrix_value_uint8_t(out, i - 1, j - 1, m[i][j])
        end
    end
    return out
end

function utils.to_matrix_d(m)
    local out = lib.identity_matrix_double()
    for i = 1, 3 do
        for j = 1, 3 do
            lib.set_matrix_value_double(out, i - 1, j - 1, m[i][j])
        end
    end
    return out
end

function utils.create_test_image(scale)
    local image = lib.make_filled_image(100, 100, utils.create_pixel(255 * scale, 255 * scale, 255 * scale, 255))
    local red = lib.make_filled_image(50, 50, utils.create_pixel(255 * scale, 0, 0, 255))
    local green = lib.make_filled_image(50, 50, utils.create_pixel(0, 255 * scale, 0, 255))
    local blue = lib.make_filled_image(50, 50, utils.create_pixel(0, 0, 255 * scale, 255))

    lib.paste_to_image(red, image, 50, 0)
    lib.paste_to_image(green, image, 0, 50)
    lib.paste_to_image(blue, image, 50, 50)

    return image
end

function utils.create_another_test_image(scale)
    local image = lib.make_filled_image(100, 100, utils.create_pixel(0, 0, 0, 0))
    local red = lib.make_filled_image(10, 20, utils.create_pixel(255 * scale, 0, 0, 255))
    local green = lib.make_filled_image(10, 10, utils.create_pixel(0, 255 * scale, 0, 255))

    lib.paste_to_image(red, image, 10, 10)
    lib.paste_to_image(green, image, 10, 30)

    return image
end

return utils
