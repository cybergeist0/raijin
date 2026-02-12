#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include "pico/stdlib.h"
#include "displaylib_16/ili9341.hpp"

ILI9341_TFT display;

const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 320;
const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;

const float MATH_MIN = -5.0f;
const float MATH_MAX = 5.0f;
const float SCALE = (SCREEN_WIDTH / 2) / (MATH_MAX - MATH_MIN);

const uint16_t GRID_COLOR = 0x2104;
const uint16_t TICK_COLOR = 0x4208;

int mathToScreenX(float x) {
    return (int)((x - MATH_MIN) / (MATH_MAX - MATH_MIN) * SCREEN_WIDTH);
}

int mathToScreenY(float y) {
    return (int)(SCREEN_HEIGHT - (y - MATH_MIN) / (MATH_MAX - MATH_MIN) * SCREEN_HEIGHT);
}

void drawGrid() {
    int tick_interval = 1;
    
    for (float x = MATH_MIN; x <= MATH_MAX; x += tick_interval) {
        int screen_x = mathToScreenX(x);
        display.drawLine(screen_x, 0, screen_x, SCREEN_HEIGHT, GRID_COLOR);
    }
    
    for (float y = MATH_MIN; y <= MATH_MAX; y += tick_interval) {
        int screen_y = mathToScreenY(y);
        display.drawLine(0, screen_y, SCREEN_WIDTH, screen_y, GRID_COLOR);
    }
}

void drawAxes() {
    int x0 = mathToScreenX(0);
    int y0 = mathToScreenY(0);
    
    if (x0 >= 0 && x0 < SCREEN_WIDTH)
        display.drawLine(x0, 0, x0, SCREEN_HEIGHT, display.C_WHITE);
    if (y0 >= 0 && y0 < SCREEN_HEIGHT)
        display.drawLine(0, y0, SCREEN_WIDTH, y0, display.C_WHITE);
    
    int tick_length = 4;
    int tick_interval = 1;
    
    for (float x = MATH_MIN; x <= MATH_MAX; x += tick_interval) {
        int screen_x = mathToScreenX(x);
        if (y0 >= 0 && y0 < SCREEN_HEIGHT)
            display.drawLine(screen_x, y0 - tick_length/2, screen_x, y0 + tick_length/2, TICK_COLOR);
    }
    
    for (float y = MATH_MIN; y <= MATH_MAX; y += tick_interval) {
        int screen_y = mathToScreenY(y);
        if (x0 >= 0 && x0 < SCREEN_WIDTH)
            display.drawLine(x0 - tick_length/2, screen_y, x0 + tick_length/2, screen_y, TICK_COLOR);
    }
}

void drawGraph(float (*func)(float)) {
    for (float x = MATH_MIN; x < MATH_MAX; x += 0.05f) {
        float y = func(x);
        int screen_x = mathToScreenX(x);
        int screen_y = mathToScreenY(y);
        
        if (screen_x >= 0 && screen_x < SCREEN_WIDTH && 
            screen_y >= 0 && screen_y < SCREEN_HEIGHT) {
            display.drawPixel(screen_x, screen_y, display.C_GREEN);
        }
    }
}

float parabola(float x) {
    return x * x / 5.0f;
}

float sine_wave(float x) {
    return 2.0f * sin(x);
}

float linear(float x) {
    return x;
}

int main() {
    stdio_init_all();
    sleep_ms(1000);
    
    display.SetupGPIO(20, 21, 17, 18, 19, 16);
    display.SetupScreenSize(240, 320);
    display.SetupSPI(25000000, spi0);
    display.ILI9341Initialize();
    
    display.fillScreen(display.C_BLACK);
    
    drawGrid();
    drawAxes();
    drawGraph(sine_wave);
    
    while(true) {
        sleep_ms(1000);
    }
    
    return 0;
}