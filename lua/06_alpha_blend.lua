lib = require('image_lib')
utils = require('utils')

-- file to demonstrate alpha blendings

function create_image(pixel, x, y)
  local image = lib.make_filled_image(100, 100, utils.create_pixel(0, 0, 0, 0))
  local to_paste = lib.make_filled_image(50, 50, pixel)
  lib.paste_to_image(to_paste, image, x, y)
  return image
end

i_1 = create_image(utils.create_pixel(128, 0, 0, 128), 10, 10)
i_2 = create_image(utils.create_pixel(0, 128, 0, 128), 40, 40)
lib.write_pam("../images/6_alpha_i_1.pam", i_1)
lib.write_pam("../images/6_alpha_i_2.pam", i_2) 

out_1 = lib.alpha_blend(i_1, i_2)
out_2 = lib.alpha_blend(i_2, i_1)

lib.write_pam("../images/6_alpha_blend_out_1.pam", out_1)
lib.write_pam("../images/6_alpha_blend_out_2.pam", out_2) 
