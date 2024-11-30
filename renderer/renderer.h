#pragma once

#include "utils.h"
#include "mesh.h"
#include "transform.h"
#include "screen.h"
#include "texture.h"

#define FOCAL_LENGTH 246

uint32_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

void rasterizeTriangle(int x1, int y1,
                       int x2, int y2,
                       int x3, int y3,
                       double u1, double v1,
                       double u2, double v2,
                       double u3, double v3,
                       int z1, int z2, int z3,
                       texture *tex,
                       screen *buffer, double *zBuffer)
{
    int triX = min(min(x1, x2), x3);
    int triY = min(min(y1, y2), y3);
    int triW = max(max(x1, x2), x3) - triX;
    int triH = max(max(y1, y2), y3) - triY;

    // double u1i = u1 / (z1);
    // double v1i = v1 / (z1);
    // double u2i = u2 / (z2);
    // double v2i = v2 / (z2);
    // double u3i = u3 / (z3);
    // double v3i = v3 / (z3);

    // double z1i = 1.0f / z1;
    // double z2i = 1.0f / z2;
    // double z3i = 1.0f / z3;

    for (int x = 0; x < triW; x++)
    {
        for (int y = 0; y < triH; y++)
        {
            int px = triX + x;
            int py = triY + y;

            // Barycentric coordinates
            float denominator = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
            if (denominator == 0)
            {
                continue;
            }
            double w0 = ((y2 - y3) * (px - x3) + (x3 - x2) * (py - y3)) /
                      denominator;
            double w1 = ((y3 - y1) * (px - x3) + (x1 - x3) * (py - y3)) /
                      denominator;
            double w2 = 1 - w0 - w1;

            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
            {
                // double zi = w0 * z1i + w1 * z2i + w2 * z3i;
                // double z = 1 / zi;
                double z = w0 * z1 + w1 * z2 + w2 * z3;

                if (zBuffer[px + py * buffer->width] < z && zBuffer[px + py * buffer->width] != -1)
                {
                    continue;
                }
                zBuffer[px + py * buffer->width] = z;

                // double ui = w0 * u1i + w1 * u2i + w2 * u3i;
                // double vi = w0 * v1i + w1 * v2i + w2 * v3i;
                // double u = ui * z;
                // double v = vi * z;
                double u = w0 * u1 + w1 * u2 + w2 * u3;
                double v = w0 * v1 + w1 * v2 + w2 * v3;
                // //print z1, z2, z3, z1i, z2i, z3i, zi, z

                uint16_t color = tex->data[(int)(u * tex->width) + (int)(v * tex->height) * tex->width];

                buffer->buffer[px + py * buffer->width] = color;
            }
        }
    }
}

void render(mesh **meshes, int numMeshes, texture *tex, screen *buffer)
{
    double *zBuffer = new double[buffer->width * buffer->height];
    for (int i = 0; i < buffer->width * buffer->height; i++)
    {
        zBuffer[i] = -1;
    }
    // memset(zBuffer, -1, buffer->width * buffer->height * sizeof(double));

    for (int i = 0; i < numMeshes; i++)
    {
        mesh *m = meshes[i];
        for (int j = 0; j < m->numTriangles; j++)
        {
            triangle t = m->triangles[j];
            vertex v1 = t.v1;
            vertex v2 = t.v2;
            vertex v3 = t.v3;

            // Transform
            vertex *transformed1 = new vertex(v1);
            vertex *transformed2 = new vertex(v2);
            vertex *transformed3 = new vertex(v3);

            scaleVertex(transformed1, m->scale);
            scaleVertex(transformed2, m->scale);
            scaleVertex(transformed3, m->scale);

            // Rotate
            rotateVertex(transformed1, m->rotation->x, m->rotation->y, m->rotation->z);
            rotateVertex(transformed2, m->rotation->x, m->rotation->y, m->rotation->z);
            rotateVertex(transformed3, m->rotation->x, m->rotation->y, m->rotation->z);

            // Translate
            translateVertex(transformed1, m->translation->x, m->translation->y, m->translation->z);
            translateVertex(transformed2, m->translation->x, m->translation->y, m->translation->z);
            translateVertex(transformed3, m->translation->x, m->translation->y, m->translation->z);

            // Projection
            if (transformed1->z <= 0 && transformed2->z <= 0 && transformed3->z <= 0)
            {
                continue;
            }

            // Projection
            point p1;
            point p2;
            point p3;

            if (transformed1->z == 0)
            {
                p1 = {transformed1->x, transformed1->y};
            }
            else
            {
                p1 = {(transformed1->x * FOCAL_LENGTH) / (transformed1->z + FOCAL_LENGTH), (transformed1->y * FOCAL_LENGTH) / (transformed1->z + FOCAL_LENGTH)};
            }

            if (transformed2->z == 0)
            {
                p2 = {transformed2->x, transformed2->y};
            }
            else
            {
                p2 = {(transformed2->x * FOCAL_LENGTH) / (transformed2->z + FOCAL_LENGTH), (transformed2->y * FOCAL_LENGTH) / (transformed2->z + FOCAL_LENGTH)};
            }

            if (transformed3->z == 0)
            {
                p3 = {transformed3->x, transformed3->y};
            }
            else
            {
                p3 = {(transformed3->x * FOCAL_LENGTH) / (transformed3->z + FOCAL_LENGTH), (transformed3->y * FOCAL_LENGTH) / (transformed3->z + FOCAL_LENGTH)};
            }

            p1.x = (p1.x) + (buffer->width / 2);
            p1.y = (p1.y) + (buffer->height / 2);
            p2.x = (p2.x) + (buffer->width / 2);
            p2.y = (p2.y) + (buffer->height / 2);
            p3.x = (p3.x) + (buffer->width / 2);
            p3.y = (p3.y) + (buffer->height / 2);

            rasterizeTriangle(p1.x, p1.y,
                              p2.x, p2.y,
                              p3.x, p3.y,
                              t.t1.x, t.t1.y,
                              t.t2.x, t.t2.y,
                              t.t3.x, t.t3.y,
                              transformed1->z, transformed2->z, transformed3->z,
                              tex, buffer, zBuffer);

            delete transformed1;
            delete transformed2;
            delete transformed3;
        }
    }

    delete[] zBuffer;
}
