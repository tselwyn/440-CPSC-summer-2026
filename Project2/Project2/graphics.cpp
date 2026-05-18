// graphics.cpp - Drawing and input implementation
// Tyler Selwyn - CPSC 440 - Program 2

#include "graphics.h"
#include <cmath>

// draws the 5x5 grid lines
void draw_grid() {
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

    for (int i = 0; i <= COLS; i++) {
        al_draw_line(i * CELL_SIZE, 0, i * CELL_SIZE, ROWS * CELL_SIZE, white, 2);
    }

    for (int i = 0; i <= ROWS; i++) {
        al_draw_line(0, i * CELL_SIZE, COLS * CELL_SIZE, i * CELL_SIZE, white, 2);
    }
}

// figures out which cell was clicked based on pixel position
void get_mouse_input(int mx, int my, int& row, int& col) {
    col = mx / CELL_SIZE;
    row = my / CELL_SIZE;

    if (row < 0) row = 0;
    if (row >= ROWS) row = ROWS - 1;
    if (col < 0) col = 0;
    if (col >= COLS) col = COLS - 1;
}

void draw_circle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x, y, 40, color);
}

void draw_triangle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_triangle(x, y - 40, x - 40, y + 40, x + 40, y + 40, color);
}

void draw_rectangle_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x - 35, y - 25, x + 35, y + 25, color);
}

// 4 point polygon rotated 45 degrees
void draw_diamond_shape(int x, int y, ALLEGRO_COLOR color) {
    float points[8] = { (float)x, (float)(y - 40), (float)(x + 30), (float)y,
                         (float)x, (float)(y + 40), (float)(x - 30), (float)y };
    al_draw_filled_polygon(points, 4, color);
}

void draw_oval_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_ellipse(x, y, 40, 25, color);
}

// 8-sided polygon
void draw_octagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float s = 18;
    float r = 40;
    float points[16] = {
        x - s, y - r,  x + s, y - r,
        x + r, y - s,  x + r, y + s,
        x + s, y + r,  x - s, y + r,
        x - r, y + s,  x - r, y - s
    };
    al_draw_filled_polygon(points, 8, color);
}

// 5 point star with outer and inner radius
void draw_star_shape(int x, int y, ALLEGRO_COLOR color) {
    float outer = 40;
    float inner = 18;
    float points[20];
    for (int i = 0; i < 5; i++) {
        float angle_out = (i * 72 - 90) * 3.14159f / 180.0f;
        float angle_in = ((i * 72) + 36 - 90) * 3.14159f / 180.0f;
        points[i * 4] = x + outer * cos(angle_out);
        points[i * 4 + 1] = y + outer * sin(angle_out);
        points[i * 4 + 2] = x + inner * cos(angle_in);
        points[i * 4 + 3] = y + inner * sin(angle_in);
    }
    al_draw_filled_polygon(points, 10, color);
}

// two overlapping rectangles
void draw_cross_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_rectangle(x - 10, y - 35, x + 10, y + 35, color);
    al_draw_filled_rectangle(x - 35, y - 10, x + 35, y + 10, color);
}

// triangle on top, rectangle on bottom
void draw_arrow_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_triangle(x, y - 40, x - 30, y, x + 30, y, color);
    al_draw_filled_rectangle(x - 12, y, x + 12, y + 35, color);
}

void draw_hexagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float r = 38;
    float points[12];
    for (int i = 0; i < 6; i++) {
        float angle = (i * 60 - 30) * 3.14159f / 180.0f;
        points[i * 2] = x + r * cos(angle);
        points[i * 2 + 1] = y + r * sin(angle);
    }
    al_draw_filled_polygon(points, 6, color);
}

void draw_pentagon_shape(int x, int y, ALLEGRO_COLOR color) {
    float r = 38;
    float points[10];
    for (int i = 0; i < 5; i++) {
        float angle = (i * 72 - 90) * 3.14159f / 180.0f;
        points[i * 2] = x + r * cos(angle);
        points[i * 2 + 1] = y + r * sin(angle);
    }
    al_draw_filled_polygon(points, 5, color);
}

// two circles on top with a triangle underneath
void draw_heart_shape(int x, int y, ALLEGRO_COLOR color) {
    al_draw_filled_circle(x - 18, y - 10, 20, color);
    al_draw_filled_circle(x + 18, y - 10, 20, color);
    al_draw_filled_triangle(x - 38, y - 2, x + 38, y - 2, x, y + 40, color);
}

// draws an X over matched cells
void draw_matched(int x, int y) {
    ALLEGRO_COLOR gray = al_map_rgb(100, 100, 100);
    al_draw_line(x - 35, y - 35, x + 35, y + 35, gray, 3);
    al_draw_line(x + 35, y - 35, x - 35, y + 35, gray, 3);
}

// status info in the bottom-right cell
void draw_status(ALLEGRO_FONT* font, int matched, int remaining) {
    int x = 4 * CELL_SIZE + 10;
    int y = 4 * CELL_SIZE + 20;

    // green background for status cell
    al_draw_filled_rectangle(4 * CELL_SIZE + 1, 4 * CELL_SIZE + 1,
        5 * CELL_SIZE - 1, 5 * CELL_SIZE - 1, al_map_rgb(0, 80, 0));

    char buf[50];
    sprintf_s(buf, "Matched: %d", matched);
    al_draw_text(font, al_map_rgb(255, 255, 255), x, y, 0, buf);

    sprintf_s(buf, "Left: %d", remaining);
    al_draw_text(font, al_map_rgb(255, 255, 255), x, y + 30, 0, buf);
}

// picks the right draw function based on shape type
void draw_objects(int x, int y, ShapeType shape) {
    ALLEGRO_COLOR color;
    switch (shape) {
    case CIRCLE:    color = al_map_rgb(255, 0, 0); draw_circle_shape(x, y, color); break;
    case TRIANGLE:  color = al_map_rgb(0, 255, 0); draw_triangle_shape(x, y, color); break;
    case RECTANGLE: color = al_map_rgb(0, 0, 25