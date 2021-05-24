lib = require('image_lib')
utils = require('utils')

-- file to demonstrate some of the slightly more advanced functionality of the image library

image_size = 100

image = lib.make_filled_image(image_size, image_size, utils.create_pixel(255, 0, 0, 255))
blue_image = lib.make_filled_image(image_size / 2, image_size / 2, utils.create_pixel(0, 0, 255, 255))

original_red = lib.copy_image(image)

lib.paste_to_image(blue_image, image, image_size / 2, image_size / 2) 

clipboard = lib.copy_from_image(image, image_size / 4, image_size / 4, 3 * image_size / 4, 3 * image_size / 4)

clipboard_pasted = lib.copy_image(image)

lib.paste_to_image(clipboard, clipboard_pasted, 0, 0)

lib.write_pam("../images/2_blue_onto_red.pam", image)
lib.write_pam("../images/2_original_red.pam", original_red)
lib.write_pam("../images/2_clipboard_op.pam", clipboard_pasted)


