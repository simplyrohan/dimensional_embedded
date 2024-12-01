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

    for (int x = 0; x < triW; x++)
    {
        for (int y = 0; y < triH; y++)
        {
            int px = triX + x;
            int py = triY + y;

            if (px < 0 || px >= buffer->width || py < 0 || py >= buffer->height)
            {
                continue;
            }

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
                double z = w0 * z1 + w1 * z2 + w2 * z3;
                // if (z < 0)
                // {
                //     continue;
                // }
                if (zBuffer[px + py * buffer->width] < z && zBuffer[px + py * buffer->width] != -1)
                {
                    continue;
                }
                zBuffer[px + py * buffer->width] = z;

                double u = w0 * u1 + w1 * u2 + w2 * u3;
                double v = w0 * v1 + w1 * v2 + w2 * v3;

                uint16_t color = tex->data[(int)(u * tex->width) + (int)(v * tex->height) * tex->width];

                buffer->buffer[px + py * buffer->width] = color;
                if (w1 < 0.01 || w2 < 0.01 || w0 < 0.01)
                {
                    buffer->buffer[px + py * buffer->width] = rgb_to_565(255, 0, 0);
                }
            }
        }
    }
}

void render(mesh **meshes, int numMeshes, screen *buffer, transformation *camera)
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
        texture *tex = m->texture;
        for (int j = 0; j < m->numTriangles; j++)
        {
            triangle t = m->triangles[j];
            vector3 v1 = t.v1;
            vector3 v2 = t.v2;
            vector3 v3 = t.v3;

            // Transform
            vector3 *transformed1 = new vector3(v1);
            vector3 *transformed2 = new vector3(v2);
            vector3 *transformed3 = new vector3(v3);

            applyTransformation(transformed1, m->transformation);
            applyTransformation(transformed2, m->transformation);
            applyTransformation(transformed3, m->transformation);

            translateVertex(transformed1, camera->translation);
            translateVertex(transformed2, camera->translation);
            translateVertex(transformed3, camera->translation);

            rotateVertex(transformed1, camera->rotation);
            rotateVertex(transformed2, camera->rotation);
            rotateVertex(transformed3, camera->rotation);

            // applyTransformation(transformed1, camera);
            // applyTransformation(transformed2, camera);
            // applyTransformation(transformed3, camera);

            // Projection
            if (transformed1->z <= -FOCAL_LENGTH && transformed2->z <= -FOCAL_LENGTH && transformed3->z <= -FOCAL_LENGTH)
            {
                continue;
            }

            // Projection
            vector2 p1;
            vector2 p2;
            vector2 p3;

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
