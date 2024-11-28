#include "renderer/mesh.h"

vertex vertices[8] = {
    {-1, -1, -1},
    {1, -1, -1},
    {1, 1, -1},
    {-1, 1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, 1},
    {-1, 1, 1}};

point textureCoords[4] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1}};

triangle triangles[12] = {
    {vertices[0], vertices[1], vertices[2], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[0], vertices[2], vertices[3], textureCoords[0], textureCoords[2], textureCoords[3]},
    {vertices[1], vertices[5], vertices[6], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[1], vertices[6], vertices[2], textureCoords[0], textureCoords[2], textureCoords[3]},
    {vertices[5], vertices[4], vertices[7], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[5], vertices[7], vertices[6], textureCoords[0], textureCoords[2], textureCoords[3]},
    {vertices[4], vertices[0], vertices[3], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[4], vertices[3], vertices[7], textureCoords[0], textureCoords[2], textureCoords[3]},
    {vertices[3], vertices[2], vertices[6], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[3], vertices[6], vertices[7], textureCoords[0], textureCoords[2], textureCoords[3]},
    {vertices[4], vertices[5], vertices[1], textureCoords[0], textureCoords[1], textureCoords[2]},
    {vertices[4], vertices[1], vertices[0], textureCoords[0], textureCoords[2], textureCoords[3]}};

mesh cube = {triangles, 12, new vertex({0, 0, 0}), new vertex({0, 0, 200}), 100};

mesh *meshes[] = {&cube};