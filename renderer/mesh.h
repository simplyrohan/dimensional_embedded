#pragma once

/**
 * @struct point
 * @brief A point in 2D space.
 * @param x The x coordinate.
 * @param y The y coordinate.
 */
struct point
{
    double x;
    double y;
};
typedef struct point point;

/**
 * @struct vertex
 * @brief A point in 3D space.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param z The z coordinate.
 */
struct vertex
{
    double x;
    double y;
    double z;
};
typedef struct vertex vertex;

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
    vertex v1;
    vertex v2;
    vertex v3;

    point t1;
    point t2;
    point t3;

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

    vertex *rotation;
    vertex *translation;
    double scale;
};
typedef struct mesh mesh;
