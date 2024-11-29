#include <cstdio>
#include "renderer.h"

#define FOCAL_LENGTH 111

uint32_t rgb_to_565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

void rasterizeTriangle(int x1, int y1,
                       int x2, int y2,
                       int x3, int y3,
                       int u1, int v1,
                       int u2, int v2,
                       int u3, int v3,
                       int z1, int z2, int z3,
                       screen *buffer, double *zBuffer)
{
    // lcd->drawLine(x1, y1, x2, y2, color);
    // lcd->drawLine(x2, y2, x3, y3, color);
    // lcd->drawLine(x3, y3, x1, y1, color);
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
                // lcd->writePixel(px, py, color);
                // buffer->buffer[px + py * buffer->width] = rgb_to_565(255, 255, 255);
                double z = w0 * z1 + w1 * z2 + w2 * z3;
                // printf("z: %f\n", z);
                if (zBuffer[px + py * buffer->width] < z && zBuffer[px + py * buffer->width] != -1)
                {
                    continue;
                }
                zBuffer[px + py * buffer->width] = z;
                buffer->buffer[px + py * buffer->width] = rgb_to_565(w0 * 255, w1 * 255, w2 * 255);
                // buffer->buffer[px + py * buffer->width] = rgb_to_565(z / 400 * 255, 0, 0);
            }
        }
    }
}

void render(mesh **meshes, int numMeshes, screen *buffer)
{
    // double *zBuffer = new double[buffer->width * buffer->height];
    // make z buffer full of -1s
    double *zBuffer = new double[buffer->width * buffer->height];
    for (int i = 0; i < buffer->width * buffer->height; i++)
    {
        zBuffer[i] = -1;
    }


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
            // vertex *transformed1 = scaleVertex(&v1, m->scale);
            // vertex *transformed2 = scaleVertex(&v2, m->scale);
            // vertex *transformed3 = scaleVertex(&v3, m->scale);
            // copy vertex
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
            point p1 = {(transformed1->x * FOCAL_LENGTH) / (transformed1->z + FOCAL_LENGTH), (transformed1->y * FOCAL_LENGTH) / (transformed1->z + FOCAL_LENGTH)};
            point p2 = {(transformed2->x * FOCAL_LENGTH) / (transformed2->z + FOCAL_LENGTH), (transformed2->y * FOCAL_LENGTH) / (transformed2->z + FOCAL_LENGTH)};
            point p3 = {(transformed3->x * FOCAL_LENGTH) / (transformed3->z + FOCAL_LENGTH), (transformed3->y * FOCAL_LENGTH) / (transformed3->z + FOCAL_LENGTH)};

            p1.x = (p1.x) + (buffer->width / 2);
            p1.y = (p1.y) + (buffer->height / 2);
            p2.x = (p2.x) + (buffer->width / 2);
            p2.y = (p2.y) + (buffer->height / 2);
            p3.x = (p3.x) + (buffer->width / 2);
            p3.y = (p3.y) + (buffer->height / 2);

            // lcd->drawLine(p1.x, p1.y, p2.x, p2.y, color);
            // lcd->drawLine(p2.x, p2.y, p3.x, p3.y, color);
            // lcd->drawLine(p3.x, p3.y, p1.x, p1.y, color);
            rasterizeTriangle(p1.x, p1.y,
                              p2.x, p2.y,
                              p3.x, p3.y,
                              t.t1.x, t.t1.y,
                              t.t2.x, t.t2.y,
                              t.t3.x, t.t3.y,
                              transformed1->z, transformed2->z, transformed3->z,
                              buffer, zBuffer);

            delete transformed1;
            delete transformed2;
            delete transformed3;
        }
    }

    delete[] zBuffer;
}
