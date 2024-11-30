// This file was generated by obj2h.py
// OBJ file: minecraft.obj
#include "renderer/mesh.h"
vertex vertices[] = {
    {1.0, 3e-06, -1.0},
    {1.0, 3e-06, 1.0},
    {-1.0, 3e-06, 1.0},
    {-1.0, 3e-06, -1.0},
    {1.0, 2.000003, -0.999998},
    {-1.0, 2.000003, -0.999999},
    {-1.0, 2.000003, 1.000001},
    {0.999999, 2.000003, 1.000002},
};

// Texture coordinates
point textureCoords[] = {
    {0.333343, 0.250023},
    {0.666657, 3.8e-05},
    {0.666657, 0.250023},
    {0.666657, 0.500009},
    {0.333343, 0.749994},
    {0.333343, 0.500009},
    {2.9e-05, 0.749994},
    {2.9e-05, 0.500009},
    {0.666657, 0.99998},
    {0.333343, 0.99998},
    {0.999971, 0.500009},
    {0.666657, 0.749994},
    {0.333343, 3.8e-05},
    {0.999971, 0.749994},
};
triangle faces[] = {
    {vertices[1], vertices[3], vertices[0], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[4], vertices[6], vertices[7], textureCoords[3], textureCoords[4], textureCoords[5]},
    {vertices[4], vertices[1], vertices[0], textureCoords[3], textureCoords[0], textureCoords[2]},
    {vertices[7], vertices[2], vertices[1], textureCoords[5], textureCoords[6], textureCoords[7]},
    {vertices[6], vertices[3], vertices[2], textureCoords[4], textureCoords[8], textureCoords[9]},
    {vertices[0], vertices[5], vertices[4], textureCoords[10], textureCoords[11], textureCoords[3]},
    {vertices[1], vertices[2], vertices[3], textureCoords[0], textureCoords[12], textureCoords[1]},
    {vertices[4], vertices[5], vertices[6], textureCoords[3], textureCoords[11], textureCoords[4]},
    {vertices[4], vertices[7], vertices[1], textureCoords[3], textureCoords[5], textureCoords[0]},
    {vertices[7], vertices[6], vertices[2], textureCoords[5], textureCoords[4], textureCoords[6]},
    {vertices[6], vertices[5], vertices[3], textureCoords[4], textureCoords[11], textureCoords[8]},
    {vertices[0], vertices[3], vertices[5], textureCoords[10], textureCoords[13], textureCoords[11]},
};

mesh minecraft = {
    faces,
    12,
    new vertex({0, 0, 0}),   // Rotation
    new vertex({0, 0, 200}), // Translation
    100,                     // Scalex
};
