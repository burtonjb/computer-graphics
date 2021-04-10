lib = require('image_lib')
utils = require('utils')
math = require('math')

-- file to demonstrate various affine transformations


image = utils.create_another_test_image(1)

identity = utils.matrix()
lib.write_pam('../images/affine_start.pam', image)


-- identity (no-op) transform
identity = utils.matrix()
identity[1][1] = 1
identity[2][2] = 1
identity[3][3] = 1
m = utils.to_matrix_d(identity)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_identity_transform.pam", x)


-- translation - shift a little on both the x and y axis
shift = utils.matrix()
shift[1][1] = 1; shift[1][2] = 0; shift[1][3] = 20;
shift[2][1] = 0; shift[2][2] = 1; shift[2][3] = 10;
shift[3][1] = 0; shift[3][2] = 0; shift[3][3] = 1;
m = utils.to_matrix_d(shift)
x = lib.affine_transform(utils.create_another_test_image(1), m)
lib.write_pam("../images/affine_translation.pam", x)


-- reflection - flip over the y-axis
reflect = utils.matrix()
reflect[1][1] = 1 
reflect[2][2] = -1 -- flip the y-axis values
reflect[3][3] = 1

shift = utils.matrix()
shift[1][1] = 1; shift[1][2] = 0; shift[1][3] = 0;
shift[2][1] = 0; shift[2][2] = 1; shift[2][3] = -50;
shift[3][1] = 0; shift[3][2] = 0; shift[3][3] = 1;

multi_xform = utils.matrix_multiply(reflect, shift) -- the shift is required to move all the pixels to -50 before flipping them, otherwise the end up off the image

m = utils.to_matrix_d(multi_xform)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_reflection.pam", x)


-- rotation 90 degrees
-- some additional translation is required because the origin is weird (0, 0 is the top left corner). If its not included, pixels on the image are rotated off the image, causing nothing to be outputted
rotate_90 = utils.matrix()
rotate_90[1][1] = 0; rotate_90[1][2] = 1; rotate_90[1][3] = 50;
rotate_90[2][1] = -1; rotate_90[2][2] = 0; rotate_90[2][3] = 50;
rotate_90[3][3] = 1

m = utils.to_matrix_d(rotate_90)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_90_degree_reflection.pam", x)


-- rotation 45 degrees
-- some additional translation is required because the origin is weird (0, 0 is the top left corner). If its not included, pixels on the image are rotated off the image, causing nothing to be outputted
rotate_45 = utils.matrix()
rotate_45[1][1] = math.cos(math.pi/4); rotate_45[1][2] = -math.sin(math.pi/4); rotate_45[1][3] = 25;
rotate_45[2][1] = math.sin(math.pi/4); rotate_45[2][2] = math.cos(math.pi/4); rotate_45[2][3] = 25;
rotate_45[3][3] = 1

m = utils.to_matrix_d(rotate_45)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_45_degree_reflection.pam", x)


-- scale image - shrink by 50% on y axis
scale = utils.matrix()
scale[1][1] = 1; scale[2][2] = 0.5; 
scale[3][3] = 1

m = utils.to_matrix_d(scale)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_scale_y_.5.pam", x)


-- scale image - increase size by 50% on both x and y axis
scale = utils.matrix()
scale[1][1] = 1.5; scale[2][2] = 1.5; 
scale[3][3] = 1

m = utils.to_matrix_d(scale)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_scale_1.5x_and_y.pam", x)


-- shear - shear on x axis
shear_x = utils.matrix()
shear_x[1][1] = 1; shear_x[1][2] = 1.2;
shear_x[2][2] = 1;
shear_x[3][3] = 1

m = utils.to_matrix_d(shear_x)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_shear_x.pam", x)

-- shear - shear on y axis
shear_y = utils.matrix()
shear_y[1][1] = 1; shear_y[1][2] = 0;
shear_y[2][1] = 1.2; shear_y[2][2] = 1;
shear_y[3][3] = 1

m = utils.to_matrix_d(shear_y)
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_shear_y.pam", x)

-- shear x and y
m = utils.to_matrix_d(utils.matrix_multiply(shear_x, shear_y))
x = lib.affine_transform(image, m)
lib.write_pam("../images/affine_shear_x_and_y.pam", x)