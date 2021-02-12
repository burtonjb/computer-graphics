# 2D graphics in C

This is a project/documentation about my findings for 2d graphics. 

I'm doing this because I think C is cool, and I think 2d graphics is interesting - there's a lot of linear algebra.

## Color and pixels

The color model that most computers work with (sort-of, I'm actually not super knowledgable in this) is an additive color model, with the base colors being red, green, and blue. 
A pixel is made of a 3-tuple of these colors to light up a portion of the screen. Adding more colors together would make something lighter, and adding all of them together makes white. The absence of any color leaves a black pixel. 

A pixel uses a tuple of RGB, with a possible 4th value for 'alpha' (basically transparency). Each color has a 'depth' which is how many possible values there are for that color.
e.g. if a pixel had a red depth of 2, then the pixel could either be red or not. I'm going to use 1 byte for each color for each pixel, mostly because I'm making small images and just testing stuff out, but trying different values can be interesting.

In this project, a pixel will be a 4-tuple with values ranging from 0-255 (or 0 - 0xFF in hex). This means that a pixel will take up to 4 bytes (32 bits) which is a little big. 

And as a side note, an alpha of 255 is not transparent and an alpha of 0 is fully transparent.

## Coordinates 

Computer graphics coordinate systems are slightly different than what I'm used to. 

The top-left corner of the screen is the origin, and then the bottom-right is the (MAX_X, MAX_Y) coordinate, depending on the resolution of the screen. 

## Graphics file format

The final topic for the initial commit is picking a graphics file format. I want to be able to write out to a file to generate an image (I'm developing remotely over SSH, so I can't just see the image on the screen). I did a very small amount of research, found an open standard which seems really easy to write (the PAM format).  

### PAM file format
The pam format is a relatively easy format to write. It has a simple header and then a blob of data to represent the image. More information about the header can be found here: http://manpages.ubuntu.com/manpages/bionic/man5/pam.5.html

The downsides of the PAM format is almost no image tools support this format (not even GIMP!). You'll need to fiddle around with the [netpbm package](http://netpbm.sourceforge.net/) to install the conversion tools.

There's a converter util to convert these files to png files called pamtopng which can be found as part of the netpbm package. See [pamtopng](https://manpages.debian.org/experimental/netpbm/pamtopng.1.en.html).

I didn't go with some of the more standard file formats (bmp, png) as the header is kind of complicated and they're kind of tricky to write.

## Pixel struct

I'm using a simple struct to represent a pixel. Its a more object-oriented approach (which I'm more familiar with) and you can do stuff like pixel.red / pixel->red instead of pixel\[RED\]. 
The downside of doing it this way is that it it makes it harder to do vectorized optimizations to the algorithms. I'm not super worried about this because I'm already doing a ton of unoptimized stuff - e.g. the PAM file format I'm using is pretty inefficient. 

## Image

I've defined an image struct, which has a width, height and then an array of pixels to store the actual image definition.

I've updated the definition of the write_pam_file API to take in a path and an image, as the image has enough information for it to be serialized (and also I've updated some of the naming).

I've also created 3 functions. 2 of them are util functions and 1 is mostly a test function
* make_filled_image - creates an image filled with a single color
* copy_image - creates a copy of an image. This is really useful as a lot of my functions will be destructive (basically any function that doesn't take in a const can and probably will mutate the input paramters)
* fill_section - fills a section of an image. This is for testing that the coordinate system is correct. 

The code in [main.c](./src/main.c) outputs two images:
* The original image

  ![](./docs/hello_world.pam.png).

  You can see that its 3/4 red with the bottom-right corner being blue. This is great, as it means that the coordinate system is working
* The copy of the image before it was modified 
  
  ![](./docs/copy.pam.png). 
  
  Its not modified. This is also great, this means that the copy function is working. Now if images are magically getting changed, its because I didn't make a copy before doing a mutating operation on it. 
