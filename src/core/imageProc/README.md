# imageProc

Here we find miscellaneous low-level code for manipulating individual pixels in images.

As of 2016 January 25, most of this code is in support of rescaling, which is described in great length 
[here](https://drive.google.com/drive/folders/0B6vdQw-a6njpQ3dUWnNMSV9MZWc).

-   **histogram**/ 
    -   Rescaling makes heavy use of histograms to determine the distribution
    of pixel intensity values in an image before choosing which ones to preserve and which to 
    compress. Part of the reason there are so many files here is that we made use of the Decorator
    pattern to allow for modularity between different components. HorizonImageHistogram, for example,
    takes into account the position of the horizon in an image in making a tally of pixel values.
    Combine it with MedianGetter, for example, to find the median pixel value below the horizon in
    a particular image.
-   **liveFeed**/
    -   Serialization and deserialization of images to send them over network sockets.
-   **rescale**/
    -   The actual classes that perform rescaling. In a sense they provide the "plumbing" to
    assemble together the pieces found in **histogram/**.
-   **smoothing**/
    -   Here "smoothing" refers to smoothing over time. In rescaling, sometimes there will be sharp
    transitions in the central tendency of the pixel values of successive images in a video stream;
    when this happens, it is sometimes desirable to dampen such jumps in pixel values by keeping a
    moving average of pixel values over the previous X frames. The classes in this folder provide
    that functionality, making use of the decorator pattern.
    