#pragma once

#include "utils.h"
#include "mesh.h"
#include <math.h>

void scaleVertex(vertex *p, double scale);

void translateVertex(vertex *p, double x, double y, double z);

void rotateVertex(vertex *p, double angleX, double angleY, double angleZ);