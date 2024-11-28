#pragma once

#include "utils.h"
#include "mesh.h"
#include <math.h>

vertex *scaleVertex(vertex *p, double scale);

vertex *translateVertex(vertex *p, double x, double y, double z);

vertex *rotateVertex(vertex *p, double angleX, double angleY, double angleZ);