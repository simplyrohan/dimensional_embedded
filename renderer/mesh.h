#pragma once
#include "types.h"
#include "transform.h"

/**
 * @struct triangle
 * @brief A triangle in 3D space.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @param v3 The third vertex.
 * @param t1 The first texture coordinate.
 * @param t2 The second texture coordinate.
 * @param t3 The third texture coordinate.
 */
struct triangle
{
    vector3 v1;
    vector3 v2;
    vector3 v3;

    vector2 t1;
    vector2 t2;
    vector2 t3;

    // vertex norm1;
    // vertex norm2;
    // vertex norm3;
};
typedef struct triangle triangle;

/**
 * @struct mesh
 * @brief A mesh of triangles.
 * @param triangles The triangles of the mesh.
 * @param numTriangles The number of triangles in `triangles`.
 * @param rotation The rotation of the mesh.
 * @param translation The translation of the mesh.
 * @param scale The scale of the mesh.
 */
struct mesh
{
    triangle *triangles;
    int numTriangles;

    // vector3 *rotation;
    // vector3 *translation;
    // double scale;
    transformation *transformation;
};
typedef struct mesh mesh;
