Last updated: 14/Mar/2015 by Paul Cernek


=====
TL;DR
=====

Usage:
./thermoscale <image path>

Functionality:
-When you click on a pixel, its 16-bit value is printed to console
-When you move either of the two sliders, the updated min, max, and range are printed to console


==========
BACKGROUND
==========

This is a program that loads a 16-bit image and renders it as an 8-bit image, allowing the user to dynamically control the scaling of pixel values by manually adjusting the minimum and maximum pixel value thresholds.

To understand how this works, one needs to consider the following simple formula for converting pixel values in a 16-bit grayscale image into 8-bit values:

        val' = [(val - min) / (max - min)] * 255

    ...where:
        val = the current pixel value
        min = the lowest pixel value in the entire image
        max = the highest pixel value in the entire image
        255 is the highest possible pixel value in an 8-bit image
        
Intuitively, this formula sets the lowest pixel value in the image to 0 and the highest pixel value to 255. Everything in between gets scaled proportionately to fit within the range [0, 255]. This is generally what we mean by the term `autoscaling'. It takes only a moment's consideration to realize that applying this formula results in a loss of information when the range of pixel values in the 16-bit image (max - min) exceeds 255. This can result in the undesirable outcome in which an object of interest that is detectable in the 16-bit image becomes indistinguishable from its background in the 8-bit conversion.

For example, thermal images that include the sun are often rendered as all black, except for the sun, which is white. This is because the sun's intensity is generally an order of magnitude greater than that of any other object in the frame. Thus, for any non-sun object in the frame, the value of the denominator in the formula above (max - min) is much greater than the value of the numerator (val - min), resulting in 8-bit values that are close to 0. This is one of the clearest examples of how `autoscaling' can be a lossy form of compression, hindering the visualization of 16-bit images. (See footnote [1].)

In autoscaling, the values of min and max are automatically set to the minimum and maximum pixel values in the 16-bit image. This program allows the user to manually control these values via two sliders.

Read TL;DR above for 

Footnotes:
[1] NOTE: It should be emphasized that this is primarily a problem of data visualization. If a program is capable of handling 16-bit images, then it doesn't need to perform any kind of scaling at all. However, some OpenCV functions do operate only on 8-bit images, making this problem relevant at a programmatic level after all.
