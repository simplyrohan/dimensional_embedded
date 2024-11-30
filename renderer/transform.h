#pragma once

#include "utils.h"
#include "mesh.h"
#include <math.h>
#include "transform.h"

void scaleVertex(vertex *p, double scale)
{
    p->x = p->x * scale;
    p->y = p->y * scale;
    p->z = p->z * scale;
}

void translateVertex(vertex *p, double x, double y, double z)
{
    p->x = p->x + x;
    p->y = p->y + y;
    p->z = p->z + z;
}

void rotateVertex(vertex *p, double angleX, double angleY, double angleZ)
{
    double y = p->y;
    double z = p->z;
    double x = p->x;

    double sX = sin(radians(angleX));
    double cX = cos(radians(angleX));
    double sY = sin(radians(angleY));
    double cY = cos(radians(angleY));
    double sZ = sin(radians(angleZ));
    double cZ = cos(radians(angleZ));

    p->x = x * cY * cZ + y * (sX * sY * cZ - cX * sZ) + z * (cX * sY * cZ + sX * sZ);
    p->y = x * cY * sZ + y * (sX * sY * sZ + cX * cZ) + z * (cX * sY * sZ - sX * cZ);
    p->z = -x * sY + y * sX * cY + z * cX * cY;
}
