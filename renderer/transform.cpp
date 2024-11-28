#include "transform.h"

vertex *scaleVertex(vertex *p, double scale)
{
    vertex *copy = new vertex();
    copy->x = p->x * scale;
    copy->y = p->y * scale;
    copy->z = p->z * scale;
    return copy;
}

vertex *translateVertex(vertex *p, double x, double y, double z)
{
    vertex *copy = new vertex();
    copy->x = p->x + x;
    copy->y = p->y + y;
    copy->z = p->z + z;
    return copy;
}

vertex *rotateVertex(vertex *p, double angleX, double angleY, double angleZ)
{
    vertex *copy = new vertex();

    double y = p->y;
    double z = p->z;
    double x = p->x;

    double sX = sin(radians(angleX));
    double cX = cos(radians(angleX));
    double sY = sin(radians(angleY));
    double cY = cos(radians(angleY));
    double sZ = sin(radians(angleZ));
    double cZ = cos(radians(angleZ));

    copy->x = x * cY * cZ + y * (sX * sY * cZ - cX * sZ) + z * (cX * sY * cZ + sX * sZ);
    copy->y = x * cY * sZ + y * (sX * sY * sZ + cX * cZ) + z * (cX * sY * sZ - sX * cZ);
    copy->z = -x * sY + y * sX * cY + z * cX * cY;

    return copy;
}
