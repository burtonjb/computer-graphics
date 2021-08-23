lib = require('image_lib')
utils = require('utils')

-- file to demonstrate reading and writing jpeg files
-- also test to see if reading/writing the same jpeg repeatedly will cause "jpeging" of the image 

quality = 100

image = utils.create_kernel_test_image(1);

lib.write_png("./images/10_jpg_test_start.png", image)
lib.write_jpeg("./images/10_jpg_test_start.jpg", image, quality)

for i = 1,10 do
    if i == 1 then
        x = image
    else 
        temp = lib.read_jpeg("./images/10_jpg_test_num_" .. i-1 .. ".jpg")
        print(lib.are_images_equal(x, temp))
        x = temp
        lib.print_pixel(lib.get_pixel_from_image(x, 0, 0))
    end
    lib.write_jpeg("./images/10_jpg_test_num_" .. i .. ".jpg", x, quality)
end