#pragma once

#include "utils.h"
#include "mesh.h"
#include <math.h>
#include "transform.h"

typedef struct
{
    vector3 *rotation;
    vector3 *translation;
    vector3 *scale;
} transformation;

void scaleVertex(vector3 *p, vector3 *scale)
{
    p->x = p->x * scale->x;
    p->y = p->y * scale->y;
    p->z = p->z * scale->z;

}

void translateVertex(vector3 *p, vector3 *translation)
{
    p->x = p->x + translation->x;
    p->y = p->y + translation->y;
    p->z = p->z + translation->z;
}

void rotateVertex(vector3 *p, vector3 *rotation)
{
    double y = p->y;
    double z = p->z;
    double x = p->x;

    double sX = sin(radians(rotation->x));
    double cX = cos(radians(rotation->x));
    double sY = sin(radians(rotation->y));
    double cY = cos(radians(rotation->y));
    double sZ = sin(radians(rotation->z));
    double cZ = cos(radians(rotation->z));

    p->x = x * cY * cZ + y * (sX * sY * cZ - cX * sZ) + z * (cX * sY * cZ + sX * sZ);
    p->y = x * cY * sZ + y * (sX * sY * sZ + cX * cZ) + z * (cX * sY * sZ - sX * cZ);
    p->z = -x * sY + y * sX * cY + z * cX * cY;
}


void applyTransformation(vector3 *p, transformation *t)
{
    scaleVertex(p, t->scale);
    rotateVertex(p, t->rotation);
    translateVertex(p, t->translation);
}