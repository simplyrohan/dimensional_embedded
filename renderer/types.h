/**
 * @struct vector3
 * @brief A vector in 3D space. Can be used to represent any data with three components (rotation, translation, scale, etc.).
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param z The z coordinate.
 */
typedef struct vector3
{
    double x;
    double y;
    double z;
};

/**
 * @struct vector2
 * @brief A vector/position in 2D space. Can be used to represent any data with two components (points, texture coordinates, etc.).s
 * @param x The x coordinate.
 * @param y The y coordinate.
 */
typedef struct vector2
{
    double x;
    double y;
};
