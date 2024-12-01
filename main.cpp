#include <MiniFB.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "renderer/types.h"

#include "renderer/renderer.h"
// #include "cube.h"
#include "cobble.h"
#include "image.h"

static uint32_t g_width = 800;
static uint32_t g_height = 600;
static uint32_t *g_buffer = 0x0;

screen g_screen;

transformation camera = {
    new vector3({0, 0, 0}), // Rotation
    new vector3({0, 0, 0}), // Translation
    new vector3({1, 1, 1}), // Scale
};

mesh *meshes[256];

mfb_timer *timer = mfb_timer_create();

uint32_t fsf_to_color(uint16_t fsf)
{
    // convert a 565 color to a 888 color
    uint32_t r = (fsf >> 11) & 0x1F;
    uint32_t g = (fsf >> 5) & 0x3F;
    uint32_t b = fsf & 0x1F;

    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    return (r << 16) | (g << 8) | b;
}

int main()
{
    int screenPos;
    struct mfb_window *window = mfb_open_ex("Noise Test", g_width, g_height, WF_RESIZABLE);
    if (!window)
        return 0;

    g_buffer = (uint32_t *)malloc(g_width * g_height * 4);

    // g_screen
    g_screen.width = g_width;
    g_screen.height = g_height;
    g_screen.buffer = new uint16_t[g_width * g_height];

    // Populate mesh array
    for (int x = 0; x < 16; x++)
    {
        for (int z = 0; z < 16; z++)
        {
            mesh *m = genCobble(x - 7.5, 5, z -5, 50);
            meshes[x * 16 + z] = m;
        }
    }

    mfb_update_state state;
    do
    {
        for (screenPos = 0; screenPos < g_width * g_height; screenPos++)
        {
            g_buffer[screenPos] = fsf_to_color(g_screen.buffer[screenPos]);
            g_screen.buffer[screenPos] = 0;
        }

        // cobble.transformation->rotation->y += 1;
        render(meshes, 256, &g_screen, &camera);
        printf("fps: %f\n", 1.0 / mfb_timer_delta(timer));

        state = mfb_update_ex(window, g_buffer, g_width, g_height);
        if (state != STATE_OK)
        {
            window = 0x0;
            break;
        }
    } while (mfb_wait_sync(window));

    return 0;
}