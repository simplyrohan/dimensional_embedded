#pragma once

#include "utils.h"
#include "mesh.h"
#include "transform.h"
#include "screen.h"

#define FOCAL_LENGTH 111

uint32_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b);

void rasterizeTriangle(int x1, int y1,
                       int x2, int y2,
                       int x3, int y3,
                       int u1, int v1,
                       int u2, int v2,
                       int u3, int v3,
                       int z1, int z2, int z3,
                       screen buffer, int color, double *zBuffer);

void render(mesh **meshes, int numMeshes, screen *buffer, int color);
