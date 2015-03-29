# histogram equalization

import sys
import operator

def equalize(h):

    lut = []

    for b in range(0, len(h), 256):

        # step size
        step = reduce(operator.add, h[b:b+256]) / 255

        # create equalization lookup table
        n = 0
        for i in range(256):
            lut.append(n / step)
            n = n + h[i+b]

    return lut

#
# test stuff

if __name__ == "__main__":

    import Image

    im = Image.open(sys.argv[1])

    # calculate lookup table
    lut = equalize(im.histogram())

    # map image through lookup table
    im = im.point(lut)

    im.save("out.png")
