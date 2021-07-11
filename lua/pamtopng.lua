-- janky lua file to convert from the pam (simple, but undisplayable) file format 
-- to the png file format so that the images can be viewed.
--
-- usage is lua pamtopng INPUT_PATH OUTPUT_PATH

lib = require('image_lib')
utils = require('utils')

if arg[1] == nil or arg[2] == nil then
 print("no input arg, exiting")
 return
end

input_file = arg[1]
output_file = arg[2]

image = lib.read_pam(input_file)
output = lib.write_png(output_file, image)

