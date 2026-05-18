// graphics.cpp - Drawing and input implementation
// Tyler Selwyn - CPSC 440 - Program 2

#include "graphics.h"

void draw_grid() {
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    // vertical lines
    for (int i = 0; i <= COLS; i++) {
        al_draw_line(i * CELL_SIZE, 0, i * CELL_SIZE, ROWS * CELL_SIZE, white, 2);
    }

    // horizontal lines
    for (int i = 0; i <= ROWS; i++) {
        al_draw_line(0, i * CELL_SIZE, COLS * CELL_SIZE, i * CELL_SIZE, white, 2);
    }
}

void get_mouse_input(int mx, int my, int& row, int& col) {
    col = mx / CELL_SIZE;
    row = my / CELL_SIZE;

    // bounds check
    if (row < 0) row = 0;
    if (row >= ROWS) row = ROWS - 1;
    if (col < 0) col = 0;
    if (col >= COLS) col = COLS - 1;
}