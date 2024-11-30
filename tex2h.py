import sys
import PIL.Image
import PIL.ImageColor

if len(sys.argv) < 2:
    print("Usage: tex2h.py <filename>")
    sys.exit(1)

filename = sys.argv[1]

if len(sys.argv) > 2:
    scale = float(sys.argv[2])

else:
    scale = 1.0

# Get file name
title = filename.split(".")[:-1]

print("[INFO] Reading file:", filename)

img = PIL.Image.open(filename).convert("RGB")

# resize image by scale
# img = img.resize((int(img.width * scale), int(img.height * scale)))
# if sscale is negative then downscale
if scale < 0:
    img = img.resize((int(img.width / abs(scale)), int(img.height / abs(scale))), PIL.Image.BOX)
else:
    img = img.resize((int(img.width * scale), int(img.height * scale)))

img.show()

width, height = img.size

pixels = list(img.getdata())

print("[DATA] Width:", width)
print("[DATA] Height:", height)


def rgb_to_565(r, g, b):
    r = r >> 3
    g = g >> 2
    b = b >> 3

    return (r << 11) | (g << 5) | b


stuff = f"""// This file was generated by tex2h.py
// Texture file: {filename}

#include "renderer/texture.h"

const uint16_t textureData[] = {{
"""

for i, pixel in enumerate(pixels):
    r, g, b = pixel
    fsf = rgb_to_565(r, g, b)
    
    # convert to 4 hex digits
    fsf = hex(fsf)[2:]
    while len(fsf) < 4:
        fsf = "0" + fsf
    stuff += "0x" + fsf + ", "

stuff += "};\n"

stuff += f"""
texture texture_{title[0]} = {{
    .width = {width},
    .height = {height},
    .data = textureData,
}};
"""

print("[INFO] Writing to file:", title[0] + ".h")

with open(title[0] + ".h", "w") as f:
    f.write(stuff)
