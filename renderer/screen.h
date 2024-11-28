#pragma once

#include <stdint.h>

struct screen {
    int width;
    int height;
    
    uint16_t *buffer;
};
typedef struct screen screen;