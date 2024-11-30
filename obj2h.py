import sys

if len(sys.argv) != 2:
    print("Usage: obj2h.py <filename>")
    sys.exit(1)

filename = sys.argv[1]

# Get file name
title = filename.split(".")[:-1]

print("[INFO] Reading file:", filename)
with open(filename, "r") as f:
    data = f.read()

vs = [line for line in data.split("\n") if line.startswith("v ")]
vts = [line for line in data.split("\n") if line.startswith("vt ")]
fs = [line for line in data.split("\n") if line.startswith("f ")]

vertices = [
    [float(component.strip()) for component in components.split(" ")[1:4]]
    for components in vs
]
textures = [
    [float(component.strip()) for component in components.split(" ")[1:3]]
    for components in vts
]
faces = [
    [
        [int(component.split("/")[0]), int(component.split("/")[1])]
        for component in components.split(" ")[1:4]
    ]
    for components in fs
]

print("[DATA] Vertices:", len(vertices))
print("[DATA] Texture Coordinates:", len(textures))
print("[DATA] Faces:", len(faces))

stuff = f"""// This file was generated by obj2h.py
// OBJ file: {filename}
#include "renderer/mesh.h"
"""


# vertices
stuff += "vertex vertices[] = {\n"

for vertex in vertices:
    stuff += (
        "    { "
        + str(vertex[0])
        + ", "
        + str(vertex[1])
        + ", "
        + str(vertex[2])
        + "},\n"
    )

stuff += "};\n"


# Texure coordinates
stuff += """
// Texture coordinates
point textureCoords[] = {
"""

for texture in textures:
    stuff += "    { " + str(texture[0]) + ", " + str(texture[1]) + "},\n"

stuff += "};\n"

# triangles
stuff += "triangle faces[] = {\n"

for face in faces:
    stuff += (
        "    { vertices["
        + str(face[0][0] - 1)
        + "] , vertices["
        + str(face[1][0] - 1)
        + "] , vertices["
        + str(face[2][0] - 1)
        + "], textureCoords["
        + str(face[0][1] - 1)
        + "], textureCoords["
        + str(face[1][1] - 1)
        + "], textureCoords["
        + str(face[2][1] - 1)
        + "]},\n"
    )

stuff += "};\n"

stuff += f"""
mesh {title[0]} = {{
    faces,
    {len(faces)},
    new vertex({{0, 0, 0}}), // Rotation
    new vertex({{0, 0, 200}}), // Translation
    10, // Scale
}};
"""

print("[INFO] Writing to file:", title[0] + ".h")
with open(title[0] + ".h", "w") as f:
    f.write(stuff)