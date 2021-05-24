lib = require('image_lib')
utils = require('utils')
math = require('math')

-- file to demonstrate various affine transformations


image = utils.create_test_image(0.2)

identity = utils.matrix()
lib.write_pam('../images/5_kernel_transform_initial.pam', image)


-- identity 
identity = utils.matrix()
identity[2][2] = 1
x = lib.kernel_transform(image, utils.to_matrix_d(identity))
lib.write_pam("../images/5_kernel_transform_identity.pam", x)


-- box blur. The 1/9 is to normalize the transformation 
blur = utils.matrix()
blur[1][1] = 1/9; blur[1][2] = 1/9; blur[1][3] = 1/9; 
blur[2][1] = 1/9; blur[2][2] = 1/9; blur[2][3] = 1/9; 
blur[3][1] = 1/9; blur[3][2] = 1/9; blur[3][3] = 1/9; 
x = lib.kernel_transform(image, utils.to_matrix_d(blur))
lib.write_pam("../images/5_kernel_transform_blur.pam", x)


-- box blur without normalization
blur = utils.matrix()
blur[1][1] = 1; blur[1][2] = 1; blur[1][3] = 1; 
blur[2][1] = 1; blur[2][2] = 1; blur[2][3] = 1; 
blur[3][1] = 1; blur[3][2] = 1; blur[3][3] = 1; 
x = lib.kernel_transform(image, utils.to_matrix_d(blur))
lib.write_pam("../images/5_kernel_transform_blur_no_normalization.pam", x)


-- gaussian blur (with normalization)
g_blur = utils.matrix()
g_blur[1][1] = 1/16; g_blur[1][2] = 2/16; g_blur[1][3] = 1/16; 
g_blur[2][1] = 2/16; g_blur[2][2] = 4/16; g_blur[2][3] = 2/16; 
g_blur[3][1] = 1/16; g_blur[3][2] = 2/16; g_blur[3][3] = 1/16; 
x = lib.kernel_transform(image, utils.to_matrix_d(g_blur))
lib.write_pam("../images/5_kernel_transform_gaussian_blur.pam", x)


-- sharpen
sharpen = utils.matrix()
sharpen[1][1] = 0; sharpen[1][2] = -1; sharpen[1][3] = 0; 
sharpen[2][1] = -1; sharpen[2][2] = 5; sharpen[2][3] = -1; 
sharpen[3][1] = 0; sharpen[3][2] = -1; sharpen[3][3] = 0; 
x = lib.kernel_transform(image, utils.to_matrix_d(sharpen))
lib.write_pam("../images/5_kernel_transform_sharpen.pam", x)


-- edge detection. Its actually much better if I use a greyscale image, but this works ok. 
edge = utils.matrix()
edge[1][1] = -1; edge[1][2] = -1; edge[1][3] = -1; 
edge[2][1] = -1; edge[2][2] = 8; edge[2][3] = -1; 
edge[3][1] = -1; edge[3][2] = -1; edge[3][3] = -1; 
x = lib.kernel_transform(image, utils.to_matrix_d(edge))
lib.write_pam("../images/5_kernel_transform_edge_detection.pam", x)