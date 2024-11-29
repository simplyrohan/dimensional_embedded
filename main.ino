#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// ----------------------------------------------------------
// 3D
#include "mesh.h"
#include "transform.h"
#include "renderer.h"

#include "cube.h"

// ----------------------------------------------------------

mesh *meshes[] = {
    &cube,
};

// Buffers
screen g_screen;
screen g_screen2; // for double buffering to prevent flickering
// NOTE: some libraries will allow you to get the screenbuffer directly
uint16_t *screenbuffer; // for faster writes to screen (only write if pixel has changed)

#define WHITE 0xFFFF
#define BLACK 0x0000

#define TFT_CS RX
#define TFT_RST A3
#define TFT_DC A2
Adafruit_ST7789 *lcd;

// Stats
int renderFPS = 0;
int videoFPS = 0;
// ----------------------------------------------------------

void videoTask(void *stuff)
{
    while (true)
    {

        long millisStart = millis();

        lcd->startWrite();
        for (int screenPos = 0; screenPos < 240 * 135; screenPos++)
        {
            if (screenbuffer[screenPos] != g_screen2.buffer[screenPos])
            {
                lcd->writePixel(screenPos % 240, screenPos / 240, g_screen2.buffer[screenPos]);
                screenbuffer[screenPos] = g_screen2.buffer[screenPos];
            }
        }
        lcd->endWrite();

        videoFPS = 1000 / (millis() - millisStart);
        // Log stats
        lcd->setCursor(0, 0);
        lcd->setTextColor(WHITE, BLACK);

        lcd->print(videoFPS);
        lcd->println(" Video FPS");

        lcd->print(renderFPS);
        lcd->println(" Render FPS");
    }
}

void setup()
{
    Serial.begin(115200); // Init Display

    // Init Display
    lcd = new Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
    lcd->setSPISpeed(80000000);
    lcd->init(135, 240);
    lcd->setSPISpeed(80000000);
    lcd->setRotation(1);
    lcd->fillScreen(BLACK);

    screenbuffer = new uint16_t[240 * 135];
    for (int i = 0; i < 240 * 135; i++)
    {
        screenbuffer[i] = 0;
    }

    // 3d
    g_screen.width = 240;
    g_screen.height = 135;
    g_screen.buffer = new uint16_t[240 * 135];

    g_screen2.width = 240;
    g_screen2.height = 135;
    g_screen2.buffer = new uint16_t[240 * 135];

    memset(g_screen.buffer, 0, 240 * 135 * 2);
    memset(g_screen2.buffer, 0, 240 * 135 * 2);

    xTaskCreatePinnedToCore(
        videoTask,
        "videoTask",
        10000,
        NULL,
        0,
        NULL,
        0);
}

void loop()
{
    long millisStart = millis();

    cube.rotation->y += 7;

    render(meshes, 1, &g_screen);

    // Move the rendered screen to the second buffer to prevent flickering
    memcpy(g_screen2.buffer, g_screen.buffer, 240 * 135 * 2);

    // Clear the first buffer
    memset(g_screen.buffer, 0, 240 * 135 * 2);

    // This will be logged in the videoTask
    renderFPS = 1000 / (millis() - millisStart);
}
