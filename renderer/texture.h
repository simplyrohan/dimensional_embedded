#pragma once
#include <cstdint>

struct texture {
    int width;
    int height;
    const uint16_t *data;
};
typedef struct texture texture;