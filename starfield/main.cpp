#include <stdio.h>
#include <cstdlib>
#include "pico/stdlib.h"
#include "displaylib_16/ili9341.hpp"

ILI9341_TFT display;

const int NUM_STARS = 150;
const float SPEED = 4.5f;
const float MAX_DEPTH = 300.0f;
const float MIN_DEPTH = 1.0f;

struct Star {
    float x;
    float y;
    float z;
};

Star stars[NUM_STARS];

int screen_width = 240;
int screen_height = 320;

void init_stars() {
    for (int i = 0; i < NUM_STARS; i++) {
        stars[i].x = (rand() % 400) - 200;
        stars[i].y = (rand() % 400) - 200;
        stars[i].z = (rand() % (int)MAX_DEPTH) + MIN_DEPTH;
    }
}

void update_stars() {
    for (int i = 0; i < NUM_STARS; i++) {
        stars[i].z -= SPEED;
        
        if (stars[i].z < MIN_DEPTH) {
            stars[i].x = (rand() % 400) - 200;
            stars[i].y = (rand() % 400) - 200;
            stars[i].z = MAX_DEPTH;
        }
    }
}

void project_stars(int& screen_x, int& screen_y, float star_x, float star_y, float star_z) {
    float scale = 150.0f / star_z;
    
    screen_x = (int)(screen_width / 2.0f + star_x * scale);
    screen_y = (int)(screen_height / 2.0f + star_y * scale);
}

void draw_starfield() {
    for (int i = 0; i < NUM_STARS; i++) {
        int screen_x, screen_y;
        project_stars(screen_x, screen_y, stars[i].x, stars[i].y, stars[i].z);
        
        if (screen_x >= 0 && screen_x < screen_width && 
            screen_y >= 0 && screen_y < screen_height) {
            
            uint16_t brightness = (uint16_t)((1.0f - (stars[i].z / MAX_DEPTH)) * 31);
            uint16_t color = (brightness << 11) | (brightness << 6) | brightness;
            
            display.drawPixel(screen_x, screen_y, color);
            if (screen_x + 1 < screen_width)
                display.drawPixel(screen_x + 1, screen_y, color);
            if (screen_y + 1 < screen_height)
                display.drawPixel(screen_x, screen_y + 1, color);
            if (screen_x + 1 < screen_width && screen_y + 1 < screen_height)
                display.drawPixel(screen_x + 1, screen_y + 1, color);
        }
    }
}

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("Starting Starfield Animation\n");

    display.SetupGPIO(20, 21, 17, 18, 19, 16);

    display.SetupScreenSize(240, 320);

    display.SetupSPI(25000000, spi0);

    display.ILI9341Initialize();
    printf("Display initialized\n");

    init_stars();
    
    display.fillScreen(display.C_BLACK);

    printf("Starfield animation running...\n");

    while(1) {
        display.fillScreen(display.C_BLACK);
        
        update_stars();
        
        draw_starfield();
        
        sleep_ms(5);
    }

    return 0;
}
